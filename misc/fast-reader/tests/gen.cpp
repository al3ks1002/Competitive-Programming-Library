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

const int kMaxN = 2e6;

int main() {
    srand(time(0));
    cin.sync_with_stdio(false);

    for (int i = 0; i < 10; i++) {
        string test = "test";
        stringstream mlc;
        string in = ".in";
        mlc << test << i << in;
        string str = mlc.str();
        ofstream cout(str);

        int n;
        if (i < 9) {
            n = kMaxN / 4;
        } else {
            n = kMaxN;
        }

        cout << n << '\n';
        for (; n; n--) {
            cout << rand() << '\n';
        }
    }


    return 0;
}