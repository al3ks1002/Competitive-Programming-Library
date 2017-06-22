#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class ZAlgorithm {
 public:
  explicit ZAlgorithm(const string& text) : text_(text) {}

  vector<int> FindZ() {
    vector<int> z(text_.size(), 0);
    int left = -1;
    int right = -1;
    for (int i = 1; i < (int)text_.size(); i++) {
      if (i > right) {
        int x = -1;
        int y = i - 1;
        while (y < (int)text_.size() - 1 && text_[x + 1] == text_[y + 1]) {
          x++;
          y++;
        }

        z[i] = x + 1;
        if (z[i]) {
          left = i;
          right = y;
        }
      } else {
        int mirror = i - left;

        if (i + z[mirror] - 1 < right) {
          z[i] = z[mirror];
        } else {
          int x = right - i;
          int y = right;
          while (y < (int)text_.size() - 1 && text_[x + 1] == text_[y + 1]) {
            x++;
            y++;
          }

          z[i] = y - i + 1;
          left = i;
          right = y;
        }
      }
    }

    return z;
  }

  pair<int, vector<int>> GetMatchingIndexes(const string& pattern,
  const int max_index_count) {
    text_ = pattern + '$' + text_;

    int count = 0;
    vector<int> indexes;
    indexes.reserve(max_index_count);

    vector<int> z = FindZ();
    for (int i = 0; i < (int)z.size(); i++) {
      if (z[i] == (int)pattern.size()) {
        if (++count <= max_index_count) {
          indexes.push_back(i - pattern.size() - 1);
        }
      }
    }

    return {count, indexes};
  }

 private:
  string text_;
};

int main() {
  cin.sync_with_stdio(false);

  string pattern;
  cin >> pattern;

  string text;
  cin >> text;

  ZAlgorithm zalgo(text);

  pair<int, vector<int>> answer = zalgo.GetMatchingIndexes(pattern, 1000);
  cout << answer.first << '\n';
  for (int it : answer.second) {
    cout << it << " ";
  }

  return 0;
}
