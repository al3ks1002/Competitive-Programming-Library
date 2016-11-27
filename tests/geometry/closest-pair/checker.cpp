#include <bits/stdc++.h>

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

int main(int argc, char* argv[]) {
    if (argc != 4) {
        return 2;
    }

    ifstream fin(argv[1]);
    ifstream fout(argv[2]);
    ifstream fok(argv[3]);

    double user_answer;
    fout >> user_answer;

    if (fout.fail()) {
        InvalidOutput();
    }

    double answer;
    fok >> answer;

    if (Equal(user_answer, answer)) {
        Correct();
    }

    WrongAnswer();

    return 0;
}
