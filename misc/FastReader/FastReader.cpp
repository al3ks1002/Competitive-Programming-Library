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
            while (!IsDigit(buffer_[position_])) {
                AdvancePointer();
            }
            while (IsDigit(buffer_[position_])) {
                number = number * 10 + buffer_[position_] - '0';
                AdvancePointer();
            }
        }

        void ReadInt64(int64_t &number) {
            number = 0;
            while (!IsDigit(buffer_[position_])) {
                AdvancePointer();
            }
            while (IsDigit(buffer_[position_])) {
                number = number * 10 + buffer_[position_] - '0';
                AdvancePointer();
            }
        }

    private:
        void AdvancePointer() {
            if (++position_ == kMaxDim) {
                fread(buffer_, 1, kMaxDim, stdin);
                position_ = 0;
            }
        }

        bool IsDigit(char c) {
            return c >= '0' && c <= '9';
        }

        static const int kMaxDim = 10000;
        char buffer_[kMaxDim];
        int position_;
};

int main() {
    FastReader reader;
    int n;
    reader.ReadInt(n);

    int64_t sol = 0;
    for (; n; n--) {
        int64_t x;
        reader.ReadInt64(x);
        sol ^= x;
    }

    cout << sol << '\n';

    return 0;
}
