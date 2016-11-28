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

        int q;
        if (i < 7) {
            q = rand() % kMaxQ + 1;
        } else {
            q = kMaxQ;
        }

        cout << q << '\n';

        char ops[] = {'I', 'D', 'C', 'K'};
        for (; q; q--) {
            char op = ops[rand() % 4];
            cout << op << " ";
            if (op != 'K') {
                int x = rand() % kMaxVal;
                int y = rand() % 2;
                if (y) {
                    x = -x;
                }
                cout << x << '\n';
            } else {
                int x = rand() % kMaxVal;
                cout << x << '\n';
            }
        }
    }

    return 0;
}
