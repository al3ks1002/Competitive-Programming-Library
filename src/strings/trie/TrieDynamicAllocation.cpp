#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Class that represents a trie. It uses STL vector.
// It is slow if the number of sons is small (e.g binary trie).
class Trie {
    public:
        Trie(const int alphabet_size, const int alphabet_start) :
            alphabet_size_(alphabet_size), alphabet_start_(alphabet_start) {
            root_ = new Node(alphabet_size_);
        }

        void AddWord(const string& word) {
            Node* current = root_;
            for (char letter : word) {
                letter -= alphabet_start_;
                if (current->sons_[letter] == nullptr) {
                    current->sons_[letter] = new Node(alphabet_size_);
                }
                current = current->sons_[letter];
                ++current->count_;
            }
            ++current->word_count_;
        }

        void DeleteWord(const string& word) {
            vector<Node*> visited_nodes;
            visited_nodes.push_back(root_);

            Node* current = root_;
            for (char letter : word) {
                letter -= alphabet_start_;
                // It is guaranteed that the word exists, so we can go without checking.
                current = current->sons_[letter];
                --current->count_;
                visited_nodes.push_back(current);
            }
            --current->word_count_;

            int current_index = (int)word.size() - 1;
            while (visited_nodes.size() > 1) {
                Node* last = visited_nodes.back();
                visited_nodes.pop_back();
                if (last->count_) {
                    break;
                }
                Node* father = visited_nodes.back();
                father->sons_[word[current_index--] - alphabet_start_] = nullptr;
                delete last;
            }
        }

        int CountWord(const string& word) const {
            Node* current = root_;
            for (char letter : word) {
                letter -= alphabet_start_;
                if (current->sons_[letter] == nullptr) {
                    return 0;
                }
                current = current->sons_[letter];
            }
            return current->word_count_;
        }

        int FindLongestPrefix(const string& word) const {
            int prefix = 0;
            Node* current = root_;
            for (char letter : word) {
                letter -= alphabet_start_;
                if (current->sons_[letter] == nullptr) {
                    return prefix;
                }
                current = current->sons_[letter];
                ++prefix;
            }
            return prefix;
        }

        void Clear() {
            Dfs(root_, nullptr, -1);
        }

        ~Trie() {
            /* Clear(); */
            /* delete root_; */
        }

    private:
        struct Node {
            // How many words finish in this node.
            int word_count_;

            // How many words use this node.
            int count_;

            vector<Node*> sons_;

            explicit Node(int alphabet_size) {
                word_count_ = 0;
                count_ = 0;
                sons_.resize(alphabet_size);
                fill(sons_.begin(), sons_.end(), nullptr);
            }
        };

        void Dfs(Node* node, Node* father, const int letter_from_father) {
            int current_letter = 0;
            for (Node* son : node->sons_) {
                if (son != nullptr) {
                    Dfs(son, node, current_letter);
                }
                ++current_letter;
            }

            if (letter_from_father != -1) {
                father->sons_[letter_from_father] = nullptr;
                delete node;
            }
        }

        const int alphabet_size_;
        const int alphabet_start_;
        Node* root_;
};

int main() {
    Trie trie(26, 'a');
    int operation;
    string word;

    while (cin >> operation >> word) {
        switch (operation) {
        case 0:
            trie.AddWord(word);
            break;
        case 1:
            trie.DeleteWord(word);
            break;
        case 2:
            cout << trie.CountWord(word) << '\n';
            break;
        default:
            cout << trie.FindLongestPrefix(word) << '\n';
        }
    }

    return 0;
}
