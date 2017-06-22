#include <stdio.h>
#include <vector>

using namespace std;

class DisjointSet {
 public:
  explicit DisjointSet(const int size) : size_(size + 1) {
    father_.resize(size_);
    rank_.resize(size_);
    for (int i = 0; i < size_; i++) {
      father_[i] = i;
      rank_[i] = 1;
    }
  }

  int Find(const int x) {
    if (father_[x] != x) {
      father_[x] = Find(father_[x]);
    }
    return father_[x];
  }

  void SetFather(const int x, const int y) {
    father_[x] = y;
  }

  // x and y must be roots
  void Unite(const int x, const int y) {
    if (rank_[x] < rank_[y]) {
      father_[x] = y;
    } else {
      father_[y] = x;
      if (rank_[x] == rank_[y]) {
        rank_[x]++;
      }
    }
  }

 private:
  const int size_;
  vector<int> father_;
  vector<int> rank_;
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  DisjointSet ds(n);
  for (; m; m--) {
    int op, x, y;
    scanf("%d%d%d", &op, &x, &y);

    if (op == 1) {
      int fx = ds.Find(x);
      int fy = ds.Find(y);
      if (fx != fy) {
        ds.Unite(fx, fy);
      }
    } else {
      printf("%s\n", ds.Find(x) == ds.Find(y) ? "YES" : "NO");
    }
  }

  return 0;
}
