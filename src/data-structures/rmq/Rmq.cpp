#include <stdio.h>
#include <vector>

using namespace std;

template<class T>
class Rmq {
 public:
  Rmq() {}

  // Must be indexed from 0.
  template<typename Array>
  Rmq(const int size, const Array& array, const vector<int>& key) :
    size_(size), lg_max_(GetLog(size)), key_(key) {
    rmq_.resize(lg_max_);
    for (int i = 0; i < (int)rmq_.size(); i++) {
      rmq_[i].resize(size_);
    }
    PrecalculateLog();
    Build(array);
  }

  template<typename Array>
  Rmq(const int size, const Array& array) : Rmq(size, array, vector<int>()) {}

  T Get(const int x, const int y) const {
    int lg = lg_[y - x + 1];
    return GetMin(rmq_[lg][x], rmq_[lg][y - (1 << lg) + 1]);
  }

 private:
  int GetLog(int size) const {
    int lg = 1;
    while (size) {
      lg++;
      size /= 2;
    }
    return lg;
  }

  void PrecalculateLog() {
    lg_.resize(size_ + 1);
    lg_[1] = 0;
    for (int i = 2; i <= size_; i++) {
      lg_[i] = lg_[i / 2] + 1;
    }
  }

  template<typename Array>
  void Build(const Array& array) {
    for (int i = 0; i < size_; i++) {
      rmq_[0][i] = array[i];
    }
    for (int i = 1, p = 2; p <= size_; i++, p *= 2)
      for (int j = 0; j + p - 1 < size_; j++) {
        rmq_[i][j] = GetMin(rmq_[i - 1][j], rmq_[i - 1][j + p / 2]);
      }
  }

  int GetMin(const int x, const int y) const {
    if (Key(x) < Key(y)) {
      return x;
    }
    return y;
  }

  int Key(const int x) const {
    if (key_.empty()) {
      return x;
    }
    return key_[x];
  }

  const int size_;
  const int lg_max_;
  vector<int> lg_;
  vector<vector<T>> rmq_;
  vector<int> key_;
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }

  Rmq<int> rmq(n, v);
  for (; m; m--) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--;
    y--;
    printf("%d\n", rmq.Get(x, y));
  }

  return 0;
}
