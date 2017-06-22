#include <stdio.h>
#include <vector>

using namespace std;

// Class that represents a segment tree that supports
// update operation on intervals (lazy update).
template<typename T>
class LazySegmentTree {
 public:
  explicit LazySegmentTree(const int size) : size_(size) {
    segment_.resize(4 * size + 5);
    lazy_.resize(4 * size + 5);
  }

  template<typename Array>
  LazySegmentTree(const int size, const Array& array) : size_(size) {
    segment_.resize(4 * size + 5);
    lazy_.resize(4 * size + 5);
    Build(1, 1, size, array);
  }

  void Update(const int update_left, const int update_right, const T value) {
    return Update(1, 1, size_, update_left, update_right, value);
  }

  T Query(const int left, const int right) {
    return Query(1, 1, size_, left, right);
  }

 private:
  template<typename Array>
  void Build(const int node, const int left, const int right, const Array& v) {
    if (left == right) {
      segment_[node] = v[left];
      return;
    }

    int middle = (left + right) / 2;
    int left_son = 2 * node;
    int right_son = 2 * node + 1;

    Build(left_son, left, middle, v);
    Build(right_son, middle + 1, right, v);

    segment_[node] = segment_[left_son] + segment_[right_son];
  }

  void Update(const int node, const int left, const int right,
              const int update_left, const int update_right, const T value) {
    int middle = (left + right) / 2;
    int left_son = 2 * node;
    int right_son = 2 * node + 1;

    Propagate(node, left, right);

    if (left > update_right || right < update_left) {
      return;
    }

    if (left >= update_left && right <= update_right) {
      segment_[node] += 1LL * value * (right - left + 1);
      if (left < right) {
        lazy_[left_son] += value;
        lazy_[right_son] += value;
      }
      return;
    }

    Update(left_son, left, middle, update_left, update_right, value);
    Update(right_son, middle + 1, right, update_left, update_right, value);
    segment_[node] = segment_[left_son] + segment_[right_son];
  }

  T Query(const int node, const int left, const int right,
          const int update_left,
          const int update_right) {
    int middle = (left + right) / 2;
    int left_son = 2 * node;
    int right_son = 2 * node + 1;

    Propagate(node, left, right);

    if (left > update_right || right < update_left) {
      return 0;
    }

    if (left >= update_left && right <= update_right) {
      return segment_[node];
    }

    return Query(left_son, left, middle, update_left, update_right)
           + Query(right_son, middle + 1, right, update_left, update_right);
  }

  void Propagate(const int node, const int left, const int right) {
    if (lazy_[node]) {
      segment_[node] += lazy_[node] * (right - left + 1);
      if (left < right) {
        lazy_[2 * node] += lazy_[node];
        lazy_[2 * node + 1] += lazy_[node];
      }
      lazy_[node] = 0;
    }
  }

  vector<T> segment_;
  vector<T> lazy_;
  const int size_;
};

int main() {
  int n, q;
  scanf("%d%d", &n, &q);

  LazySegmentTree<long long> seg(n);

  for (; q; q--) {
    int op;
    scanf("%d", &op);

    if (op == 0) {
      int left;
      int right;
      long long val;
      scanf("%d%d%lld", &left, &right, &val);
      seg.Update(left, right, val);
    } else {
      int left, right;
      scanf("%d%d", &left, &right);
      printf("%lld\n", seg.Query(left, right));
    }
  }

  return 0;
}
