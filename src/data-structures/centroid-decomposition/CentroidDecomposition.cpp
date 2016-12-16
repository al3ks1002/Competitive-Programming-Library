#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<ld, ld>
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second

// Helper for LCA.
template<class T>
class Rmq {
    public:
        Rmq() {}

        template<typename Array>
        Rmq(const int size, const Array& array, const vector<int>& key) :
            size_(size), lg_max_(GetLog(size)), key_(key) {
            rmq_.resize(lg_max_);
            for (int i = 0; i < (int)rmq_.size(); i++) {
                rmq_[i].resize(size_);
            }
            PrecalculateLog();
            Build(array);
        }

        template<typename Array>
        Rmq(const int size, const Array& array) : Rmq(size, array, vector<int>()) {}

        T Get(const int x, const int y) const {
            int lg = lg_[y - x + 1];
            return GetMin(rmq_[lg][x], rmq_[lg][y - (1 << lg) + 1]);
        }

    private:
        int GetLog(int size) const {
            int lg = 1;
            while (size) {
                lg++;
                size /= 2;
            }
            return lg;
        }

        void PrecalculateLog() {
            lg_.resize(size_ + 1);
            lg_[1] = 0;
            for (int i = 2; i <= size_; i++) {
                lg_[i] = lg_[i / 2] + 1;
            }
        }

        template<typename Array>
        void Build(const Array& array) {
            for (int i = 0; i < size_; i++) {
                rmq_[0][i] = array[i];
            }
            for (int i = 1, p = 2; p <= size_; i++, p *= 2)
                for (int j = 0; j + p - 1 < size_; j++) {
                    rmq_[i][j] = GetMin(rmq_[i - 1][j], rmq_[i - 1][j + p / 2]);
                }
        }

        int GetMin(const int x, const int y) const {
            if (Key(x) < Key(y)) {
                return x;
            }
            return y;
        }

        int Key(const int x) const {
            if (key_.empty()) {
                return x;
            }
            return key_[x];
        }

        const int size_;
        const int lg_max_;
        vector<int> lg_;
        vector<vector<T>> rmq_;
        vector<int> key_;
};

// Can get LCA between two nodes in O(1) with a precalculation of N * log(N)
class LCATree {
    public:
        LCATree(const int num_vertices, const int root) :
            num_vertices_(num_vertices), root_(root), rmq_(nullptr) {
            sons_.resize(num_vertices_ + 1);
            edges_.resize(num_vertices_ + 1);
        }

        void AddEdge(const int father, const int son) {
            sons_[father].push_back(son);
        }

        void AddEdgeBidirectional(const int from, const int to) {
            edges_[from].push_back(to);
            edges_[to].push_back(from);
        }

        void Precalculate() {
            if (!edges_[root_].empty()) {
                FindSons(root_, -1);
            }

            first_apparition_.resize(num_vertices_ + 1, 0);
            level_.resize(num_vertices_ + 1, 0);

            DFS(root_);

            rmq_ = new Rmq<int>(euler_path_.size(), euler_path_, level_);
        }

        int GetLCA(int x, int y) const {
            x = first_apparition_[x];
            y = first_apparition_[y];

            if (x > y) {
                swap(x, y);
            }

            return rmq_->Get(x, y);
        }

        int GetDistance(const int x, const int y) const {
            return level_[x] + level_[y] - 2 * level_[GetLCA(x, y)];
        }

    private:
        void DFS(const int vertex) {
            euler_path_.push_back(vertex);
            first_apparition_[vertex] = euler_path_.size() - 1;

            for (auto son : sons_[vertex]) {
                level_[son] = level_[vertex] + 1;
                DFS(son);
                euler_path_.push_back(vertex);
            }
        }

        void FindSons(const int vertex, const int father) {
            for (auto son : edges_[vertex]) {
                if (son != father) {
                    sons_[vertex].push_back(son);
                    FindSons(son, vertex);
                }
            }
        }

        const int num_vertices_;
        const int root_;
        vector<vector<int>> sons_;
        vector<vector<int>> edges_;
        vector<int> euler_path_;
        vector<int> first_apparition_;
        vector<int> level_;
        Rmq<int>* rmq_;
};

