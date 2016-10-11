#include <bits/stdc++.h>

using namespace std;

template<typename T>
class LongestCommonSubsequence {
    public:
        // Constructor takes 0 indexed vectors.
        LongestCommonSubsequence(const vector<T>& a, const vector<T>& b) {
            n_ = a.size();
            m_ = b.size();
            a_.resize(n_ + 1);
            for (int i = 0; i < n_; i++) {
                a_[i + 1] = a[i];
            }

            b_.resize(m_ + 1);
            for (int i = 0; i < m_; i++) {
                b_[i + 1] = b[i];
            }

            dp_.resize(n_ + 1);
            for (int i = 0; i <= n_; i++) {
                dp_[i].resize(m_ + 1);
            }
        }

        int FindLCS() {
            for (int i = 1; i <= n_; i++)
                for (int j = 1; j <= m_; j++) {
                    if (a_[i] == b_[j]) {
                        dp_[i][j] = dp_[i - 1][j - 1] + 1;
                    } else {
                        dp_[i][j] = max(dp_[i - 1][j], dp_[i][j - 1]);
                    }
                }

            return dp_[n_][m_];
        }

        vector<int> FindActualLCS() {
            vector<int> lcs;
            for (int i = n_, j = m_; i && j;) {
                if (a_[i] == b_[j]) {
                    lcs.push_back(a_[i]);
                    i--;
                    j--;
                } else if (dp_[i][j] == dp_[i - 1][j]) {
                    i--;
                } else {
                    j--;
                }
            }

            reverse(lcs.begin(), lcs.end());
            return lcs;
        }

    private:
        int n_;
        int m_;
        vector<T> a_;
        vector<T> b_;
        vector<vector<int>> dp_;
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    vector<int> b(m);
    for (int i = 0; i < m; i++)
        scanf("%d", &b[i]);

    LongestCommonSubsequence<int> lcs(a, b);
    printf("%d\n", lcs.FindLCS());

    return 0;
}
