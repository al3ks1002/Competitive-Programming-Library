#include <fstream>
#include <sstream>

using namespace std;

const int kMaxN = 1e3;

int main() {
    srand(time(0));

    for (int i = 1; i <= 10; i++) {
        string test = "test";
        stringstream my_stream;
        string in = ".in";
        my_stream << test << i << in;
        string str = my_stream.str();
        ofstream cout(str);
    }

    return 0;
}
