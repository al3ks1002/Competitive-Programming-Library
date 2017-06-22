#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

template<class T>
class LIS {
 public:
  // Indexed from 0
  explicit LIS(const vector<T>& array) : array_(array) {}

  vector<T> FindLIS() {
    vector<T> v;
    vector<int> where(array_.size());
    int answer = 0;
    for (int i = 0; i < array_.size(); i++) {
      v.push_back(numeric_limits<T>::max());
      int position = lower_bound(v.begin(), v.end(), array_[i]) - v.begin();
      v[position] = array_[i];
      where[i] = position;
      answer = max(answer, position);
    }

    int current = answer;
    vector<int> actual_answer;
    for (int i = (int)array_.size() - 1; i >= 0; i--) {
      if (where[i] == current) {
        actual_answer.push_back(array_[i]);
        current--;
      }
    }

    reverse(actual_answer.begin(), actual_answer.end());
    return actual_answer;
  }

 private:
  vector<T> array_;
};

int main() {
  cin.sync_with_stdio(false);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  LIS<int> lis(a);
  vector<int> answer = lis.FindLIS();

  cout << answer.size() << '\n';

  return 0;
}
