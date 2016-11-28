#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>

using namespace std;

template<class T>
class HashSet {
    public:
        HashSet() {
            srand(time(0));
            mod_ = kHashPrimes[rand() % 3];
            hash_.resize(mod_);
        }

        bool Insert(const T value) {
            int bucket = value % mod_;
            for (T current_value : hash_[bucket]) {
                if (current_value == value) {
                    return false;
                }
            }
            hash_[bucket].push_back(value);
            return true;
        }

        bool Remove(const T value) {
            int bucket = value % mod_;
            for (T& current_value : hash_[bucket]) {
                if (current_value == value) {
                    swap(current_value, hash_[bucket].back());
                    hash_[bucket].pop_back();
                    return true;
                }
            }
            return false;
        }

        bool Find(const T value) const {
            int bucket = value % mod_;
            for (T current_value : hash_[bucket]) {
                if (current_value == value) {
                    return true;
                }
            }
            return false;
        }

    private:
        const int kHashPrimes[3] = {98317, 196613, 393241};
        int mod_;
        vector<vector<T>> hash_;
};

int main() {
    int m;
    scanf("%d", &m);

    HashSet<int> hash;
    for (; m; m--) {
        int op, x;
        scanf("%d%d", &op, &x);

        if (op == 1) {
            hash.Insert(x);
        } else if (op == 2) {
            hash.Remove(x);
        } else {
            printf("%d\n", hash.Find(x));
        }
    }

    return 0;
}
