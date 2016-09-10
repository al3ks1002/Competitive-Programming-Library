#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

// Class that represents a fast reader.
class FastReader {
    public:
        FastReader() {
            position_ = 0;
            memset(buffer_, 0, sizeof(buffer_));
        }

        void ReadInt(int &number) {
            number = 0;
            while (buffer_[position_] < '0' || buffer_[position_] > '9') {
                AdvancePointer();
            }
            while (buffer_[position_] >= '0' && buffer_[position_] <= '9') {
                number = number * 10 + buffer_[position_] - '0';
                AdvancePointer();
            }
        }

        void ReadInt64(int64_t &number) {
            number = 0;
            while (buffer_[position_] < '0' || buffer_[position_] > '9') {
                AdvancePointer();
            }
            while (buffer_[position_] >= '0' && buffer_[position_] <= '9') {
                number = number * 10 + buffer_[position_] - '0';
                AdvancePointer();
            }
        }

    private:
        const static int kMaxDim = 10000;
        char buffer_[kMaxDim];
        int position_;

        void AdvancePointer() {
            if (++position_ == kMaxDim) {
                fread(buffer_, 1, kMaxDim, stdin);
                position_ = 0;
            }
        }
};

int main() {
    return 0;
}
