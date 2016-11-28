#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const double kEps = 1e-6;

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

bool Equal(double x, double y) {
    return fabs(x - y) <= kEps;
}

bool Equal(pair<double, double> x, pair<double, double> y) {
    return Equal(x.first, y.first) && Equal(x.second, y.second);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        return 2;
    }

    ifstream fin(argv[1]);
    ifstream fout(argv[2]);
    ifstream fok(argv[3]);

    int n;
    fok >> n;
    vector<pair<double, double>> ch;
    for (int i = 0; i < n; i++) {
        double x, y;
        fok >> x >> y;
        ch.emplace_back(x, y);
    }

    int user_n;
    fout >> user_n;
    if (fout.fail()) {
        InvalidOutput();
    }
    if (user_n != n) {
        WrongAnswer();
    }

    vector<pair<double, double>> user_ch;
    for (int i = 0; i < n; i++) {
        double x, y;
        fout >> x >> y;
        if (fout.fail()) {
            InvalidOutput();
        }
        user_ch.emplace_back(x, y);
    }
    for (int i = 0; i < n; i++) {
        user_ch.push_back(user_ch[i]);
    }

    for (int i = 0; i < n; i++) {
        if (Equal(user_ch[i], ch[0])) {
            for (int j = i, k = 0; k < n; j++, k++) {
                if (!Equal(user_ch[j], ch[k])) {
                    WrongAnswer();
                }
            }
            Correct();
        }
    }

    return 0;
}
