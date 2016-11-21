#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class ConvexHullGraham {
    public:
        struct Point {
            double x_;
            double y_;

            Point() : x_(0.0), y_(0.0) {};

            Point(double x_, double y_) : x_(x_), y_(y_) {};

            Point& operator =(const Point& other) {
                this->x_ = other.x_;
                this->y_ = other.y_;
                return *this;
            }

            Point& operator =(const pair<double, double>& other) {
                this->x_ = other.first;
                this->y_ = other.second;
                return *this;
            }
        };

        ConvexHullGraham(const vector<pair<double, double>>& input_points) {
            int sentinel_index = 0;
            pair<double, double> sentinel = input_points[0];

            int current_index = 0;
            for (auto& point : input_points) {
                points_.emplace_back(point.first, point.second);
                if (point < sentinel) {
                    sentinel = point;
                    sentinel_index = current_index;
                }
                current_index++;
            }

            sentinel_ = sentinel;
            swap(points_[0], points_[sentinel_index]);
        }

        vector<pair<double, double>> GetConvexHull() {
            sort(points_.begin() + 1, points_.end(), PolarComparator(this));

            vector<Point> stack;
            for (auto& point : points_) {
                int size = stack.size();
                while (size >= 2
                        && CrossProduct(stack[size - 2], stack[size - 1], point) < 0) {
                    stack.pop_back();
                    size--;
                }
                stack.push_back(point);
            }

            vector<pair<double, double>> convex_hull;
            for (auto& point : stack) {
                convex_hull.emplace_back(point.x_, point.y_);
            }

            return convex_hull;
        }


    private:
        vector<Point> points_;
        Point sentinel_;

        static double CrossProduct(const Point& a, const Point& b, const Point& c) {
            return (b.x_ - a.x_) * (c.y_ - a.y_) - (c.x_ - a.x_) * (b.y_ - a.y_);
        }

        struct PolarComparator {
            ConvexHullGraham* parent_class_;

            PolarComparator(ConvexHullGraham* parent_class) : parent_class_(parent_class) {}

            bool operator() (const Point& a, const Point& b) const {
                return CrossProduct(parent_class_->sentinel_, a, b) > 0;
            }
        };
};

int main() {
    cin.sync_with_stdio(false);

    int n;
    cin >> n;

    vector<pair<double, double>> points_;
    for (int i = 0; i < n; i++) {
        double x;
        double y;
        cin >> x >> y;
        points_.emplace_back(x, y);
    }

    ConvexHullGraham ch(points_);
    vector<pair<double, double>> ans = ch.GetConvexHull();

    cout << ans.size() << '\n';
    for (auto& it : ans) {
        cout << fixed << setprecision(8) << it.first << " " << it.second << '\n';
    }

    return 0;
}
