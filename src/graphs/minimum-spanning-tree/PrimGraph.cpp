#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

template<class T>
class PrimGraph {
 public:
  explicit PrimGraph(const int num_vertices) : num_vertices_(num_vertices) {
    edges_.resize(num_vertices + 1);
    distance_.resize(num_vertices + 1, kMaxCost);
    father_.resize(num_vertices + 1, 0);
    visited_.resize(num_vertices + 1, false);
  }

  void AddEdge(const int from, const int to, const T cost) {
    edges_[from].push_back({to, cost});
    edges_[to].push_back({from, cost});
  }

  pair<T, vector<pair<int, int>>> GetMinimumSpanningTree() {
    T total_cost = 0;
    vector<pair<int, int>> spanning_tree;

    ExtendVertex(1);
    while (!queue.empty()) {
      T current_cost = queue.top().first;
      int current_vertex = queue.top().second;
      queue.pop();

      if (visited_[current_vertex]) {
        continue;
      }

      total_cost += current_cost;
      spanning_tree.push_back({current_vertex, father_[current_vertex]});

      ExtendVertex(current_vertex);
    }

    return {total_cost, spanning_tree};
  }

 private:
  void ExtendVertex(const int vertex) {
    visited_[vertex] = true;
    for (auto& edge : edges_[vertex]) {
      int neighbour = edge.first;
      T cost = edge.second;

      if (!visited_[neighbour] && cost < distance_[neighbour]) {
        distance_[neighbour] = cost;
        father_[neighbour] = vertex;
        queue.push({distance_[neighbour], neighbour});
      }
    }
  }

  const int kMaxCost = numeric_limits<T>::max();
  const int num_vertices_;
  vector<vector<pair<int, T>>> edges_;
  vector<T> distance_;
  vector<int> father_;
  vector<bool> visited_;
  priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> queue;
};

int main() {
  cin.sync_with_stdio(false);

  int n, m;
  cin >> n >> m;

  PrimGraph<int> graph(n);
  for (; m; m--) {
    int x, y, z;
    cin >> x >> y >> z;
    graph.AddEdge(x, y, z);
  }

  pair<int, vector<pair<int, int>>> ans = graph.GetMinimumSpanningTree();
  cout << ans.first << '\n';

  return 0;
}
