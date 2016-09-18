#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

// Class that represents a directed graph where you
// can find the max flow.
// vector<vector<int>> is too slow.
// Unfortunately, you have to modify kMax manually.
template<class F>
class MinCostMaxFlowGraph {
    public:
        MinCostMaxFlowGraph(int num_vertices) : num_vertices_(num_vertices + 1) {
            previous_vertex_.resize(num_vertices_);
        }

        void AddEdge(int from, int to, F capacity) {
            neighbours_[from].push_back(to);
            capacity_[from][to] += capacity;
            neighbours_[to].push_back(from);
        }

        F GetMinCostMaxFlow(int source, int sink) {
            F max_flow = 0;
            while (PushFlow(source, sink)) {
                for (int vertex : neighbours_[sink]) {
                    if (previous_vertex_[vertex] != -1) {
                        previous_vertex_[sink] = vertex;
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
                    }
                }
            }
            return max_flow;
        }

        F GetFlow(int from, int to) const {
            return flow_[from][to];
        }

    private:
        bool PushFlow(int source, int sink) {
            fill(previous_vertex_.begin(), previous_vertex_.end(), -1);
            queue<int> q;

            previous_vertex_[source] = 0;
            q.push(source);

            while (!q.empty()) {
                int vertex = q.front();
                q.pop();

                if (vertex == sink) {
                    continue;
                }

                for (int neighbour : neighbours_[vertex]) {
                    F edge_capacity = capacity_[vertex][neighbour];
                    F edge_flow = flow_[vertex][neighbour];

                    if (previous_vertex_[neighbour] == -1 && edge_flow < edge_capacity) {
                        previous_vertex_[neighbour] = vertex;
                        q.push(neighbour);
                    }
                }
            }

            return previous_vertex_[sink] != -1;
        }

        static const int kMax = 1005;
        int num_vertices_;
        vector<int> neighbours_[kMax];
        F capacity_[kMax][kMax];
        F flow_[kMax][kMax];
        vector<int> previous_vertex_;
};

int main() {
    return 0;
}
