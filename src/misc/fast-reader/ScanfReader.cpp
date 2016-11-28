#include <stdio.h>

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
