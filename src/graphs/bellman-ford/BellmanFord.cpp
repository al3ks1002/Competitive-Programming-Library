#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

template<class T>
class BellmanFordGraph {
    public:
        BellmanFordGraph(int num_vertices) : num_vertices_(num_vertices) {
            edges_.resize(num_vertices + 1);
        }

        void AddEdge(int from, int to, T cost) {
            edges_[from].push_back({to, cost});
        }

        // Returns empty vector if the graph has a negative cycle.
        vector<T> GetDistances(int source) {
            vector<T> distance(num_vertices_ + 1, kMaxInf);
            vector<bool> in_queue(num_vertices_ + 1, false);
            vector<int> count(num_vertices_ + 1, 0);
            queue<int> queue;

            distance[source] = 0;
            in_queue[source] = true;
            queue.push(source);

            while (!queue.empty()) {
                int x = queue.front();
                in_queue[x] = false;
                queue.pop();

                count[x]++;
                if (count[x] > num_vertices_) {
                    return vector<T>();
                }

                for (auto it : edges_[x]) {
                    int y = it.first;
                    T cost = it.second;
                    if (distance[x] + cost < distance[y]) {
                        distance[y] = distance[x] + cost;
                        if (!in_queue[y]) {
                            in_queue[y] = true;
                            queue.push(y);
                        }
                    }
                }
            }

            return distance;
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

    BellmanFordGraph<int> bf(n);
    for (; m; m--) {
        int x, y, z;
        cin >> x >> y >> z;
        bf.AddEdge(x, y, z);
    }

    vector<int> ans = bf.GetDistances(1);
    if (ans.empty()) {
        cout << "Ciclu negativ!\n";
    } else {
        for (int i = 2; i <= n; i++) {
            cout << ans[i] << " ";
        }
    }

    return 0;
}
