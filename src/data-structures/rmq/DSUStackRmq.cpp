#include <stdio.h>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

class DisjointSet {
 public:
  explicit DisjointSet(const int size) : size_(size + 1) {
    father_.resize(size_);
    rank_.resize(size_);
    for (int i = 0; i < size_; i++) {
      father_[i] = i;
      rank_[i] = 1;
    }
  }

  int Find(const int x) {
    if (father_[x] != x) {
      father_[x] = Find(father_[x]);
    }
    return father_[x];
  }

  void SetFather(const int x, const int y) {
    father_[x] = y;
  }

  // x and y must be roots
  void Unite(const int x, const int y) {
    if (rank_[x] < rank_[y]) {
      father_[x] = y;
    } else {
      father_[y] = x;
      if (rank_[x] == rank_[y]) {
        rank_[x]++;
      }
    }
  }

 private:
  const int size_;
  vector<int> father_;
  vector<int> rank_;
};

template<class T>
class DSUStackRmq {
 public:
  // The array must be indexed from 0.
  DSUStackRmq(const int size, const vector<T>& array,
              const vector<pair<int, int>> queries) :
    size_(size), array_(array), queries_(queries) {}

  vector<T> GetAnswers() {
    vector<T> answer(queries_.size());
    DisjointSet ds(size_);
    stack<int> stack;
    vector<vector<pair<int, int>>> query_info(size_ + 1);

    for (int i = 0; i < (int)queries_.size(); i++) {
      query_info[queries_[i].second].emplace_back(queries_[i].first, i);
    }

    for (int i = 0; i < (int)array_.size(); i++) {
      while (!stack.empty() && array_[i] <= array_[stack.top()]) {
        ds.SetFather(stack.top(), i);
        stack.pop();
      }
      stack.push(i);

      for (auto query : query_info[i]) {
        answer[query.second] = array_[ds.Find(query.first)];
      }
    }

    return answer;
  }

 private:
  const int size_;
  const vector<T> array_;
  const vector<pair<T, T>> queries_;
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }

  vector<pair<int, int>> queries(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &queries[i].first, &queries[i].second);
    queries[i].first--;
    queries[i].second--;
  }

  DSUStackRmq<int> dsr(n, v, queries);
  auto answer = dsr.GetAnswers();

  for (auto it : answer) {
    printf("%d\n", it);
  }

  return 0;
}
