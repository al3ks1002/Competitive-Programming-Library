#include <iostream>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

template<class T>
class DijkstraGraph {
    public:
        explicit DijkstraGraph(int num_vertices) : num_vertices_(num_vertices) {
            edges_.resize(num_vertices + 1);
        }

        void AddEdge(const int from, const int to, const T cost) {
            edges_[from].push_back({to, cost});
        }

        vector<T> GetDistances(const int source) {
            vector<T> distance(num_vertices_ + 1, kMaxInf);
            vector<bool> visited(num_vertices_ + 1, 0);
            priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> queue;

            distance[source] = 0;
            queue.push({0, source});

            while (!queue.empty()) {
                int x = queue.top().second;
                queue.pop();

                if (visited[x]) {
                    continue;
                }
                visited[x] = 1;

                for (auto it : edges_[x]) {
                    int y = it.first;
                    T cost = it.second;
                    if (distance[x] + cost < distance[y]) {
                        distance[y] = distance[x] + cost;
                        queue.push({distance[y], y});
                    }
                }
            }

            for (int i = 1; i <= num_vertices_; i++) {
                if (distance[i] == kMaxInf) {
                    distance[i] = -1;
                }
            }

            return distance;
        }

    private:
        static const T kMaxInf = numeric_limits<T>::max();
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
