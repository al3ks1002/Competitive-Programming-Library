#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class Gauss {
    public:
        Gauss(int num_equations, int num_unknowns, const vector<vector<double>>& system) :
            num_equations_(num_equations), num_unknowns_(num_unknowns), system_(system) {}

        vector<double> SolveSystem() {
            TransformToRowEchelonForm();
            return FindUnknowns();
        }

    private:
        const double kEps = 1e-10;
        int num_equations_;
        int num_unknowns_;
        vector<vector<double>> system_;

        void TransformToRowEchelonForm() {
            int i = 0;
            int j = 0;
            while (i < num_equations_ && j < num_unknowns_) {
                int non_zero_row = -1;
                for (int k = i; k < num_equations_; k++) {
                    if (NotZero(system_[k][j])) {
                        non_zero_row = k;
                        break;
                    }
                }

                if (non_zero_row == -1) {
                    j++;
                    continue;
                }

                if (non_zero_row != i) {
                    for (int l = 0; l <= num_unknowns_; l++) {
                        swap(system_[i][l], system_[non_zero_row][l]);
                    }
                }

                for (int l = j + 1; l <= num_unknowns_; l++) {
                    system_[i][l] /= system_[i][j];
                }
                system_[i][j] = 1.0;

                for (int k = i + 1; k < num_equations_; k++) {
                    for (int l = j + 1; l <= num_unknowns_; l++) {
                        system_[k][l] -= system_[k][j] * system_[i][l];
                    }

                    system_[k][j] = 0.0;
                }

                i++;
                j++;
            }
        }

        vector<double> FindUnknowns() {
            vector<double> unknowns(num_unknowns_, 0.0);

            for (int i = num_equations_ - 1; i >= 0; i--) {
                int unknown_found = -1;
                for (int j = 0; j <= num_unknowns_; j++) {
                    if (NotZero(system_[i][j])) {
                        unknown_found = j;
                        break;
                    }
                }

                if (unknown_found == -1) {
                    continue;
                }

                if (unknown_found == num_unknowns_) {
                    return vector<double>();
                }

                unknowns[unknown_found] = system_[i][num_unknowns_];
                for (int j = unknown_found + 1; j < num_unknowns_; j++) {
                    unknowns[unknown_found] -= unknowns[j] * system_[i][j];
                }
            }

            return unknowns;
        }

        bool NotZero(double x) {
            return fabs(x) >= kEps;
        }
};

int main() {
    cin.sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<vector<double>> system(n, vector<double>(m + 1, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            cin >> system[i][j];
        }
    }

    Gauss gauss(n, m, system);
    vector<double> ans = gauss.SolveSystem();
    if (ans.empty()) {
        cout << "Imposibil\n";
    } else {
        for (auto it : ans) {
            cout << fixed << setprecision(10) << it<< " ";
        }
    }

    return 0;
}
