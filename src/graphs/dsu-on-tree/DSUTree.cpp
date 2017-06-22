#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class DSUTree {
 public:
  // Must be indexed from 1.
  explicit DSUTree(const vector<int>& color) :
    root_(1), num_vertices_(color.size() - 1), color_(color) {
    edges_.resize(color.size());
  }

  void AddEdge(int from, int to) {
    edges_[from].push_back(to);
    edges_[to].push_back(from);
  }

  // Gets the sum of all dominating color from each vertex.
  vector<long long> GetSolution() {
    subtree_.resize(num_vertices_ + 1);
    first_apparition_.resize(num_vertices_ + 1);
    last_apparition_.resize(num_vertices_ + 1);

    PrepareDFS(root_, -1);

    frequency_.resize(num_vertices_ + 1);
    sum_of_colors_.resize(num_vertices_ + 1);
    answer_.resize(num_vertices_ + 1);
    max_frequency_ = 0;

    for (int i = 1; i <= num_vertices_; i++) {
      sum_of_colors_[0] += color_[i];
    }

    SolveDFS(root_, false);

    return answer_;
  }

 private:
  void PrepareDFS(int vertex, int father) {
    subtree_[vertex] = 1;
    first_apparition_[vertex] = linearization_.size();
    linearization_.push_back(vertex);

    for (int son : edges_[vertex]) {
      if (son != father) {
        PrepareDFS(son, vertex);
        subtree_[vertex] += subtree_[son];
      }
    }

    for (int& son : edges_[vertex]) {
      if (son == father) {
        swap(son, edges_[vertex].back());
        edges_[vertex].pop_back();
        break;
      }
    }

    last_apparition_[vertex] = linearization_.size() - 1;
  }

  void SolveDFS(int vertex, bool dump) {
    int max_subtree = 0;
    int big_son = -1;

    for (int son : edges_[vertex]) {
      if (subtree_[son] > max_subtree) {
        max_subtree = subtree_[son];
        big_son = son;
      }
    }

    for (int son : edges_[vertex]) {
      if (son != big_son) {
        SolveDFS(son, true);
      }
    }
    if (big_son != -1) {
      SolveDFS(big_son, false);
    }

    AddToSack(vertex);
    for (int son : edges_[vertex]) {
      if (son != big_son) {
        for (int i = first_apparition_[son]; i <= last_apparition_[son]; i++) {
          AddToSack(linearization_[i]);
        }
      }
    }

    answer_[vertex] = sum_of_colors_[max_frequency_];

    if (dump) {
      max_frequency_ = 0;
      for (int i = first_apparition_[vertex]; i <= last_apparition_[vertex]; i++) {
        RemoveFromSack(linearization_[i]);
      }
    }
  }

  void AddToSack(int vertex) {
    sum_of_colors_[frequency_[color_[vertex]]] -= color_[vertex];
    frequency_[color_[vertex]]++;
    sum_of_colors_[frequency_[color_[vertex]]] += color_[vertex];
    max_frequency_ = max(max_frequency_, frequency_[color_[vertex]]);
  }

  void RemoveFromSack(int vertex) {
    sum_of_colors_[frequency_[color_[vertex]]] = 0;
    frequency_[color_[vertex]] = 0;
  }

  const int root_;
  const int num_vertices_;
  const vector<int> color_;
  int max_frequency_;
  vector<int> subtree_;
  vector<int> first_apparition_;
  vector<int> last_apparition_;
  vector<int> linearization_;
  vector<int> frequency_;
  vector<long long> sum_of_colors_;
  vector<long long> answer_;
  vector<vector<int>> edges_;
};

int main() {
  cin.sync_with_stdio(false);

  int n;
  cin >> n;

  vector<int> color(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> color[i];
  }

  DSUTree dsutree(color);
  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    dsutree.AddEdge(x, y);
  }

  auto answer = dsutree.GetSolution();
  for (int i = 1; i <= n; i++) {
    cout << answer[i] << " ";
  }

  return 0;
}
