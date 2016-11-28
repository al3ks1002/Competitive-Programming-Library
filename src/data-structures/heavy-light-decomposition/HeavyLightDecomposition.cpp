#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Class that represents a segment tree that supports
// update operation only on a value (not an interval).
template<typename T>
class SegmentTree {
    public:
        explicit SegmentTree(const int size) : size_(size) {
            segment_.resize(4 * size + 5);
        }

        // The array must be indexed from 1
        template<typename Array>
        SegmentTree(const int size, const Array& array) : size_(size) {
            segment_.resize(4 * size + 5);
            Build(1, 1, size, array);
        }

        void Update(const int position, const T value) {
            return Update(1, 1, size_, position, value);
        }

        T Query(const int left, const int right) const {
            return Query(1, 1, size_, left, right);
        }

    private:
        template<typename Array>
        void Build(const int node, const int left, const int right, const Array& v) {
            if (left == right) {
                segment_[node] = v[left];
                return;
            }

            int middle = (left + right) / 2;
            int left_son = 2 * node;
            int right_son = 2 * node + 1;

            Build(left_son, left, middle, v);
            Build(right_son, middle + 1, right, v);

            segment_[node] = TreeFunction(segment_[left_son], segment_[right_son]);
        }

        void Update(const int node, const int left, const int right,
                    const int position, const T value) {
            if (left == right) {
                segment_[node] = value;
                return;
            }

            int middle = (left + right) / 2;
            int left_son = 2 * node;
            int right_son = 2 * node + 1;

            if (position <= middle) {
                Update(left_son, left, middle, position, value);
            } else {
                Update(right_son, middle + 1, right, position, value);
            }

            segment_[node] = TreeFunction(segment_[left_son], segment_[right_son]);
        }

        T Query(const int node, const int left, const int right, const int a, const int b) const {
            if (left >= a && right <= b) {
                return segment_[node];
            }

            int middle = (left + right) / 2;
            int left_son = 2 * node;
            int right_son = 2 * node + 1;

            T x = 0;
            T y = 0;

            if (a <= middle) {
                x = Query(left_son, left, middle, a, b);
            }
            if (b > middle) {
                y = Query(right_son, middle + 1, right, a, b);
            }

            return TreeFunction(x, y);
        }

        T TreeFunction(const T x, const T y) const {
            return (x > y) ? x : y;
        }

        vector<T> segment_;
        const int size_;
};

template<class T>
class HLDTree {
    public:
        // values vector must be indexed from 1.
        HLDTree(const int num_vertices, const vector<T>& values, const int root) :
            num_vertices_(num_vertices), values_(values), root_(root) {
            edges_.resize(num_vertices + 1);
        }

        HLDTree(const int num_vertices, const vector<T>& values) :
            HLDTree(num_vertices, values, 1) {}

        void AddEdge(const int from, const int to) {
            edges_[from].push_back(to);
            edges_[to].push_back(from);
        }

        // Must be called first.
        void Prepare() {
            subtree_.resize(num_vertices_ + 1);
            level_.resize(num_vertices_ + 1);
            father_.resize(num_vertices_ + 1);
            chain_.resize(num_vertices_ + 1);
            where_.resize(num_vertices_ + 1);

            DFS(root_, -1);

            vector<T> aux;
            for (int i = 0; i < (int)path_.size(); i++) {
                reverse(path_[i].begin() + 1, path_[i].end());

                aux.clear();
                aux.push_back(-1);  // dummy
                for (int j = 1; j < (int)path_[i].size(); j++) {
                    aux.push_back(values_[path_[i][j]]);
                }
                segment_tree_.push_back(SegmentTree<int>(path_[i].size(), aux));
            }

            for (int i = 1; i <= num_vertices_; i++) {
                where_[i] = path_[chain_[i]].size() - where_[i];
            }
        }

        void Update(const int vertex, const T value) {
            int position = where_[vertex];
            segment_tree_[chain_[vertex]].Update(position, value);
        }

        T GetMax(int x, int y) const {
            T max_value = 0;
            while (1) {
                if (chain_[x] == chain_[y]) {
                    int a = min(where_[x], where_[y]);
                    int b = max(where_[x], where_[y]);
                    max_value = max(max_value, segment_tree_[chain_[x]].Query(a, b));
                    break;
                }

                if (level_[path_[chain_[x]][1]] < level_[path_[chain_[y]][1]]) {
                    swap(x, y);
                }
                int a = 1;
                int b = where_[x];
                max_value = max(max_value, segment_tree_[chain_[x]].Query(a, b));
                x = father_[path_[chain_[x]][1]];
            }
            return max_value;
        }

    private:
        const int root_;
        const int num_vertices_;
        vector<T> values_;
        vector<int> subtree_;
        vector<int> level_;
        vector<int> father_;
        vector<int> chain_;
        vector<int> where_;
        vector<vector<int>> edges_;
        vector<vector<int>> path_;
        vector<SegmentTree<T>> segment_tree_;

        void DFS(const int vertex, const int father) {
            subtree_[vertex] = 1;

            for (int son : edges_[vertex])
                if (son != father) {
                    level_[son] = level_[vertex] + 1;
                    father_[son] = vertex;
                    DFS(son, vertex);
                    subtree_[vertex] += subtree_[son];
                }

            if (edges_[vertex].size() == 1 && vertex != root_) {
                chain_[vertex] = path_.size();
                path_.push_back(vector<int>());
                path_.back().push_back(-1);  // dummy
                path_.back().push_back(vertex);
                where_[vertex] = 1;
                return;
            }

            int heaviest_son = 0;
            for (auto son : edges_[vertex])
                if (son != father && subtree_[son] > subtree_[heaviest_son]) {
                    heaviest_son = son;
                }

            chain_[vertex] = chain_[heaviest_son];
            path_[chain_[vertex]].push_back(vertex);
            where_[vertex] = path_[chain_[vertex]].size() - 1;
        }
};

int main() {
    cin.sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<int> cost(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }

    HLDTree<int> hld(n, cost);

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        hld.AddEdge(x, y);
    }

    hld.Prepare();

    for (; m; m--) {
        int op;
        cin >> op;

        if (op == 0) {
            int vertex, value;
            cin >> vertex >> value;
            hld.Update(vertex, value);
        } else {
            int x, y;
            cin >> x >> y;
            cout << hld.GetMax(x, y) << '\n';
        }
    }

    return 0;
}
