#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

// Class that represents a directed graph where you
// can find the min cost max flow with Bellman-Ford.
// Memory complexity: O(number_of_vertices ^ 2).
// vector<vector<int>> is too slow.
// Unfortunately, you have to modify kMax manually.
template<class F, class C>
class MinCostMaxFlowGraph {
    public:
        MinCostMaxFlowGraph(int num_vertices) : num_vertices_(num_vertices + 1) {
            previous_vertex_.resize(num_vertices_);
            distance_.resize(num_vertices_);
        }

        void AddEdge(int from, int to, F capacity, C cost) {
            AddEdge(from, to, capacity, cost, 0);
        }

        void AddEdge(int from, int to, F capacity, C cost, int index) {
            neighbours_[from].push_back(to);
            capacity_[from][to] += capacity;
            cost_[from][to] += cost;
            neighbours_[to].push_back(from);
            cost_[to][from] -= cost;
            index_[from][to] = index;
        }

        pair<F, C> GetMinCostMaxFlow(int source, int sink) {
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
                min_cost += distance_[sink] * flow_added;
            }
            return make_pair(max_flow, min_cost);
        }

        F GetFlow(int from, int to) const {
            return flow_[from][to];
        }

        int GetIndex(int from, int to) const {
            return index_[from][to];
        }

    private:
        bool PushFlow(int source, int sink) {
            fill(previous_vertex_.begin(), previous_vertex_.end(), -1);
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

                for (int neighbour : neighbours_[vertex]) {
                    F edge_capacity = capacity_[vertex][neighbour];
                    F edge_flow = flow_[vertex][neighbour];
                    C edge_cost = cost_[vertex][neighbour];

                    if (distance_[vertex] + edge_cost < distance_[neighbour]
                            && edge_flow < edge_capacity) {
                        distance_[neighbour] = distance_[vertex] + edge_cost;
                        previous_vertex_[neighbour] = vertex;
                        if (!in_queue[neighbour]) {
                            in_queue[neighbour] = true;
                            q.push(neighbour);
                        }
                    }
                }
            }

            return distance_[sink] != numeric_limits<C>::max();
        }

        static const int kMax = 355;
        int num_vertices_;
        vector<int> neighbours_[kMax];
        F capacity_[kMax][kMax];
        F flow_[kMax][kMax];
        C cost_[kMax][kMax];
        int index_[kMax][kMax];
        vector<int> previous_vertex_;
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
