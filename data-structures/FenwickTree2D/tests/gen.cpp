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

const int kMaxN = 1e3;
const int kMaxQ = 1e5;
const int kMaxVal = 1e9;

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

        int n, m, q;
        if (i < 7) {
            n = rand() % kMaxN + 1;
            m = rand() % kMaxN + 1;
            q = rand() % kMaxQ + 1;
        } else {
            n = kMaxN;
            m = kMaxN;
            q = kMaxQ;
        }

        cout << n << " " << m << " " << q << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << rand() % kMaxVal + 1 << " ";
            }
            cout << '\n';
        }

        for (; q; q--) {
            int op = rand() % 2;
            cout << op << " ";
            if (op == 0) { // query
                int a = rand() % n + 1;
                int b = rand() % n + 1;
                int c = rand() % m + 1;
                int d = rand() % m + 1;
                if (a > b) {
                    swap(a, b);
                }
                if (c > d) {
                    swap(c, d);
                }
                cout << a << " " << c << " " << b << " " << d << '\n';
            } else {
                int x = rand() % n + 1;
                int y = rand() % m + 1;
                int val = rand() % kMaxVal + 1;
                cout << x << " " << y << " " << val << '\n';
            }
        }
    }


    return 0;
}
