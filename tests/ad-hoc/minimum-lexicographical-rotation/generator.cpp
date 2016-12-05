#include <fstream>
#include <sstream>

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
            n = rand() % 20 + 1;
        } else if (i <= 7) {
            n = rand() % kMaxN + 1;
        } else {
            n = kMaxN;
        }

        for (int i = 0; i < n; i++) {
            cout << (char)(rand() % ('z' - 'a' + 1) + 'a');
        }
    }

    return 0;
}
