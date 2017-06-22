#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

template<class T>
class SuffixArray {
 public:
  // Must be indexed from 0.
  explicit SuffixArray(const vector<T>& array) :
    array_(array), array_size_(array.size()) {
    min_value_ = *min_element(array.begin(), array.end());
  }

  void Build() {
    suffix_.resize(GetLog(array_.size()));
    for (int i = 0; i < suffix_.size(); i++) {
      suffix_[i].resize(array_.size());
    }

    for (int i = 0; i < array_size_; i++) {
      suffix_[0][i] = array_[i] - min_value_;
    }

    for (int step = 1; step < suffix_.size(); step++) {
      int length = 1 << (step - 1);

      pieces_.clear();
      for (int i = 0; i < array_size_; i++) {
        int current_left_piece = suffix_[step - 1][i];
        int current_right_piece = (i + length < array_size_) ?
                                  suffix_[step - 1][i + length] : -1;
        int current_index = i;
        pieces_.emplace_back(current_left_piece, current_right_piece, current_index);
      }

      sort(pieces_.begin(), pieces_.end());

      for (int i = 0; i < array_size_; i++) {
        if (i > 0 && pieces_[i] == pieces_[i - 1]) {
          suffix_[step][pieces_[i].index_] = suffix_[step][pieces_[i - 1].index_];
        } else {
          suffix_[step][pieces_[i].index_] = i;
        }
      }
    }

    sorted_indexes_.resize(array_size_);
    for (int i = 0; i < array_size_; i++) {
      sorted_indexes_[i] = pieces_[i].index_;
    }
  }

  vector<int> GetSortedIndexes() {
    if (sorted_indexes_.empty()) {
      Build();
    }
    return sorted_indexes_;
  }

  int GetLongestCommonPrefix(int index_x, int index_y) {
    if (suffix_.empty()) {
      Build();
    }

    int lcp = 0;
    for (int i = suffix_.size() - 1; i >= 0
         && index_x < array_size_ && index_y < array_size_; i--) {
      int length = 1 << i;
      if (index_x + length <= array_size_ && index_y + length <= array_size_
          && suffix_[i][index_x] == suffix_[i][index_y]) {
        lcp += length;
        index_x += length;
        index_y += length;
      }
    }

    return lcp;
  }

 private:
  struct ArrayPiece {
    int left_piece_;
    int right_piece_;
    int index_;

    ArrayPiece(const int left_piece, const int right_piece, const int index) :
      left_piece_(left_piece), right_piece_(right_piece), index_(index) {}

    bool operator < (const ArrayPiece& other) const {
      if (this->left_piece_ == other.left_piece_) {
        return this->right_piece_ < other.right_piece_;
      }
      return this->left_piece_ < other.left_piece_;
    }

    bool operator == (const ArrayPiece& other) const {
      return this->left_piece_ == other.left_piece_
             && this->right_piece_ == other.right_piece_;
    }
  };

  int GetLog(int x) const {
    int log = 0;

    do {
      log++;
      x /= 2;
    } while (x);

    return log + 1;
  }

  const int array_size_;
  const vector<T> array_;
  T min_value_;
  vector<vector<int>> suffix_;
  vector<ArrayPiece> pieces_;
  vector<int> sorted_indexes_;
};

int main() {
  cin.sync_with_stdio(false);

  vector<char> v;

  string s;
  cin >> s;
  int n = s.size();

  for (char it : s) {
    v.push_back(it);
  }
  for (char it : s) {
    v.push_back(it);
  }

  SuffixArray<char> sa(v);
  sa.Build();

  auto sorted_indexes = sa.GetSortedIndexes();
  vector<int> valid_sorted_indexes;
  for (auto it : sorted_indexes) {
    if (it < n) {
      valid_sorted_indexes.push_back(it);
    }
  }

  int ans = valid_sorted_indexes[n - 1];
  for (int i = 0; i < n - 1; i++) {
    if (sa.GetLongestCommonPrefix(valid_sorted_indexes[i],
                                  valid_sorted_indexes[i + 1]) < n) {
      ans = valid_sorted_indexes[i];
      break;
    }
  }
  cout << ans << '\n';

  return 0;
}
