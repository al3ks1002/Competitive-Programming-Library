#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class MaxMatchingBipartiteGraph {
    public:
        MaxMatchingBipartiteGraph(int num_vertices_left_, int num_vertices_right_) :
            num_vertices_left_(num_vertices_left_),
            num_vertices_right_(num_vertices_right_) {
            edges_.resize(num_vertices_left_ + 1);
            visited_.resize(num_vertices_left_ + 1, 0);
            match_for_left_.resize(num_vertices_left_ + 1, 0);
            match_for_right_.resize(num_vertices_right_ + 1, 0);
        }

        void AddEdge(int from, int to) {
            edges_[from].push_back(to);
        }

        int GetMaximumMatching() {
            int matching = 0;
            bool ok = 1;
            while (ok) {
                ok = 0;
                fill(visited_.begin(), visited_.end(), 0);
                for (int i = 1; i <= num_vertices_left_; i++) {
                    if (!match_for_left_[i] && PairUp(i)) {
                        ok = 1;
                        matching++;
                    }
                }
            }
            return matching;
        }

        int GetMatchForLeft(int vertex) {
            return match_for_left_[vertex];
        }

        int GetMatchForRight(int vertex) {
            return match_for_right_[vertex];
        }

    private:
        int num_vertices_left_;
        int num_vertices_right_;
        vector<vector<int>> edges_;
        vector<bool> visited_;
        vector<int> match_for_left_;
        vector<int> match_for_right_;

        bool PairUp(int vertex) {
            if (visited_[vertex]) {
                return 0;
            }
            visited_[vertex] = 1;

            for (auto it : edges_[vertex])
                if (!match_for_right_[it]) {
                    match_for_left_[vertex] = it;
                    match_for_right_[it] = vertex;
                    return 1;
                }

            for (auto it : edges_[vertex])
                if (PairUp(match_for_right_[it])) {
                    match_for_left_[vertex] = it;
                    match_for_right_[it] = vertex;
                    return 1;
                }

            return 0;
        }
};

int main() {
    cin.sync_with_stdio(false);

    int n, m, e;
    cin >> n >> m >> e;

    MaxMatchingBipartiteGraph graph(n, m);

    for (; e; e--) {
        int x, y;
        cin >> x >> y;
        graph.AddEdge(x, y);
    }

    cout << graph.GetMaximumMatching() << '\n';

    return 0;
}