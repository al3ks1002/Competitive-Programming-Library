#include <iostream>
#include <vector>

using namespace std;

class MaxMatchingBipartiteGraph {
 public:
  MaxMatchingBipartiteGraph(const int num_vertices_left,
                            const int num_vertices_right) :
    num_vertices_left_(num_vertices_left),
    num_vertices_right_(num_vertices_right) {
    edges_.resize(num_vertices_left_ + 1);
    visited_.resize(num_vertices_left_ + 1, 0);
    match_for_left_.resize(num_vertices_left_ + 1, 0);
    match_for_right_.resize(num_vertices_right_ + 1, 0);
  }

  void AddEdge(const int from, const int to) {
    edges_[from].push_back(to);
  }

  int GetMaximumMatching() {
    int matching = 0;
    bool ok = 1;
    while (ok) {
      ok = 0;
      fill(visited_.begin(), visited_.end(), 0);
      for (int i = 1; i <= num_vertices_left_; i++) {
        if (!match_for_left_[i] && PairUp(i)) {
          ok = 1;
          matching++;
        }
      }
    }
    return matching;
  }

  int GetMatchForLeft(const int vertex) const {
    return match_for_left_[vertex];
  }

  int GetMatchForRight(const int vertex) const {
    return match_for_right_[vertex];
  }

 private:
  bool PairUp(const int vertex) {
    if (visited_[vertex]) {
      return 0;
    }
    visited_[vertex] = 1;

    for (auto it : edges_[vertex])
      if (!match_for_right_[it]) {
        match_for_left_[vertex] = it;
        match_for_right_[it] = vertex;
        return 1;
      }

    for (auto it : edges_[vertex])
      if (PairUp(match_for_right_[it])) {
        match_for_left_[vertex] = it;
        match_for_right_[it] = vertex;
        return 1;
      }

    return 0;
  }

  const int num_vertices_left_;
  const int num_vertices_right_;
  vector<vector<int>> edges_;
  vector<bool> visited_;
  vector<int> match_for_left_;
  vector<int> match_for_right_;
};

int main() {
  cin.sync_with_stdio(false);

  int n, m, e;
  cin >> n >> m >> e;

  MaxMatchingBipartiteGraph graph(n, m);

  for (; e; e--) {
    int x, y;
    cin >> x >> y;
    graph.AddEdge(x, y);
  }

  cout << graph.GetMaximumMatching() << '\n';

  return 0;
}
