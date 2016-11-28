#include <stdio.h>
#include <set>

using namespace std;

int main() {
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
