#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class RollingHash {
    public:
        explicit RollingHash(const string& text) : text_(text) {}

        pair<int, vector<int>> GetMatchingIndexes(const string& pattern,
        const int max_index_count) {
            int count = 0;
            vector<int> indexes;
            indexes.reserve(max_index_count);

            int length = pattern.size();
            pair<int, int> pattern_code = GetCode(pattern);

            int powered_base[2];
            pair<int, int> powered_base_pair = GetPoweredBase(length);
            powered_base[0] = powered_base_pair.first;
            powered_base[1] = powered_base_pair.second;

            int match[2] = {0, 0};
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < 2; j++) {
                    match[j] = (match[j] * kBase + text_[i]) % kHashPrimes[j];
                }
            }
            if (make_pair(match[0], match[1]) == pattern_code) {
                count++;
                indexes.push_back(0);
            }

            for (int i = length; i < (int)text_.size(); i++) {
                for (int j = 0; j < 2; j++) {
                    match[j] = ((match[j] - (powered_base[j] * text_[i - length]) % kHashPrimes[j]
                                 + kHashPrimes[j]) * kBase + text_[i]) % kHashPrimes[j];
                }

                if (make_pair(match[0], match[1]) == pattern_code) {
                    count++;
                    if ((int)indexes.size() < max_index_count) {
                        indexes.push_back(i - length + 1);
                    }
                }
            }

            return {count, indexes};
        }

    private:
        pair<int, int> GetCode(const string& pattern) {
            int match[2] = {0, 0};
            for (int i = 0; i < (int)pattern.size(); i++) {
                for (int j = 0; j < 2; j++) {
                    match[j] = (match[j] * kBase + pattern[i]) % kHashPrimes[j];
                }
            }
            return {match[0], match[1]};
        }

        pair<int, int> GetPoweredBase(const int length) {
            int powered_base[2] = {1, 1};
            for (int i = 0; i < length - 1; i++) {
                for (int j = 0; j < 2; j++) {
                    powered_base[j] = (powered_base[j] * kBase) % kHashPrimes[j];
                }
            }
            return {powered_base[0], powered_base[1]};
        }

        long long GetCombinedCode(const int x, const int y) const {
            return 1LL * x * kHashPrimes[1] + y;
        }

        long long GetCombinedCode(const pair<int, int> p) const {
            return GetCombinedCode(p.first, p.second);
        }

        static const int kBase = 137;
        const int kHashPrimes[2] = {100003, 666013};
        const string text_;
};

int main() {
    cin.sync_with_stdio(false);

    string pattern;
    cin >> pattern;

    string text;
    cin >> text;

    RollingHash hash(text);

    pair<int, vector<int>> answer = hash.GetMatchingIndexes(pattern, 1000);
    cout << answer.first << '\n';
    for (int it : answer.second) {
        cout << it << " ";
    }

    return 0;
}
