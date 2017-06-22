#include <stdio.h>
#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// Class that represents a directed graph where you
// can find the min cost max flow with Dijkstra.
// Memory complexity: O(number_of_vertices ^ 2).
// vector<vector<int>> is too slow.
// Unfortunately, you have to modify kMax manually.
template<class F, class C>
class MinCostMaxFlowGraph {
 public:
  explicit MinCostMaxFlowGraph(const int num_vertices) :
    num_vertices_(num_vertices) {
    previous_vertex_.resize(num_vertices_ + 1);
    bellman_distance_.resize(num_vertices_ + 1);
    distance_.resize(num_vertices_ + 1);
  }

  void AddEdge(const int from, const int to,
               const F capacity, const C cost, const int index) {
    neighbours_[from].push_back(to);
    capacity_[from][to] += capacity;
    cost_[from][to] += cost;
    neighbours_[to].push_back(from);
    cost_[to][from] -= cost;
    index_[from][to] = index;
  }

  void AddEdge(const int from, const int to, const F capacity, const C cost) {
    AddEdge(from, to, capacity, cost, 0);
  }

  pair<F, C> GetMinCostMaxFlow(const int source, const int sink) {
    FindBellmanDistances(source);
    F max_flow = 0;
    C min_cost = 0;

    while (PushFlow(source, sink)) {
      F flow_added = numeric_limits<F>::max();

      int current_vertex = sink;
      while (current_vertex != source) {
        int previous_vertex = previous_vertex_[current_vertex];
        flow_added = min(flow_added, capacity_[previous_vertex][current_vertex]
                         - flow_[previous_vertex][current_vertex]);
        current_vertex = previous_vertex_[current_vertex];
      }

      current_vertex = sink;
      while (current_vertex != source) {
        int previous_vertex = previous_vertex_[current_vertex];
        flow_[previous_vertex][current_vertex] += flow_added;
        flow_[current_vertex][previous_vertex] -= flow_added;
        current_vertex = previous_vertex_[current_vertex];
      }

      max_flow += flow_added;
      min_cost += bellman_distance_[sink] * flow_added;
    }

    return make_pair(max_flow, min_cost);
  }

  F GetFlow(const int from, const int to) const {
    return flow_[from][to];
  }

  int GetIndex(const int from, const int to) const {
    return index_[from][to];
  }

 private:
  void FindBellmanDistances(const int source) {
    fill(bellman_distance_.begin(), bellman_distance_.end(),
         numeric_limits<C>::max());
    vector<bool> in_queue(num_vertices_ + 1, false);
    queue<int> q;

    bellman_distance_[source] = 0;
    in_queue[source] = true;
    q.push(source);

    while (!q.empty()) {
      int vertex = q.front();
      q.pop();
      in_queue[vertex] = false;

      for (int neighbour : neighbours_[vertex]) {
        F edge_capacity = capacity_[vertex][neighbour];
        F edge_flow = flow_[vertex][neighbour];
        if (edge_flow < edge_capacity) {
          C edge_cost = cost_[vertex][neighbour];
          if (bellman_distance_[vertex] + edge_cost < bellman_distance_[neighbour]) {
            bellman_distance_[neighbour] = bellman_distance_[vertex] + edge_cost;
            if (!in_queue[neighbour]) {
              in_queue[neighbour] = true;
              q.push(neighbour);
            }
          }
        }
      }
    }
  }

  bool PushFlow(int source, int sink) {
    fill(previous_vertex_.begin(), previous_vertex_.end(), -1);
    fill(distance_.begin(), distance_.end(), numeric_limits<C>::max());
    priority_queue<pair<C, int>, vector<pair<C, int>>, greater<pair<C, int>>> q;
    vector<C> new_bellman_distance(num_vertices_ + 1, 0);

    distance_[source] = 0;
    q.push({0, source});

    while (!q.empty()) {
      int vertex = q.top().second;
      C current_cost = q.top().first;
      q.pop();

      if (current_cost > distance_[vertex]) {
        continue;
      }

      for (int neighbour : neighbours_[vertex]) {
        F edge_capacity = capacity_[vertex][neighbour];
        F edge_flow = flow_[vertex][neighbour];
        if (edge_flow < edge_capacity) {
          C edge_cost = cost_[vertex][neighbour] + bellman_distance_[vertex]
                        - bellman_distance_[neighbour];
          if (distance_[vertex] + edge_cost < distance_[neighbour]) {
            distance_[neighbour] = distance_[vertex] + edge_cost;
            new_bellman_distance[neighbour] = new_bellman_distance[vertex]
                                              + cost_[vertex][neighbour];
            previous_vertex_[neighbour] = vertex;
            q.push({distance_[neighbour], neighbour});
          }
        }
      }
    }

    for (int i = 0; i < num_vertices_; i++) {
      bellman_distance_[i] = new_bellman_distance[i];
    }

    return distance_[sink] != numeric_limits<C>::max();
  }

  static const int kMax = 605;
  const int num_vertices_;
  vector<int> neighbours_[kMax];
  F capacity_[kMax][kMax];
  F flow_[kMax][kMax];
  C cost_[kMax][kMax];
  int index_[kMax][kMax];
  vector<int> previous_vertex_;
  vector<C> bellman_distance_;
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
