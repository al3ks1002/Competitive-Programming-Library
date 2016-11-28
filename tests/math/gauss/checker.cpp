#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const double kEps = 1e-3;

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

double Equal(double x, double y) {
    return fabs(x - y) <= kEps;
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
    vector<vector<double>> system(n, vector<double>(m + 1, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            fin >> system[i][j];
        }
    }

    bool ok;
    fok >> ok;

    if (ok) {
        vector<double> answer(m);
        for (int i = 0; i < m; i++) {
            fout >> answer[i];
            if (fout.fail()) {
                InvalidOutput();
            }
        }

        for (int i = 0; i < n; i++) {
            double current = 0;
            for (int j = 0; j < m; j++) {
                current += system[i][j] * answer[j];
            }
            if (!Equal(current, system[i][m])) {
                WrongAnswer();
            }
        }

        Correct();
    } else {
        string answer;
        fout >> answer;
        if (fout.fail()) {
            InvalidOutput();
        }
        if (answer.compare("Imposibil")) {
            WrongAnswer();
        }
        Correct();
    }

    return 0;
}
