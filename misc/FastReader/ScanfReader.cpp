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

    int sol = 0;
    for (; n; n--) {
        int x;
        scanf("%d", &x);
        sol ^= x;
    }

    printf("%d\n", sol);

    return 0;
}
