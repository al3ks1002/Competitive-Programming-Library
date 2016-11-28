#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class KMP {
    public:
        explicit KMP(const string& text) : text_(text) {}

        pair<int, vector<int>> GetMatchingIndexes(const string& pattern,
            const int max_index_count) {
            int count = 0;
            vector<int> indexes;
            indexes.reserve(max_index_count);

            vector<int> prefix(pattern.size(), 0);
            BuildPi(pattern, prefix);

            int q = 0;
            for (int i = 0; i < (int)text_.size(); i++) {
                while (q && pattern[q] != text_[i]) {
                    q = prefix[q - 1];
                }

                if (pattern[q] == text_[i]) {
                    q++;
                }

                if (q == (int)pattern.size()) {
                    if (++count <= max_index_count) {
                        indexes.push_back(i - pattern.size() + 1);
                    }
                }
            }

            return {count, indexes};
        }

    private:
        void BuildPi(const string& pattern, vector<int>& prefix) {
            int q = 0;
            for (int i = 1; i < (int)pattern.size(); i++) {
                while (q && pattern[q] != pattern[i]) {
                    q = prefix[q - 1];
                }

                if (pattern[q] == pattern[i]) {
                    q++;
                }

                prefix[i] = q;
            }
        }

        const string text_;
};

int main() {
    cin.sync_with_stdio(false);

    string pattern;
    cin >> pattern;

    string text;
    cin >> text;

    KMP kmp(text);

    pair<int, vector<int>> answer = kmp.GetMatchingIndexes(pattern, 1000);
    cout << answer.first << '\n';
    for (int it : answer.second) {
        cout << it << " ";
    }

    return 0;
}
