#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class AhoCorasickAutomaton {
    public:
        AhoCorasickAutomaton(int alphabet_start) : alphabet_start_(alphabet_start), num_words_(0) {
            root_ = new Node();
        }

        void InsertWord(const string& word, int index) {
            num_words_ = max(num_words_, index + 1);
            Node* current = root_;
            for (int letter : word) {
                letter -= alphabet_start_;
                if (current->sons_[letter] == nullptr) {
                    current->sons_[letter] = new Node();
                }
                current = current->sons_[letter];
            }
            current->indexes_.push_back(index);
        }

        void Prepare() {
            BuildFailEdges();
        }

        vector<int> FindMatchings(const string& text) {
            ParseText(text);
            return RunAntiBFSAndGetMatchings();
        }

    private:
        const static int kMaxSons = 26;

        struct Node {
            vector<int> indexes_;
            int count_;
            Node* sons_[kMaxSons];
            Node* fail_;

            Node() : count_(0), fail_(nullptr) {
                for (int i = 0; i < kMaxSons; i++) {
                    sons_[i] = nullptr;
                }
            }
        };

        void BuildFailEdges() {
            deque<Node*> queue;
            root_->fail_ = root_;
            queue.push_back(root_);

            while (!queue.empty()) {
                Node* current = queue.front();
                queue_.push_back(current);
                queue.pop_front();

                for (int i = 0; i < kMaxSons; i++) {
                    if (current->sons_[i] != nullptr) {
                        Node* next = current->sons_[i];
                        Node* fail = current->fail_;

                        while (fail != root_ && fail->sons_[i] == nullptr) {
                            fail = fail->fail_;
                        }

                        if (fail->sons_[i] != nullptr && fail->sons_[i] != next) {
                            fail = fail->sons_[i];
                        }

                        next->fail_ = fail;
                        queue.push_back(next);
                    }
                }
            }
        }

        void ParseText(const string& text) {
            ClearCount();

            Node* current = root_;
            for (int letter : text) {
                letter -= alphabet_start_;

                while (current != root_ && current->sons_[letter] == nullptr) {
                    current = current->fail_;
                }

                if (current->sons_[letter] != nullptr) {
                    current = current->sons_[letter];
                }

                current->count_++;
            }
        }

        vector<int> RunAntiBFSAndGetMatchings() {
            vector<int> matchings(num_words_);
            for (auto it = queue_.rbegin(); it != queue_.rend(); it++) {
                Node* current = *it;
                current->fail_->count_ += current->count_;

                for (int index : current->indexes_) {
                    matchings[index] = current->count_;
                }
            }
            return matchings;
        }

        void ClearCount() {
            for (Node*& current : queue_) {
                current->count_ = 0;
            }
        }

        Node* root_;
        int alphabet_start_;
        int num_words_;
        deque<Node*> queue_;
};

int main() {
    cin.sync_with_stdio(false);

    ifstream cin("ahocorasick.in");
    ofstream cout("ahocorasick.out");

    string text;
    cin >> text;

    AhoCorasickAutomaton aho('a');

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        aho.InsertWord(word, i);
    }

    aho.Prepare();

    auto answer = aho.FindMatchings(text);
    for (auto it : answer) {
        cout << it << '\n';
    }

    return 0;
}
