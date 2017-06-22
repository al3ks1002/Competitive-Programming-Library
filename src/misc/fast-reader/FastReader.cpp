#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

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

  void ReadLongLong(long long &number) {
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

  bool IsDigit(const char c) const {
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

  int sol = 0;
  for (; n; n--) {
    int x;
    reader.ReadInt(x);
    sol ^= x;
  }

  cout << sol << '\n';

  return 0;
}