class CentroidDecompositionTree {
    public:
        explicit CentroidDecompositionTree(const int num_vertices) :
            num_vertices_(num_vertices), lca_tree(LCATree(num_vertices, 1)) {
            edges_.resize(num_vertices + 1);
        }

        void AddEdge(const int from, const int to) {
            edges_[from].push_back(to);
            edges_[to].push_back(from);

            lca_tree.AddEdgeBidirectional(from, to);
        }

        void DecomposeTree() {
            centroid_tree_edges_.resize(num_vertices_ + 1);
            label_.resize(num_vertices_ + 1, -1);
            subtree_.resize(num_vertices_ + 1, 0);
            father_centroid_.resize(num_vertices_ + 1, 0);
            answer_.resize(num_vertices_ + 1, kInf);

            int main_centroid = Decompose(1, 0);
            father_centroid_[main_centroid] = -1;

            lca_tree.Precalculate();
        }

        int GetLabel(const int vertex) const {
            return label_[vertex];
        }

        // Transforms a node into a red vertex.
        void UpdateVertex(const int vertex) {
            int temp_vertex = vertex;
            while (temp_vertex != -1) {
                answer_[temp_vertex] = min(answer_[temp_vertex],
                                           lca_tree.GetDistance(temp_vertex, vertex));
                temp_vertex = father_centroid_[temp_vertex];
            }
        }

        // Gets the smallest distance from vertex to a red vertex.
        int GetSmallestDistance(const int vertex) {
            int min_distance = kInf;
            int temp_vertex = vertex;
            while (temp_vertex != -1) {
                if (answer_[temp_vertex] != kInf) {
                    int current_distance = answer_[temp_vertex]
                                           + lca_tree.GetDistance(temp_vertex, vertex);
                    min_distance = min(min_distance, current_distance);
                }
                temp_vertex = father_centroid_[temp_vertex];
            }

            return min_distance;
        }

    private:
        int Decompose(const int vertex, const int label) {
            ComputeSubtrees(vertex, -1);

            int centroid = GetCentroid(vertex, -1, subtree_[vertex]);
            label_[centroid] = label;

            for (int son : edges_[centroid]) {
                if (label_[son] == -1) {
                    int centroid_son = Decompose(son, label + 1);
                    centroid_tree_edges_[centroid].push_back(centroid_son);
                    father_centroid_[centroid_son] = centroid;
                }
            }

            return centroid;
        }

        void ComputeSubtrees(const int vertex, const int father) {
            subtree_[vertex] = 1;
            for (int son : edges_[vertex]) {
                if (son != father && label_[son] == -1) {
                    ComputeSubtrees(son, vertex);
                    subtree_[vertex] += subtree_[son];
                }
            }
        }

        int GetCentroid(const int vertex, const int father, const int total) {
            int biggest_son = -1;
            for (int son : edges_[vertex]) {
                if (son != father && label_[son] == -1) {
                    if (biggest_son == -1 || subtree_[son] > subtree_[biggest_son]) {
                        biggest_son = son;
                    }
                }
            }

            if ((biggest_son == -1 || subtree_[biggest_son] <= total / 2)
                    && total - subtree_[vertex] <= total / 2) {
                return vertex;
            }

            return GetCentroid(biggest_son, vertex, total);
        }

        const int kInf = numeric_limits<int>::max();

        const int num_vertices_;
        vector<vector<int>> edges_;
        vector<vector<int>> centroid_tree_edges_;
        vector<int> label_;
        vector<int> subtree_;
        vector<int> father_centroid_;
        vector<int> answer_;
        LCATree lca_tree;
};



int main() {
    cin.sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    CentroidDecompositionTree cdt(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        cdt.AddEdge(x, y);
    }

    cdt.DecomposeTree();

    cdt.UpdateVertex(1);
    for (; m; m--) {
        int op, x;
        cin >> op >> x;

        if (op == 1) {
            cdt.UpdateVertex(x);
        } else {
            cout << cdt.GetSmallestDistance(x) << '\n';
        }
    }

    return 0;
}
