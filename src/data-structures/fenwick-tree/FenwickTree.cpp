#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;


template<class T>
class FenwickTree {
    public:
        FenwickTree() {}

        FenwickTree(int size) : size_(size) {
            fenwick_.resize(size_ + 1);
            max_power_ = GetMaxPower(size);
        }

        // The array has to be indexed from 1.
        template<typename Array>
        FenwickTree(int size, Array& v) : size_(size) {
            fenwick_.resize(size_ + 1);
            Build(size_, v);
            max_power_ = GetMaxPower(size);
        }

        void Update(int position, T value) {
            for (int i = position; i <= size_; i += Lsb(i)) {
                fenwick_[i] += value;
            }
        }

        T GetSum(int left, int right) {
            return GetSum(right) - GetSum(left - 1);
        }

        // Find the first position k such that the sum of the first k values is equal to value.
        int Query(T value) {
            int position = 0;
            T initial_value = value;

            for (int step = max_power_; step; step /= 2)
                if (position + step < size_ && fenwick_[position + step] < value) {
                    value -= fenwick_[position + step];
                    position += step;
                }

            return (GetSum(position + 1) == initial_value) ? position + 1 : -1;
        }

    private:
        vector<T> fenwick_;
        int size_;
        int max_power_;

        int GetMaxPower(int size) {
            int max_power = 1;
            while (max_power <= size) {
                max_power *= 2;
            }
            return max_power;
        }

        int Lsb(int x) {
            return x & (-x);
        }

        T GetSum(int position) {
            T result = 0;

            for (int i = position; i; i -= Lsb(i)) {
                result += fenwick_[i];
            }

            return result;
        }

        template<typename Array>
        void Build(int size_, Array& v) {
            for (int i = 1; i <= size_; i++) {
                Update(i, v[i]);
            }
        }
};

int main() {
    cin.sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    FenwickTree<int> myTree(n);

    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        myTree.Update(i, val);
    }

    for (; q; q--) {
        int op;
        cin >> op;

        if (op == 0) {
            int poz, val;
            cin >> poz >> val;
            myTree.Update(poz, val);
        } else if (op == 1) {
            int a, b;
            cin >> a >> b;
            cout << myTree.GetSum(a, b) << '\n';
        } else {
            int val;
            cin >> val;
            cout << myTree.Query(val) << '\n';
        }
    }

    return 0;
}
