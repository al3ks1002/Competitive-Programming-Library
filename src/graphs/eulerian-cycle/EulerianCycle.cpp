#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

class EulerianGraph {
    public:
        explicit EulerianGraph(const int num_vertices) :
            num_vertices_(num_vertices), edge_index_(0) {
            visited_.resize(num_vertices_ + 1, false);
            edges_.resize(num_vertices_ + 1);
        }

        void AddEdge(const int from, const int to) {
            edges_[from].emplace_back(to, edge_index_);
            edges_[to].emplace_back(from, edge_index_);
            edge_index_++;
        }

        vector<int> FindEulerianCycle() {
            vector<int> eulerian_cycle;
            if (!IsConnected() || !IsEulerian()) {
                return eulerian_cycle;
            }

            vector<bool> done_edge(edge_index_, false);
            stack<int> stack;

            stack.push(1);
            while (!stack.empty()) {
                int vertex = stack.top();

                if (!edges_[vertex].empty()) {
                    int neighbour = edges_[vertex].back().first;
                    int index = edges_[vertex].back().second;

                    if (!done_edge[index]) {
                        done_edge[index] = 1;
                        stack.push(neighbour);
                    }

                    edges_[vertex].pop_back();
                } else {
                    eulerian_cycle.push_back(stack.top());
                    stack.pop();
                }
            }

            return eulerian_cycle;
        }

    private:
        bool IsConnected() {
            DFS(1);
            for (int i = 1; i <= num_vertices_; i++) {
                if (!visited_[i]) {
                    return 0;
                }
            }
            return 1;
        }

        bool IsEulerian() const {
            for (int i = 1; i <= num_vertices_; i++) {
                if (edges_[i].size() & 1) {
                    return 0;
                }
            }
            return 1;
        }

        void DFS(const int vertex) {
            visited_[vertex] = 1;
            for (auto neighbour : edges_[vertex]) {
                if (!visited_[neighbour.first]) {
                    DFS(neighbour.first);
                }
            }
        }

        const int num_vertices_;
        int edge_index_;
        vector<bool> visited_;
        vector<vector<pair<int, int>>> edges_;
};

int main() {
    cin.sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    EulerianGraph graph(n);
    for (; m; m--) {
        int x, y;
        cin >> x >> y;
        graph.AddEdge(x, y);
    }

    auto ans = graph.FindEulerianCycle();
    if (ans.empty()) {
        cout << "-1\n";
        return 0;
    }
    for (auto it : ans) {
        cout << it << " ";
    }

    return 0;
}
