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

        int q;
        if (i < 7) {
            q = rand() % kMaxQ + 1;
        } else {
            q = kMaxQ;
        }

        cout << q << '\n';

        char ops[] = {'I', 'D', 'C', 'K'};
        for (; q; q--) {
            char op = ops[rand() % 4];
            cout << op << " ";
            if (op != 'K') {
                int x = rand() % kMaxVal;
                int y = rand() % 2;
                if (y) {
                    x = -x;
                }
                cout << x << '\n';
            } else {
                int x = rand() % kMaxVal;
                cout << x << '\n';
            }
        }
    }

    return 0;
}
