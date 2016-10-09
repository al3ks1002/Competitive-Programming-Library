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

int main() {
    cin.sync_with_stdio(false);

    ofstream cout("test11.in");

    int n = 1e4;
    int m = 1e6;

    cout << n << " " << m << '\n';
    for (int i = 0; i < m; i++) {
        cout << (rand() & 1) + 1 << " " << rand() % n + 1 << " " << rand() % n + 1 << '\n';
    }

    return 0;
}
