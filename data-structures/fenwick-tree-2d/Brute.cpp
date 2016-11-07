#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

#define ll int64_t
#define ld long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<ld, ld>
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second

const int kMaxN = 1005;

ll v[kMaxN][kMaxN];

int main() {
    cin.sync_with_stdio(false);

    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &v[i][j]);
        }
    }

    for (; q; q--) {
        int op;
        scanf("%d", &op);

        if (op == 0) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            long long sum = 0;
            for (int i = a; i <= c; i++) {
                for (int j = b; j <= d; j++) {
                    sum += v[i][j];
                }
            }
            printf("%lld\n", sum);
        } else {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            v[a][b] += c;
        }
    }

    return 0;
}
