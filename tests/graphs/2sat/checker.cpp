#include <bits/stdc++.h>

using namespace std;

bool EvaluateClause(pair<int, int> clause, const vector<int>& output) {
    int a = output[abs(clause.first)];
    int b = output[abs(clause.second)];

    if (clause.first < 0) {
        a ^= 1;
    }
    if (clause.second < 0) {
        b ^= 1;
    }

    return a | b;
}

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

    int ok;
    fok >> ok;

    if (ok == 1) {
        vector<int> output(n + 1);
        for (int i = 1; i <= n; i++) {
            int x;
            fout >> x;

            if (fout.fail() || (x < 0 || x > 1)) {
                InvalidOutput();
            }

            output[i] = x;
        }

        for (int i = 0; i < m; i++) {
            if (!EvaluateClause(input[i], output)) {
                WrongAnswer();
            }
        }

        Correct();
    } else {
        int output;
        fout >> output;

        if (fout.fail()) {
            InvalidOutput();
        } else if (output != -1) {
            WrongAnswer();
        }

        Correct();
    }

    return 0;
}
