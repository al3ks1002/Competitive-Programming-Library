#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

// Class that represents a segment tree that supports
// update operation on intervals (lazy update).
template<typename T>
class LazySegmentTree {
    public:
        LazySegmentTree(int size) : size_(size) {
            segment_.resize(4 * size + 5);
            lazy_.resize(4 * size + 5);
        }

        template<typename Array>
        LazySegmentTree(int size, Array& array) : size_(size) {
            segment_.resize(4 * size + 5);
            lazy_.resize(4 * size + 5);
            Build(1, 1, size, array);
        }

        void Update(int update_left, int update_right, T value) {
            return Update(1, 1, size_, update_left, update_right, value);
        }

        T Query(int left, int right) {
            return Query(1, 1, size_, left, right);
        }

    private:
        template<typename Array>
        void Build(int node, int left, int right, Array& v) {
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

        void Update(int node, int left, int right, int update_left, int update_right, T value) {
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

        T Query(int node, int left, int right, int update_left, int update_right) {
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

        void Propagate(int node, int left, int right) {
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
    return 0;
}
