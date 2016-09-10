#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

// Class that represents an implicit treap.
template<class T>
class ImplicitTreap {
    public:
        /**
         * Default constructor for ImplicitTreap.
         */
        ImplicitTreap() {
            srand(time(0));
            root_ = nullptr;
        }

        /**
         * Finds the value from a given index.
         */
        T GetValueFromIndex(T index) {
            return FindValueFromIndex(root_, index);
        }

        /**
         * Insers a value at a given index.
         */
        void InsertValueAtIndex(int index, T value) {
            pair<Node*, Node*> roots = Split(root_, index - 1);
            root_ = Merge(Merge(roots.first, new Node(value)), roots.second);
        }

        /**
        * Deletes the interval [left_index, right_index].
        * Preconditions: 1 <= left_index <= right_index <= treap.Size().
        */
        void DeleteInterval(int left_index, int right_index) {
            pair<Node*, Node*> left_interval = Split(root_, left_index - 1);
            pair<Node*, Node*> middle_interval =
                Split(left_interval.second, right_index - left_index + 1);
            DeleteTreap(middle_interval.first);
            root_ = Merge(left_interval.first, middle_interval.second);
        }

        /**
         * Reverses the interval [left_index, right_index].
         * Preconditions: 1 <= left_index <= right_index <= treap.Size().
         */
        void ReverseInterval(int left_index, int right_index) {
            pair<Node*, Node*> left_interval = Split(root_, left_index - 1);
            pair<Node*, Node*> middle_interval =
                Split(left_interval.second, right_index - left_index + 1);
            Reverse(middle_interval.first);
            root_ = Merge(Merge(left_interval.first, middle_interval.first),
                          middle_interval.second);
        }

        /**
         * Returns the size of the treap.
         */
        int Size() const {
            return GetSubtreeSize(root_);
        }

        /**
         * Prints the treap.
         */
        void Print()  {
            PrintTreap(root_);
        }

    private:
        struct Node {
            const T value_;
            const int priority_;
            Node* left_;
            Node* right_;
            int subtree_;
            bool is_reversed_;

            Node(int value) : value_(value), left_(nullptr), right_(nullptr),
                priority_((rand() << 16) ^ rand()), subtree_(1), is_reversed_(false) {}
        };

        int GetSubtreeSize(Node* node) const {
            return node == nullptr ? 0 : node->subtree_;
        }

        void UpdateNode(Node* node) {
            if (node == nullptr) {
                return;
            }
            node->subtree_ = 1 + GetSubtreeSize(node->left_)
                             + GetSubtreeSize(node->right_);
        }

        pair<Node*, Node*> Split(Node* node, int index) {
            if (node == nullptr) {
                return {nullptr, nullptr};
            }

            Propagate(node);

            pair<Node*, Node*> roots;
            int current_index = GetSubtreeSize(node->left_) + 1;
            if (current_index <= index) {
                roots = Split(node->right_, index - current_index);
                node->right_ = roots.first;
                roots.first = node;
            } else {
                roots = Split(node->left_, index);
                node->left_ = roots.second;
                roots.second = node;
            }

            UpdateNode(node);
            return roots;
        }

        Node* Merge(Node* left_root, Node* right_root) {
            Propagate(left_root);
            Propagate(right_root);

            if (left_root == nullptr) {
                return right_root;
            }

            if (right_root == nullptr) {
                return left_root;
            }

            if (left_root->priority_ > right_root->priority_) {
                left_root->right_ = Merge(left_root->right_, right_root);
                UpdateNode(left_root);
                return left_root;
            } else {
                right_root->left_ = Merge(left_root, right_root->left_);
                UpdateNode(right_root);
                return right_root;
            }
        }

        T FindValueFromIndex(Node* node, int index) {
            Propagate(node);

            int current_index = GetSubtreeSize(node->left_) + 1;
            if (current_index == index) {
                return node->value_;
            }
            if (current_index < index) {
                return FindValueFromIndex(node->right_, index - current_index);
            } else {
                return FindValueFromIndex(node->left_, index);
            }
        }

        void Propagate(Node* node) {
            if (node == nullptr || node->is_reversed_ == false) {
                return;
            }
            node->is_reversed_ = false;
            Reverse(node->left_);
            Reverse(node->right_);
            swap(node->left_, node->right_);
        }

        void Reverse(Node* node) {
            if (node == nullptr) {
                return;
            }
            node->is_reversed_ ^= 1;
        }

        void DeleteTreap(Node* node) {
            if (node == nullptr) {
                return;
            }
            if (node->left_ != nullptr) {
                DeleteTreap(node->left_);
            }
            if (node->right_ != nullptr) {
                DeleteTreap(node->right_);
            }
            delete node;
        }

        void PrintTreap(Node* node) {
            if (node == nullptr) {
                return;
            }
            Propagate(node);
            if (node->left_ != nullptr) {
                PrintTreap(node->left_);
            }
            printf("%d ", node->value_);
            if (node->right_ != nullptr) {
                PrintTreap(node->right_);
            }
        }

        Node* root_;
};

int main() {
    return 0;
}
