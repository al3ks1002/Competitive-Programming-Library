#include <stdio.h>
#include <algorithm>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// Class that represents a directed graph where you
// can find the min cost max flow with Bellman-Ford.
// Memory complexity: O(number_of_edges).
// Slower than O(number_of_vertices ^ 2) version.
// It is useful when you have a graph with edges a->b and b->a.
template<class F, class C>
class MinCostMaxFlowGraph {
 public:
  explicit MinCostMaxFlowGraph(const int num_vertices) :
    num_vertices_(num_vertices) {
    neighbours_.resize(num_vertices_ + 1);
    previous_edge_.resize(num_vertices_ + 1);
    distance_.resize(num_vertices_ + 1);
  }

  void AddEdge(const int from, const int to, const F capacity, const C cost) {
    neighbours_[from].push_back(edges_.size());
    edges_.emplace_back(from, to, capacity, cost);
    neighbours_[to].push_back(edges_.size());
    edges_.emplace_back(to, from, 0, -cost);
  }

  pair<F, C> GetMinCostMaxFlow(const int source, const int sink) {
    F max_flow = 0;
    C min_cost = 0;
    while (PushFlow(source, sink)) {
      F flow_added = numeric_limits<F>::max();

      int current_vertex = sink;
      while (current_vertex != source) {
        F edge_capacity = edges_[previous_edge_[current_vertex]].capacity_;
        flow_added = min(flow_added, edge_capacity);
        current_vertex = edges_[previous_edge_[current_vertex]].from_;
      }

      current_vertex = sink;
      while (current_vertex != source) {
        edges_[previous_edge_[current_vertex]].capacity_ -= flow_added;
        edges_[previous_edge_[current_vertex] ^ 1].capacity_ += flow_added;
        current_vertex = edges_[previous_edge_[current_vertex]].from_;
      }

      max_flow += flow_added;
      min_cost += distance_[sink] * flow_added;
    }
    return make_pair(max_flow, min_cost);
  }

 private:
  struct Edge {
    Edge(int from, int to, F capacity, C cost) :
      from_(from), to_(to), capacity_(capacity), cost_(cost) {}

    int from_;
    int to_;
    F capacity_;
    C cost_;
  };

  bool PushFlow(const int source, const int sink) {
    fill(previous_edge_.begin(), previous_edge_.end(), -1);
    fill(distance_.begin(), distance_.end(), numeric_limits<C>::max());
    vector<bool> in_queue(num_vertices_, false);
    queue<int> q;

    distance_[source] = 0;
    in_queue[source] = true;
    q.push(source);

    while (!q.empty()) {
      int vertex = q.front();
      q.pop();
      in_queue[vertex] = false;

      if (vertex == sink) {
        continue;
      }

      for (int neighbour_edge_index : neighbours_[vertex]) {
        Edge& neighbour_edge = edges_[neighbour_edge_index];
        int neighbour = neighbour_edge.to_;
        F edge_capacity = neighbour_edge.capacity_;
        C edge_cost = neighbour_edge.cost_;

        if (edge_capacity && distance_[vertex] + edge_cost < distance_[neighbour]) {
          distance_[neighbour] = distance_[vertex] + edge_cost;
          previous_edge_[neighbour] = neighbour_edge_index;
          if (!in_queue[neighbour]) {
            in_queue[neighbour] = true;
            q.push(neighbour);
          }
        }
      }
    }

    return distance_[sink] != numeric_limits<C>::max();
  }

  const int num_vertices_;
  vector<Edge> edges_;
  vector<vector<int>> neighbours_;
  vector<int> previous_edge_;
  vector<C> distance_;
};

int main() {
  int n, m, source, sink;
  scanf("%d%d%d%d", &n, &m, &source, &sink);

  MinCostMaxFlowGraph<int, int> graph(n);
  for (; m; m--) {
    int from, to, capacity, cost;
    scanf("%d%d%d%d", &from, &to, &capacity, &cost);
    graph.AddEdge(from, to, capacity, cost);
  }

  printf("%d\n", graph.GetMinCostMaxFlow(source, sink).second);

  return 0;
}
