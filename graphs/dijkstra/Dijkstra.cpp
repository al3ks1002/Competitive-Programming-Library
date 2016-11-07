#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

template<class T>
class DijkstraGraph {
    public:
        DijkstraGraph(int num_vertices) : num_vertices_(num_vertices) {
            edges_.resize(num_vertices + 1);
        }

        void AddEdge(int from, int to, T cost) {
            edges_[from].push_back({to, cost});
        }

        vector<T> GetDistances(int source) {
            vector<T> distance_(num_vertices_ + 1, kMaxInf);
            vector<bool> visited_(num_vertices_ + 1, 0);
            priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;

            distance_[source] = 0;
            q.push({0, source});


            while (!q.empty()) {
                int x = q.top().second;
                q.pop();

                if (visited_[x]) {
                    continue;
                }
                visited_[x] = 1;

                for (auto it : edges_[x]) {
                    int y = it.first;
                    T cost = it.second;
                    if (distance_[x] + cost < distance_[y]) {
                        distance_[y] = distance_[x] + cost;
                        q.push({distance_[y], y});
                    }
                }
            }

            for (int i = 1; i <= num_vertices_; i++) {
                if (distance_[i] == kMaxInf) {
                    distance_[i] = -1;
                }
            }

            return distance_;
        }

    private:
        static const int kMaxInf = numeric_limits<T>::max();
        const int num_vertices_;
        vector<vector<pair<int, T>>> edges_;
};

int main() {
    cin.sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    DijkstraGraph<int> dij(n);
    for (; m; m--) {
        int x, y, z;
        cin >> x >> y >> z;
        dij.AddEdge(x, y, z);
    }

    vector<int> ans = dij.GetDistances(1);
    for (int i = 2; i <= n; i++) {
        if (ans[i] == -1) {
            ans[i] = 0;
        }
        cout << ans[i] << " ";
    }

    return 0;
}
