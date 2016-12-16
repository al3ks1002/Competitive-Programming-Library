#include <fstream>
#include <sstream>

using namespace std;

const int kMaxN = 1e5;
const int kVal = 1e4;

// Not really a good generator
int main() {
    srand(time(0));

    for (int i = 0; i < 10; i++) {
        string test = "test";
        stringstream my_stream;
        string in = ".in";
        my_stream << test << i << in;
        string str = my_stream.str();
        ofstream cout(str);

        if (i == 0) {
            cout << 3 << '\n';
            cout << "8 9 5";
            continue;
        }

        int n;
        if (i < 7) {
            n = rand() % 100 + 1;
        } else {
            n = kMaxN;
        }

        cout << n << '\n';
        for (int j = 0; j < n; j++) {
            long long number = 0;
            if (i < 7) {
                number = rand() % kVal;
            } else {
                number = ((1LL * rand()) << 32) ^ rand();
            }
            cout << abs(number) << " ";
        }
    }

    return 0;
}
