#include <bits/stdc++.h>

using namespace std;

// Returns 1 on fail.
bool CheckArgument(const ifstream& stream, int arg) {
    return stream.fail() || (arg < 0 || arg > 1);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        exit(2);
    }

    ifstream fin(argv[1]);
    ifstream fout(argv[2]);
    ifstream fok(argv[3]);

    int n, m;
    fin >> n >> m;

    vector<pair<int, int>> input;
    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        input.emplace_back(x, y);
    }

    vector<int> output;
    for (int i = 0; i < n; i++) {
        int x;
        fout >> x;
        if (CheckArgument(fout, x)) {
            cout << "Invalid output!\n";
            exit(1);
        }
    }

    return 0;
}
