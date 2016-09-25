#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class DisjointSet {
    public:
        DisjointSet(int size) : size_(size + 1) {
            father_.resize(size_);
            for (int i = 0; i < size_; i++) {
                father_[i] = i;
            }
        }

        int Find(int x) {
            if (father_[x] != x) {
                father_[x] = Find(father_[x]);
            }
            return father_[x];
        }

        void Unite(int x, int y) {
            father_[x] = y;
        }

    private:
        int size_;
        vector<int> father_;
};

int main() {
    return 0;
}
