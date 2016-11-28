#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

// Class that represents an undirected graph where
// you can find the biconnected components (separated by
// articulation points).
class BCCGraph {
    public:
        explicit BCCGraph(const int num_vertices) : num_vertices_(num_vertices) {
            discovery_time_.resize(num_vertices + 1);
            low_link_.resize(num_vertices + 1);
            edges_.resize(num_vertices + 1);
            is_articulation_point_.resize(num_vertices + 1);
        }

        void AddEdge(const int from, const int to) {
            edges_[from].push_back(to);
            edges_[to].push_back(from);
        }

        void FindBiconnectedComponents() {
            current_count_ = 0;
            fill(discovery_time_.begin(), discovery_time_.end(), 0);
            fill(low_link_.begin(), low_link_.end(), 0);
            fill(is_articulation_point_.begin(), is_articulation_point_.end(), 0);
            biconnected_components_.clear();
            stack_.clear();
            DFS(1, 0);
        }

        vector<vector<int>> GetBiconnectedComponents() {
            return biconnected_components_;
        }

        bool IsArticulationPoint(const int node) const {
            return is_articulation_point_[node];
        }

    private:
        void DFS(const int node, const int father) {
            discovery_time_[node] = low_link_[node] = ++current_count_;
            stack_.push_back(node);

            for (auto neighbour : edges_[node]) {
                if (neighbour != father) {
                    if (!discovery_time_[neighbour]) {
                        DFS(neighbour, node);
                        low_link_[node] = min(low_link_[node], low_link_[neighbour]);

                        // The current node is an articulation point
                        if (low_link_[neighbour] >= discovery_time_[node]) {
                            FetchComponent(node, neighbour);
                        }
                    } else {
                        low_link_[node] = min(low_link_[node], discovery_time_[neighbour]);
                    }
                }
            }
        }

        void FetchComponent(const int node, const int son) {
            is_articulation_point_[node] = 1;
            vector<int> new_component;
            while (stack_.back() != son) {
                new_component.push_back(stack_.back());
                stack_.pop_back();
            }
            stack_.pop_back();
            new_component.push_back(son);
            new_component.push_back(node);
            biconnected_components_.push_back(new_component);
        }

        const int num_vertices_;
        int current_count_;
        vector<int> discovery_time_;
        vector<int> low_link_;
        vector<bool> is_articulation_point_;
        vector<vector<int>> edges_;
        vector<vector<int>> biconnected_components_;
        vector<int> stack_;
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    BCCGraph graph(n);
    for (; m; m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        graph.AddEdge(x, y);
    }

    graph.FindBiconnectedComponents();
    vector<vector<int>> bcc = graph.GetBiconnectedComponents();

    for (auto& comp : bcc) {
        sort(comp.begin(), comp.end());
    }
    sort(bcc.begin(), bcc.end());

    printf("%d\n", (int)bcc.size());
    for (auto& comp : bcc) {
        for (auto x : comp) {
            printf("%d ", x);
        }
        printf("\n");
    }

    return 0;
}
