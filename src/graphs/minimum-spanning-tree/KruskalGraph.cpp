#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class DisjointSet {
    public:
        explicit DisjointSet(const int size) : size_(size + 1) {
            father_.resize(size_);
            rank_.resize(size_);
            for (int i = 0; i < size_; i++) {
                father_[i] = i;
                rank_[i] = 1;
            }
        }

        int Find(const int x) {
            if (father_[x] != x) {
                father_[x] = Find(father_[x]);
            }
            return father_[x];
        }

        // x and y must be roots
        void Unite(const int x, const int y) {
            if (rank_[x] < rank_[y]) {
                father_[x] = y;
            } else {
                father_[y] = x;
                if (rank_[x] == rank_[y]) {
                    rank_[x]++;
                }
            }
        }

    private:
        const int size_;
        vector<int> father_;
        vector<int> rank_;
};

template<class T>
class KruskalGraph {
    public:
        explicit KruskalGraph(const int num_vertices) : num_vertices_(num_vertices) {}

        void AddEdge(const int from, const int to, const T cost) {
            edges_.emplace_back(from, to, cost);
        }

        pair<T, vector<pair<int, int>>> GetMinimumSpanningTree() {
            T total_cost = 0;
            vector<pair<int, int>> spanning_tree;

            DisjointSet disjoint_set(num_vertices_);

            sort(edges_.begin(), edges_.end());
            for (Edge& edge : edges_) {
                int root_from = disjoint_set.Find(edge.from_);
                int root_to = disjoint_set.Find(edge.to_);

                if (root_from != root_to) {
                    total_cost += edge.cost_;
                    spanning_tree.push_back({edge.from_, edge.to_});
                    disjoint_set.Unite(root_from, root_to);
                }
            }

            return {total_cost, spanning_tree};
        }

    private:
        struct Edge {
            int from_;
            int to_;
            T cost_;

            Edge(int from , int to, T cost) : from_(from), to_(to), cost_(cost) {}

            bool operator < (const Edge &other) const {
                return cost_ < other.cost_;
            }
        };

        const int num_vertices_;
        vector<Edge> edges_;
};


int main() {
    cin.sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    KruskalGraph<int> graph(n);
    for (; m; m--) {
        int x, y, z;
        cin >> x >> y >> z;
        graph.AddEdge(x, y, z);
    }

    pair<int, vector<pair<int, int>>> ans = graph.GetMinimumSpanningTree();
    cout << ans.first << '\n';

    return 0;
}
