#include <stdio.h>
#include <utility>
#include <vector>

using namespace std;

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

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    LCATree tree(n, 1);
    for (int i = 2; i <= n; i++) {
        int f;
        scanf("%d", &f);
        tree.AddEdge(f, i);
    }

    tree.Precalculate();

    for (; m; m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", tree.GetLCA(x, y));
    }

    return 0;
}
