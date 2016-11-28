#include <fstream>
#include <sstream>

using namespace std;

const int kMaxN = 2e6;

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
        if (i < 9) {
            n = kMaxN / 4;
        } else {
            n = kMaxN;
        }

        cout << n << '\n';
        for (; n; n--) {
            cout << rand() << '\n';
        }
    }

    return 0;
}
