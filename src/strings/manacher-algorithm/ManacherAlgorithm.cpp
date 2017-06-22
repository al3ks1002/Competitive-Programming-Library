#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Manacher {
 public:
  explicit Manacher(const string& text) {
    text_ = "$";
    for (auto ch : text) {
      text_ += ch;
      text_ += '$';
    }

    longest_ = vector<int>(text_.size());
    for (int i = 0; i < (int)text_.size(); i++) {
      longest_[i] = (text_[i] != '$');
    }
  }

  void Prepare() {
    int center = 0;
    int max_right = 0;

    for (int i = 1; i < (int)text_.size(); i++) {
      int mirror = 2 * center - i;

      if (i <= max_right) {
        longest_[i] = min(longest_[mirror], max_right - i + 1);
      }

      int left = i - longest_[i] + 1;
      int right = i + longest_[i] - 1;
      while (left - 2 >= 0 && right + 2 < (int)text_.size()
             && text_[left - 2] == text_[right + 2]) {
        left -= 2;
        right += 2;
        longest_[i] += 2;
      }

      if (right > max_right) {
        max_right = right;
        center = i;
      }
    }
  }

  long long GetNumberOfPalindromes() const {
    long long palindromes = 0;
    for (int i = 0; i < (int)longest_.size(); i++) {
      palindromes += (longest_[i] + 1) / 2;
    }
    return palindromes;
  }

  int GetLongestPalindrome() const {
    int longest = 0;
    for (int i = 0; i < (int)longest_.size(); i++) {
      longest = max(longest, longest_[i]);
    }
    return longest;
  }

 private:
  string text_;
  vector<int> longest_;
};

int main() {
  cin.sync_with_stdio(false);

  string s;
  cin >> s;

  Manacher manacher(s);
  manacher.Prepare();
  cout << manacher.GetNumberOfPalindromes() << '\n';
  cout << manacher.GetLongestPalindrome() << '\n';

  return 0;
}
