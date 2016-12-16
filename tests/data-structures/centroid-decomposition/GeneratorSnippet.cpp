#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int kMaxN = 1e5;

int main() {
    srand(time(0));

    for (int i = 1; i <= 10; i++) {
        string test = "test";
        stringstream my_stream;
        string in = ".in";
        my_stream << test << i << in;
        string str = my_stream.str();
        ofstream cout(str);

        int n;
        if (i <= 2) {
            n = 10;
        } else if (i <= 7) {
            n = rand() % kMaxN + 1;
        } else {
            n = kMaxN;
        }
        int m = n;

        cout << n << " " << m << '\n';
        for (int i = 2; i <= n; i++) {
            cout << i << " " << rand() % (i - 1) + 1 << '\n';
        }

        vector<int> v;
        for (int i = 2; i <= n; i++) {
            v.push_back(i);
        }
        random_shuffle(v.begin(), v.end());

        for (; m; m--) {
            int op = rand() % 2 + 1;
            cout << op << " ";
            if (op == 1) {
                cout << v.back() << '\n';
                v.pop_back();
            } else {
                cout << rand() % n + 1 << '\n';
            }
        }
    }

    return 0;
}
