#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

// Class that represents a segment tree that supports
// update operation only on a value (not an interval).
template<typename T>
class SegmentTree {
    public:
        SegmentTree(int size) : size_(size) {
            segment_.resize(4 * size + 5);
        }

        // The array must be indexed from 1
        template<typename Array>
        SegmentTree(int size, Array& array) : size_(size) {
            segment_.resize(4 * size + 5);
            Build(1, 1, size, array);
        }

        void Update(int position, T value) {
            return Update(1, 1, size_, position, value);
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

            segment_[node] = TreeFunction(segment_[left_son], segment_[right_son]);
        }

        void Update(int node, int left, int right, int position, T value) {
            if (left == right) {
                segment_[node] = value;
                return;
            }

            int middle = (left + right) / 2;
            int left_son = 2 * node;
            int right_son = 2 * node + 1;

            if (position <= middle) {
                Update(left_son, left, middle, position, value);
            } else {
                Update(right_son, middle + 1, right, position, value);
            }

            segment_[node] = TreeFunction(segment_[left_son], segment_[right_son]);
        }

        T Query(int node, int left, int right, int a, int b) {
            if (left >= a && right <= b) {
                return segment_[node];
            }

            int middle = (left + right) / 2;
            int left_son = 2 * node;
            int right_son = 2 * node + 1;

            T x = 0;
            T y = 0;

            if (a <= middle) {
                x = Query(left_son, left, middle, a, b);
            }
            if (b > middle) {
                y = Query(right_son, middle + 1, right, a, b);
            }

            return TreeFunction(x, y);
        }

        T TreeFunction(T x, T y) {
            return (x > y) ? x : y;
        }

        vector<T> segment_;
        const int size_;
};

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    vector<int> v(n + 5);
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);

    SegmentTree<int> seg(n, v);

    for (; q; q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int poz, val;
            scanf("%d%d", &poz, &val);
            seg.Update(poz, val);
        } else {
            int left, right;
            scanf("%d%d", &left, &right);
            printf("%d\n", seg.Query(left, right));
        }
    }

    return 0;
}
