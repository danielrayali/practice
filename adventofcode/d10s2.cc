#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

// struct Point {
//     int x = 0;
//     int y = 0;

//     Point(int a, int b) : x(a), y(b) {}

//     Point(const Point& other) : x(other.x), y(other.y) {}
// };

// bool operator==(const Point& a, const Point& b) {
//     return (a.x == b.x) && (a.y == b.y);
// }

// double CalculateDistance(const Point a, const Point b) {
//     int x_a = a.x - b.x;
//     int y_a = a.y - b.y;
//     return sqrt(double(x_a * x_a) + double(y_a * y_a));
// }

// bool operator<(const Point& a, const Point& b) {
//     const double distance_a = CalculateDistance(a, kCenter);
//     const double distance_b = CalculateDistance(b, kCenter);
//     return distance_a < distance_b;
// }

// struct Slope {
//     int x = 0;
//     int y = 0;

//     Slope(const Point from, const Point to) {
//         this->x = to.x - from.x;
//         this->y = to.y - from.y;
//     }

//     Slope(int a, int b) : x(a), y(b) {}

//     Slope(const Slope& other) : x(other.x), y(other.y) {}
// };

// bool operator<(const Slope& a, const Slope& b) {
//     double slope_a(double(a.x) / double(a.y));
//     double slope_b(double(b.x) / double(b.y));
//     return slope_a < slope_b;
// }

// int CalculateGCD(const int a, const int b) {
//     if (b == 0) {
//         return a;
//     }
//     return CalculateGCD(b, a % b);
// }

// void SortLine(vector<Point>& line) {
//     sort(line.begin(), line.end());
// }

struct Point {
    int x;
    int y;

    Point(int a, int b) : x(a), y(b) {}

    double Magnitude() {
        return sqrt(x*x + y*y);
    }
};

Point operator-(const Point from, const Point to) {
    return Point(to.x - from.x, to.y - from.y);
}

static const Point kCenter(12,14);

double CalculateAngle(const Point point) {
    const double x_squared = pow(point.x, 2.0);
    const double y_squared = pow(point.y, 2.0);
    const double length = x_squared + y_squared;
    if (point.x >= 0.0 && point.y > 0.0) {
        // In upper right quadrant
        return (180.0 / M_PI) * atan(double(point.x) / double(point.y));
    } else if ((point.x > 0.0) && (point.y <= 0.0)) {
        // In lower right quadrant
        return (180.0 / M_PI) * (M_PI / 2.0 - atan(double(point.y) / double(point.x)));
    } else if ((point.x <= 0.0) && (point.y < 0.0)) {
        // In lower left quadrant
        return (180.0 / M_PI) * (M_PI + atan(double(point.x) / double(point.y)));
    } else if ((point.x < 0) && (point.y >= 0)) {
        // In upper left quadrant
        return (180.0 / M_PI) * (3.0*M_PI/2.0 - atan(double(point.y) / double(point.x)));
    } else {
        return 0.0;
    }
}

ostream& operator<<(ostream& out, const Point point) {
    out << "(" << point.x << "," << point.y << ")";
    return out;
}

void EraseLowest(vector<Point>& points) {
    auto lowest = points.begin();
    for (auto iter = points.begin(); iter != points.end(); iter++) {
        if (lowest->Magnitude() > iter->Magnitude()) {
            lowest = iter;
        }
    }
    cout << "Removing " << *lowest << endl;
    points.erase(lowest);
}

void PrintAsteroids(map<double, vector<Point>> asteroids) {
    for (auto)
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    string path(argv[1]);
    ifstream input(path);

    // Maps a GCD reduced slope to a set of points
    map<double, vector<Point>> asteroids;
    char temp;
    int x_pos = 1, y_pos = 1;
    while (input.get(temp)) {
        if (temp == '\n') {
            x_pos = 1;
            y_pos++;
        } else if (temp == '#') {
            Point absolute(x_pos, y_pos);
            Point relative = kCenter - absolute;
            double angle = CalculateAngle(relative);
            stringstream angle_str;
            angle_str << setprecision(7) << angle;
            cout << "Absolute: " << absolute << endl;
            cout << "Relative: " << relative << endl;
            cout << "Angle: " << angle_str.str() << endl;
            asteroids[atof(angle_str.str().c_str())].emplace_back(relative);
            x_pos++;
        }
    }

    // Collect keys
    vector<double> keys;
    for (auto iter : asteroids) {
        keys.push_back(iter.first);
    }

    bool all_empty = false;
    while (!all_empty) {
        all_empty = true;
        for (size_t i = 0; i < keys.size(); ++i) {
            auto iter = asteroids.find(keys[i]);
            if (iter->second.empty()) {
                continue;
            }
            all_empty = false;
            EraseLowest(iter->second);
        }
    }

    cout << "Done" << endl;

    // // Print for verification
    // for (auto line : asteroids) {
    //     cout << double(line.first.x) / double(line.first.y) << ": ";
    //     for (auto point : line.second) {
    //        cout << point.x << "/" << point.y << " (" << CalculateDistance(point, kCenter) << "), ";
    //     }
    //     cout << endl;
    // }

    return 0;
}
