#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define Point pair<int, int>
#define x first
#define y second

class PointSet {
    public:
        explicit PointSet(const vector<Point>& points) : points_(points) {}

        double FindClosestPair() {
            sort(points_.begin(), points_.end());

            set<Point, YComparator> interesting_points;
            double closest_pair = kMaxInf;

            for (int left_p = 0, right_p = 0;
                    right_p < (int)points_.size(); right_p++) {
                long long current_solution = (long long)closest_pair + 1;

                while (left_p < right_p && current_solution + points_[left_p].x
                        < 1LL * points_[right_p].x) {
                    interesting_points.erase(points_[left_p++]);
                }

                Point aux = {0, (int)max(1LL * kMinCoordinate,
                                         1LL * points_[right_p].y - current_solution)
                            };
                for (auto it = interesting_points.lower_bound(aux);
                        it != interesting_points.end()
                        && 1LL * it->y <= current_solution + points_[right_p].y; it++) {
                    closest_pair = min(closest_pair, GetDistance(*it, points_[right_p]));
                }

                interesting_points.insert(points_[right_p]);
            }

            return closest_pair;
        }

    private:
        struct YComparator {
            bool operator () (const Point &a, const Point& b) const {
                return a.y < b.y;
            }
        };

        static double GetDistance(const Point& a, const Point& b) {
            return sqrt(1.0 * (a.x - b.x) * (a.x - b.x) + 1.0 * (a.y - b.y) * (a.y - b.y));
        }

        const int kMinCoordinate = -1e9;
        const double kMaxInf = 1e10;
        vector<Point> points_;
};

int main() {
    srand(time(0));
    cin.sync_with_stdio(false);

    int n;
    cin >> n;

    vector<Point> points;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    PointSet s(points);
    double answer = s.FindClosestPair();
    cout << fixed << setprecision(7) << answer << '\n';

    return 0;
}
