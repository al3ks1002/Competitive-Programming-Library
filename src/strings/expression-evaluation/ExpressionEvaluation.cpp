#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<ld, ld>
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second

template<class T>
class ExpressionEvaluation {
    public:
        ExpressionEvaluation(const string& expression) : expression_(expression) {}

        T Evaluate() {
            pointer_ = expression_.begin();
            return EvaluateExpression();
        }

    private:
        string expression_;
        string::iterator pointer_;

        T EvaluateExpression() {
            T result = EvaluateTerm();

            while (*pointer_ == '+' || *pointer_ == '-') {
                if (*pointer_ == '+') {
                    pointer_++;
                    result += EvaluateTerm();
                } else {
                    pointer_++;
                    result -= EvaluateTerm();
                }
            }

            return result;
        }

        T EvaluateTerm() {
            T result = EvaluateFactor();

            while (*pointer_ == '*' || *pointer_ == '/') {
                if (*pointer_ == '*') {
                    pointer_++;
                    result *= EvaluateFactor();
                } else {
                    pointer_++;
                    result /= EvaluateFactor();
                }
            }

            return result;
        }

        T EvaluateFactor() {
            T result = 0;

            if (*pointer_ == '(') {
                pointer_++;
                result = EvaluateExpression();
                pointer_++;
                return result;
            }

            while (*pointer_ >= '0' && *pointer_ <= '9') {
                result = result * 10 + *pointer_ - '0';
                pointer_++;
            }

            return result;
        }
};

int main() {
    cin.sync_with_stdio(false);

    string s;
    cin >> s;

    ExpressionEvaluation<int> expr(s);
    cout << expr.Evaluate() << '\n';

    return 0;
}
