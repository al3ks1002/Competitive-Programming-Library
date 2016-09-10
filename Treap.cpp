#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

// Class that represents a treap.
template<class T>
class Treap {
    public:
        /**
         * Default constructor for Treap.
         */
        Treap() {
            srand(time(0));
            root_ = nullptr;
        }

        /**
         * Finds if a value is in the treap.
         */
        bool Find(T value) const {
            return FindValue(root_, value);
        }

        /**
         * Inserts a value in the treap (if it's already
         * in the treap, nothing happens).
         */
        void Insert(T value) {
            if (Find(value)) {
                return;
            }
            root_ = InsertValue(value);
        }

        /**
         * Removes a value from the treap (if it's not
         * in the treap, nothing happens).
         */
        void Remove(T value) {
            root_ = RemoveValue(root_, value);
        }

        /**
         * Finds the kth value from the treap
         * (preconditions: k must be in [1, treap.Size()]).
         */
        T KthElement(int k) const {
            return FindKthElement(root_, k);
        }

        /**
         * Counts how many values from the treap are
         * smaller or equal than the given value.
         */
        int SmallerOrEqualThan(T value) const {
            return CountSmallerOrEqualThan(root_, value);
        }

        /**
         * Returns the size of the treap.
         */
        int Size() const {
            return GetSubtreeSize(root_);
        }

    private:
        struct Node {
            const T value_;
            const int priority_;
            Node* left_;
            Node* right_;
            int subtree_;

            Node(int value) : value_(value), left_(nullptr), right_(nullptr),
                priority_((rand() << 16) ^ rand()), subtree_(1) {}
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

        pair<Node*, Node*> Split(Node* current_node, T split_value) {
            if (current_node == nullptr) {
                return {nullptr, nullptr};
            }

            pair<Node*, Node*> roots;
            if (current_node->value_ <= split_value) {
                roots = Split(current_node->right_, split_value);
                current_node->right_ = roots.first;
                roots.first = current_node;
            } else {
                roots = Split(current_node->left_, split_value);
                current_node->left_ = roots.second;
                roots.second = current_node;
            }

            UpdateNode(current_node);
            return roots;
        }

        Node* Merge(Node* left_root, Node* right_root) {
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

        bool FindValue(Node* node, T value) const {
            if (node == nullptr) {
                return false;
            }

            if (value < node->value_) {
                return FindValue(node->left_, value);
            } else if (value > node->value_) {
                return FindValue(node->right_, value);
            }

            return true;
        }

        Node* InsertValue(T value) {
            pair<Node*, Node*> roots = Split(root_, value);
            return Merge(Merge(roots.first, new Node(value)), roots.second);
        }

        Node* RemoveValue(Node* node, T value) {
            if (node == nullptr) {
                return nullptr;
            }

            if (value == node->value_) {
                Node* old_node = node;
                node = Merge(node->left_, node->right_);
                delete old_node;
            } else if (value < node->value_) {
                node->left_ = RemoveValue(node->left_, value);
            } else {
                node->right_ = RemoveValue(node->right_, value);
            }

            UpdateNode(node);
            return node;
        }

        T FindKthElement(Node* node, int k) const {
            int left_subtree_size = GetSubtreeSize(node->left_);
            if (left_subtree_size + 1 == k) {
                return node->value_;
            }

            if (left_subtree_size + 1 < k) {
                return FindKthElement(node->right_, k - left_subtree_size - 1);
            } else {
                return FindKthElement(node->left_, k);
            }
        }

        int CountSmallerOrEqualThan(Node* node, T value) const {
            if (node == nullptr) {
                return 0;
            }

            if (node->value_ <= value) {
                return 1 + GetSubtreeSize(node->left_)
                       + CountSmallerOrEqualThan(node->right_, value);
            } else {
                return CountSmallerOrEqualThan(node->left_, value);
            }
        }

        Node* root_;
};

int main() {
    return 0;
}