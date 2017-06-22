#include <stdio.h>
#include <vector>

using namespace std;

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  vector<long long> v(n + 1);

  for (; q; q--) {
    int op;
    scanf("%d", &op);
    if (op == 0) {
      int x, y, val;
      scanf("%d%d%d", &x, &y, &val);
      for (int i = x; i <= y; i++) {
        v[i] += val;
      }
    } else {
      int x, y;
      scanf("%d%d", &x, &y);
      long long sum = 0;
      for (int i = x; i <= y; i++) {
        sum += v[i];
      }
      printf("%lld\n", sum);
    }
  }

  return 0;
}
