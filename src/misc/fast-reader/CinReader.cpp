#include <iostream>

using namespace std;

int main() {
    cin.sync_with_stdio(false);

    int n;
    cin >> n;

    int sol = 0;
    for (; n; n--) {
        int x;
        cin >> x;
        sol ^= x;
    }

    cout << sol << '\n';

    return 0;
}
