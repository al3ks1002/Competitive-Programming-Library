#include <bits/stdc++.h>

using namespace std;

void InvalidOutput() {
    cout << "Invalid output\n";
    exit(1);
}

void WrongAnswer() {
    cout << "Wrong answer\n";
    exit(1);
}

void Correct() {
    cout << "Correct\n";
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        return 2;
    }

    ifstream fin(argv[1]);
    ifstream fout(argv[2]);
    ifstream fok(argv[3]);

    int n, m;
    fin >> n >> m;

    multiset<pair<int, int>> e;
    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        if (x > y) {
            swap(x, y);
        }
        e.insert({x, y});
    }

    int ok;
    fok >> ok;

    if (ok == 1) {
        vector<int> cycle;
        for (int i = 0; i <= m; i++) {
            int x;
            fout >> x;
            if (fout.fail()) {
                InvalidOutput();
            }
            if (x < 1 || x > n) {
                WrongAnswer();
            }
            cycle.push_back(x);
        }

        for (int i = 1; i <= m; i++) {
            pair<int, int> edge = {min(cycle[i - 1], cycle[i]), max(cycle[i - 1], cycle[i])};
            auto it = e.find(edge);
            if (it == e.end()) {
                WrongAnswer();
            }
            e.erase(it);
        }

        Correct();
    } else {
        int x;
        fout >> x;
        if (fout.fail()) {
            InvalidOutput();
        }
        if (x != -1) {
            WrongAnswer();
        }
        Correct();
    }

    return 0;
}
