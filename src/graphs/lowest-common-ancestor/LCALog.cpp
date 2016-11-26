#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class LCATree {
    public:
        LCATree(int num_vertices, int root, const vector<int>& father) :
            num_vertices_(num_vertices),
            root_(root) {
            sons_.resize(num_vertices_ + 1);
            father_.resize(GetLog(num_vertices));
            for (int i = 0; i < (int)father_.size(); i++) {
                father_[i].resize(num_vertices + 1, 0);
            }

            for (int i = 2; i <= num_vertices; i++) {
                father_[0][i] = father[i - 2];
                sons_[father[i - 2]].push_back(i);
            }

            Precalculate();
        }

        void AddEdge(int father, int son) {
            sons_[father].push_back(son);
            father_[0][son] = father;
            level_[son] = level_[father] + 1;
            for (int i = 1; i < (int)father_.size(); i++) {
                father_[i][son] = father_[i - 1][father_[i - 1][son]];
            }
        }

        int GetLCA(int x, int y) {
            if (level_[x] > level_[y]) {
                swap(x, y);
            }

            int diff = level_[y] - level_[x];
            for (int i = 0; (1 << i) <= diff; i++) {
                if ((1 << i) & diff) {
                    y = father_[i][y];
                }
            }

            if (x == y) {
                return x;
            }

            for (int i = (int)father_.size() - 1; i >= 0; i--) {
                if (father_[i][x] != father_[i][y]) {
                    x = father_[i][x];
                    y = father_[i][y];
                }
            }

            return father_[0][x];
        }

    private:
        int num_vertices_;
        int root_;
        vector<vector<int>> sons_;
        vector<vector<int>> father_;
        vector<int> level_;

        void DFS(int vertex) {
            for (auto son : sons_[vertex]) {
                level_[son] = level_[vertex] + 1;
                DFS(son);
            }
        }

        int GetLog(int x) {
            int log = 0;
            while ((1 << log) <= x) {
                log++;
            }
            return log;
        }

        void Precalculate() {
            for (int i = 1; i < (int)father_.size(); i++) {
                for (int j = 1; j <= num_vertices_; j++) {
                    father_[i][j] = father_[i - 1][father_[i - 1][j]];
                }
            }

            level_.resize(num_vertices_ + 1, 0);
            DFS(root_);
        }
};

int main() {
    cin.sync_with_stdio(false);

    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> father;
    for (int i = 2; i <= n; i++) {
        int f;
        scanf("%d", &f);
        father.push_back(f);
    }

    LCATree tree(n, 1, father);

    for (; m; m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", tree.GetLCA(x, y));
    }

    return 0;
}
