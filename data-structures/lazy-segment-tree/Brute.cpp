#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<ld, ld>
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second

int main() {
    cin.sync_with_stdio(false);

    int n, q;
    scanf("%d%d", &n, &q);
    vector<ll> v(n + 1);

    for (; q; q--) {
        int op;
        scanf("%d", &op);
        if (op == 0) {
            int x, y, val;
            scanf("%d%d%d", &x, &y, &val);
            for (int i = x; i <= y; i++) {
                v[i] += val;
            }
        } else {
            int x, y;
            scanf("%d%d", &x, &y);
            ll sum = 0;
            for (int i = x; i <= y; i++) {
                sum += v[i];
            }
            printf("%lld\n", sum);
        }
    }

    return 0;
}
