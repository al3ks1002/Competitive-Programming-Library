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
    int n;
    scanf("%d", &n);

    ll sol = 0;
    for (; n; n--) {
        ll x;
        scanf("%lld", &x);
        sol ^= x;
    }

    printf("%lld\n", sol);

    return 0;
}
