#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class MinimumLexicographicalRotation {
 public:
  explicit MinimumLexicographicalRotation(const string& text) :
    text_(text + text) {}

  int FindMinimumLexicographicalRotation() {
    // the index where the rotation is minimum
    int minimum_rotation = 0;

    // the current index
    int current_index = 1;

    // the first match characters from text_[minimum_rotation]
    // are equal with the first match characters from text_[current_index]
    int match = 0;

    while (current_index < (int)text_.size() / 2
           && minimum_rotation + match + 1 < (int)text_.size() / 2) {
      if (text_[minimum_rotation + match] == text_[current_index + match]) {
        match++;
      } else if (text_[minimum_rotation + match] < text_[current_index + match]) {
        current_index = current_index + match + 1;
        match = 0;
      } else {
        minimum_rotation = max(minimum_rotation + match + 1, current_index);
        current_index = minimum_rotation + 1;
        match = 0;
      }
    }

    return minimum_rotation;
  }

 private:
  string text_;
};

int main() {
  cin.sync_with_stdio(false);

  string s;
  cin >> s;

  MinimumLexicographicalRotation mlr(s);
  cout << mlr.FindMinimumLexicographicalRotation() << '\n';

  return 0;
}
