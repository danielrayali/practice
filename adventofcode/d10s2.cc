#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Point {
    int x = 0;
    int y = 0;

    Point(int a, int b) : x(a), y(b) {}

    Point(const Point& other) : x(other.x), y(other.y) {}
};

bool operator==(const Point& a, const Point& b) {
    return (a.x == b.x) && (a.y == b.y);
}

static const Point kCenter(12,14);

double CalculateDistance(const Point a, const Point b) {
    int x_a = a.x - b.x;
    int y_a = a.y - b.y;
    return sqrt(double(x_a * x_a) + double(y_a * y_a));
}

bool operator<(const Point& a, const Point& b) {
    const double distance_a = CalculateDistance(a, kCenter);
    const double distance_b = CalculateDistance(b, kCenter);
    return distance_a < distance_b;
}

struct Slope {
    int x = 0;
    int y = 0;

    Slope(int a, int b) : x(a), y(b) {}

    Slope(const Slope& other) : x(other.x), y(other.y) {}
};

bool operator<(const Slope& a, const Slope& b) {
    double slope_a(double(a.x) / double(a.y));
    double slope_b(double(b.x) / double(b.y));
    return slope_a < slope_b;
}

int CalculateGCD(const int a, const int b) {
    if (b == 0) {
        return a;
    }
    return CalculateGCD(b, a % b);
}

void SortLine(vector<Point>& line) {
    sort(line.begin(), line.end());
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    string path(argv[1]);
    ifstream input(path);

    // Maps a GCD reduced slope to a set of points
    map<Slope, vector<Point>> asteroids;
    char temp;
    int x_pos = 1, y_pos = 1;
    while (input.get(temp)) {
        if (temp == '\n') {
            x_pos = 1;
            y_pos++;
        } else if (temp == '#') {
            int x_diff = x_pos - kCenter.x;
            int y_diff = y_pos - kCenter.y;
            int x_slope = x_diff;
            int y_slope = y_diff;
            int gcd = 1;
            if (x_diff != 0 && y_diff != 0) {
                gcd = CalculateGCD(x_diff, y_diff);
            }
            if (x_diff == 0) {
                if (y_diff > 0) {
                    x_slope = numeric_limits<int>::max();
                } else {
                    x_slope = numeric_limits<int>::min();
                }
            } else {
                x_slope /= gcd;
            }
            if (y_diff == 0) {
                if (x_diff > 0) {
                    y_slope = numeric_limits<int>::max();
                } else {
                    y_slope = numeric_limits<int>::min();
                }
            } else {
                y_slope /= gcd;
            }
            Slope slope(x_slope, y_slope);
            asteroids[slope].emplace_back(x_pos, y_pos);
            x_pos++;
        }
    }

    // Sort points by their distance from the center
    for (auto &line : asteroids) {
        SortLine(line.second);
    }

    // Print for verification
    for (auto line : asteroids) {
        cout << double(line.first.x) / double(line.first.y) << ": ";
        for (auto point : line.second) {
           cout << point.x << "/" << point.y << " (" << CalculateDistance(point, kCenter) << "), ";
        }
        cout << endl;
    }

    return 0;
}
