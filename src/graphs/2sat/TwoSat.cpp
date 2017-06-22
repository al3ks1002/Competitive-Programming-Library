#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class SCCGraph {
 public:
  explicit SCCGraph(const int num_vertices) : num_vertices_(num_vertices) {
    edges_.resize(num_vertices + 1);
    transpose_edges_.resize(num_vertices + 1);
    visited_.resize(num_vertices + 1, false);
    what_component_.resize(num_vertices + 1, false);
  }

  void AddEdge(const int from, const int to) {
    edges_[from].push_back(to);
    transpose_edges_[to].push_back(from);
  }

  // Returns the number of components and a vector representing
  // for each vertex the component in which it resides (0 indexed).
  pair<int, vector<int>> GetStronglyConnectedComponents() {
    for (int i = 1; i <= num_vertices_; i++) {
      if (!visited_[i]) {
        DFS(i);
      }
    }

    int components = 0;
    fill(visited_.begin(), visited_.end(), false);
    reverse(topological_sorting_.begin(), topological_sorting_.end());
    for (int vertex : topological_sorting_) {
      if (!visited_[vertex]) {
        components++;
        DFST(vertex, components - 1);
      }
    }

    return {components, what_component_};
  }

 private:
  void DFS(const int vertex) {
    visited_[vertex] = true;

    for (auto neighbour : edges_[vertex]) {
      if (!visited_[neighbour]) {
        DFS(neighbour);
      }
    }

    topological_sorting_.push_back(vertex);
  }

  void DFST(const int vertex, const int current_component) {
    visited_[vertex] = true;
    what_component_[vertex] = current_component;

    for (auto neighbour : transpose_edges_[vertex]) {
      if (!visited_[neighbour]) {
        DFST(neighbour, current_component);
      }
    }
  }

  const int num_vertices_;
  vector<vector<int>> edges_;
  vector<vector<int>> transpose_edges_;
  vector<bool> visited_;
  vector<int> topological_sorting_;
  vector<int> what_component_;
};

class TwoSat {
 public:
  explicit TwoSat(int num_terms) : num_terms_(num_terms),
    sat_graph_(2 * num_terms) {}

  void AddProposition(int x, int y) {
    if (x < 0) {
      x = Transform(x);
    }
    if (y < 0) {
      y = Transform(y);
    }

    sat_graph_.AddEdge(Negate(x), y);
    sat_graph_.AddEdge(Negate(y), x);
  }

  // Returns empty vector if there is no solution
  vector<bool> Find2Sat() {
    vector<bool> sat;

    vector<int> what_component = sat_graph_.GetStronglyConnectedComponents().second;
    for (int i = 1; i <= num_terms_; i++) {
      if (what_component[i] == what_component[Negate(i)]) {
        return sat;
      }
    }

    sat.resize(num_terms_ + 1, 0);
    for (int i = 1; i <= num_terms_; i++) {
      sat[i] = (what_component[i] > what_component[Negate(i)]);
    }

    return sat;
  }

 private:
  int Transform(const int x) const {
    return -x + num_terms_;
  }

  int Negate(const int x) const {
    if (x <= num_terms_) {
      return x + num_terms_;
    }
    return x - num_terms_;
  }

  const int num_terms_;
  SCCGraph sat_graph_;
};

int main() {
  cin.sync_with_stdio(false);

  int n, m;
  cin >> n >> m;

  TwoSat sat(n);

  for (; m; m--) {
    int x, y;
    cin >> x >> y;
    sat.AddProposition(x, y);
  }

  vector<bool> ans = sat.Find2Sat();

  if (ans.empty()) {
    cout << "-1\n";
  } else {
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " ";
    }
  }

  return 0;
}
