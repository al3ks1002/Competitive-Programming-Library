#include <bits/stdc++.h>

using namespace std;

//Class that represents a 2D Fenwick tree.
template<class T>
class FenwickTree2D {
    public:
        FenwickTree2D(int rows, int columns) : rows_(rows), columns_(columns) {
            fenwick_.resize(rows + 1);
            for (int i = 1; i <= rows; i++) {
                fenwick_[i].resize(columns + 1, 0);
            }
        }

        void Update(int x, int y, T value) {
            for (int i = x; i <= rows_; i += Lsb(i)) {
                for (int j = y; j <= columns_; j += Lsb(j)) {
                    fenwick_[i][j] += value;
                }
            }
        }

        T Sum(int a, int b, int c, int d) {
            return Query(c, d) - Query(c, b - 1)
                   - Query(a - 1, d) + Query(a - 1, b - 1);
        }

    private:
        const int rows_;
        const int columns_;
        vector<vector<T>> fenwick_;

        int Lsb(int x) const {
            return x & (-x);
        }

        T Query(int x, int y) {
            if (x <= 0 || y <= 0) {
                return 0;
            }

            T result = 0;
            for (int i = x; i; i -= Lsb(i)) {
                for (int j = y; j; j -= Lsb(j)) {
                    result += fenwick_[i][j];
                }
            }
            return result;
        }
};

int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    FenwickTree2D<long long> fenwick(n, m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            fenwick.Update(i, j, x);
        }
    }

    for (; q; q--) {
        int op;
        scanf("%d", &op);

        if (op == 0) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            printf("%lld\n", fenwick.Sum(a, b, c, d));
        } else {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            fenwick.Update(a, b, c);
        }
    }
    return 0;
}
