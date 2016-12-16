#include <fstream>
#include <sstream>

using namespace std;

const int kMaxN = 1e5;
const int kMaxQ = 1e5;
const int kMaxVal = 1e7;

int main() {
    srand(time(0));

    for (int i = 1; i <= 10; i++) {
        string test = "test";
        stringstream my_stream;
        string in = ".in";
        my_stream << test << i << in;
        string str = my_stream.str();
        ofstream cout(str);

        int n, q;
        if (i < 7) {
            n = rand() % kMaxN + 1;
            q = rand() % kMaxQ + 1;
        } else {
            n = kMaxN;
            q = kMaxQ;
        }

        cout << n << " " << q << '\n';

        for (; q; q--) {
            int op = rand() % 2;
            cout << op << " ";
            if (op == 0) { // query
                int x = rand() % n + 1;
                int y = rand() % n + 1;
                int val = rand() % kMaxVal + 1;
                if (x > y) {
                    swap(x, y);
                }
                cout << x << " " << y << " " << val << '\n';
            } else {
                int x = rand() % n + 1;
                int y = rand() % n + 1;
                if (x > y) {
                    swap(x, y);
                }
                cout << x << " " << y << '\n';
            }
        }
    }

    return 0;
}
