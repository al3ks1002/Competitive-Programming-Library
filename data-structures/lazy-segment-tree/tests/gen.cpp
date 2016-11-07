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

const int kMaxN = 1e5;
const int kMaxQ = 1e5;
const int kMaxVal = 1e7;

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

        int n, q;
        if (i < 7) {
            n = rand() % kMaxN + 1;
            q = rand() % kMaxQ + 1;
        } else {
            n = kMaxN;
            q = kMaxQ;
        }

        cout << n << " " << q << '\n';

        for (; q; q--) {
            int op = rand() % 2;
            cout << op << " ";
            if (op == 0) { // query
                int x = rand() % n + 1;
                int y = rand() % n + 1;
                int val = rand() % kMaxVal + 1;
                if (x > y) {
                    swap(x, y);
                }
                cout << x << " " << y << " " << val << '\n';
            } else {
                int x = rand() % n + 1;
                int y = rand() % n + 1;
                if (x > y) {
                    swap(x, y);
                }
                cout << x << " " << y << '\n';
            }
        }
    }

    return 0;
}
