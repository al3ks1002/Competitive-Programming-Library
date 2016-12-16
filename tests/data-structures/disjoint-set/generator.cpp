#include <fstream>

using namespace std;

int main() {
    ofstream cout("test11.in");

    int n = 1e4;
    int m = 1e6;

    cout << n << " " << m << '\n';
    for (int i = 0; i < m; i++) {
        cout << (rand() & 1) + 1 << " " << rand() % n + 1
             << " " << rand() % n + 1 << '\n';
    }

    return 0;
}
