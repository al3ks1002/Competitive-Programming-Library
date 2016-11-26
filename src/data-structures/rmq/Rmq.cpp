#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

template<typename T>
class Rmq {
    public:
        Rmq() {}

        template<typename Array>
        Rmq(int size, const Array& array) : Rmq(size, array, vector<int>()) {}

        template<typename Array>
        Rmq(int size, const Array& array, const vector<int>& key) : size_(size), key_(key) {
            lg_max_ = GetLog(size);
            rmq_.resize(lg_max_);
            for (int i = 0; i < (int)rmq_.size(); i++) {
                rmq_[i].resize(size_);
            }
            PrecalculateLog();
            Build(array);
        }

        T Get(int x, int y) {
            int lg = lg_[y - x + 1];
            return GetMin(rmq_[lg][x], rmq_[lg][y - (1 << lg) + 1]);
        }

    private:
        int size_;
        int lg_max_;
        vector<int> lg_;
        vector<vector<T>> rmq_;
        vector<int> key_;

        int GetLog(int size) {
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
        void Build(Array & array) {
            for (int i = 0; i < size_; i++) {
                rmq_[0][i] = array[i];
            }
            for (int i = 1, p = 2; p <= size_; i++, p *= 2)
                for (int j = 0; j + p - 1 < size_; j++) {
                    rmq_[i][j] = GetMin(rmq_[i - 1][j], rmq_[i - 1][j + p / 2]);
                }
        }

        int GetMin(int x, int y) {
            if (Key(x) < Key(y)) {
                return x;
            }
            return y;
        }

        // If you want the RMQ to be compared with a different key, modify this
        int Key(int x) {
            if (key_.empty()) {
                return x;
            }
            return key_[x];
        }
};

int main() {
    cin.sync_with_stdio(false);

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
