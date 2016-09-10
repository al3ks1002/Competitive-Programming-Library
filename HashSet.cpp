#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

// Class that represents a hash set.
template<class T>
class HashSet {
    public:
        HashSet() {
            srand(time(0));
            kMod = kHashPrimes[rand() % 3];
            hash_.resize(kMod);
            cerr << kMod << endl;
        }

        void Insert(T value) {
            int bucket = value % kMod;
            for (T current_value : hash_[bucket]) {
                if (current_value == value) {
                    return;
                }
            }
            hash_[bucket].push_back(value);
        }

        void Remove(T value) {
            int bucket = value % kMod;
            for (T& current_value : hash_[bucket]) {
                if (current_value == value) {
                    swap(current_value, hash_[bucket].back());
                    hash_[bucket].pop_back();
                    return;
                }
            }
        }

        bool Find(T value) {
            int bucket = value % kMod;
            for (T current_value : hash_[bucket]) {
                if (current_value == value) {
                    return true;
                }
            }
            return false;
        }

    private:
        const int kHashPrimes[3] = {98317, 196613, 393241};
        int kMod;
        vector<vector<T>> hash_;

};

int main() {
    return 0;
}
