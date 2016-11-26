#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

template<class T>
class Set {
    public:
        Set(const vector<T>& set) : set_(set) {
            num_numbers_ = set.size();
            log_ = FindLog(set);
        }

        int FindLog(const vector<T>& set) {
            int log = 1;

            for (T x : set) {
                T number = x;
                int curr_log = 0;

                while (number) {
                    curr_log++;
                    number /= 2;
                }

                log = max(log, curr_log);
            }

            return log;
        }

        vector<T> GetXorBasis() {
            if (basis_.empty()) {
                FindXorBasis();
            }
            return basis_;
        }

        T GetMaxXorSubset() {
            if (basis_.empty()) {
                FindXorBasis();
            }

            T max_xor = 0;
            for (T number : basis_) {
                max_xor = max(max_xor, max_xor ^ number);
            }

            return max_xor;
        }

    private:
        int num_numbers_;
        int log_;
        vector<T> set_;
        vector<T> basis_;

        void FindXorBasis() {
            vector<T> set_copy(set_);
            int i = 0;
            int j = log_;
            while (i < num_numbers_ && j >= 0) {
                int where = -1;
                for (int k = i; k < num_numbers_; k++) {
                    if ((1LL << j) & set_copy[k]) {
                        where = k;
                        break;
                    }
                }

                if (where == -1) {
                    j--;
                    continue;
                }

                swap(set_copy[i], set_copy[where]);

                for (int k = i + 1; k < num_numbers_; k++) {
                    if ((1LL << j) & set_copy[k]) {
                        set_copy[k] ^= set_copy[i];
                    }
                }

                i++;
                j--;
            }

            for (T number : set_copy) {
                if (number) {
                    basis_.push_back(number);
                }
            }
        }
};

int main() {
    cin.sync_with_stdio(false);

    int n;
    cin >> n;

    vector<long long> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    Set<long long> s(v);
    long long ans = s.GetMaxXorSubset();
    cout << ans << '\n';

    return 0;
}
