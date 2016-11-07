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

    int q;
    set<int> s;
    scanf("%d\n", &q);

    for (; q; q--) {
        char operation;
        int value;
        scanf("%c %d\n", &operation, &value);

        if (operation == 'I') {
            s.insert(value);
        } else if (operation == 'D') {
            auto it = s.find(value);
            if (it != s.end()) {
                s.erase(it);
            }
        } else if (operation == 'K') {
            if (value > (int)s.size()) {
                printf("invalid\n");
            } else {
                int cnt = 0;
                for (auto it : s) {
                    if (++cnt == value) {
                        printf("%d\n", it);
                        break;
                    }
                }
            }
        } else {
            int cnt = 0;
            for (auto it : s) {
                if (it < value) {
                    cnt++;
                }
            }
            printf("%d\n", cnt);
        }
    }

    return 0;
}
