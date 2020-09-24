#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Point {
    int x;
    int y;

    Point(int a, int b) : x(a), y(b) {}

    double Magnitude() {
        return sqrt(x*x + y*y);
    }
};

Point operator-(const Point to, const Point from) {
    return Point(to.x - from.x, to.y - from.y);
}

Point operator+(const Point a, const Point b) {
    return Point(a.x + b.x, a.y + b.y);
}

bool operator==(const Point a, const Point b) {
    return (a.x == b.x && a.y == b.y);
}

static const Point kCenter(22,19);

double CalculateAngle(const Point point) {
    const double x_squared = pow(point.x, 2.0);
    const double y_squared = pow(point.y, 2.0);
    const double length = x_squared + y_squared;
    if (point.x > 0.0 && point.y >= 0.0) {
        // In upper right quadrant
        return (180.0 / M_PI) * (M_PI/2.0 + atan(double(point.y) / double(point.x)));
    } else if ((point.x >= 0.0) && (point.y < 0.0)) {
        // In lower right quadrant
        return (180.0 / M_PI) * -atan(double(point.x) / double(point.y));
    } else if ((point.x < 0.0) && (point.y <= 0.0)) {
        // In lower left quadrant
        return (180.0 / M_PI) * (3.0*M_PI / 2.0 + atan(double(point.y) / double(point.x)));
    } else if ((point.x <= 0.0) && (point.y > 0.0)) {
        // In upper left quadrant
        return (180.0 / M_PI) * (M_PI - atan(double(point.x) / double(point.y)));
    } else {
        return 0.0;
    }
}

ostream& operator<<(ostream& out, const Point point) {
    out << "(" << point.x << "," << point.y << ")";
    return out;
}

// Returns the erased point
Point EraseLowest(vector<Point>& points) {
    auto lowest = points.begin();
    for (auto iter = points.begin(); iter != points.end(); iter++) {
        if (abs(lowest->Magnitude()) > abs(iter->Magnitude())) {
            lowest = iter;
        }
    }
    Point erased = *lowest;
    points.erase(lowest);
    return erased;
}

void PrintAsteroids(map<double, vector<Point>> asteroids, size_t dims) {
    vector<vector<char>> asteroids_map;
    for (int i = 0; i < dims; i++) {
        asteroids_map.push_back({});
        for (int j = 0; j < dims; j++) {
            asteroids_map[i].push_back('.');
        }
    }

    for (auto iter : asteroids) {
        for (auto point_iter : iter.second) {
            Point point = kCenter + point_iter;
            asteroids_map[point.y][point.x] = '#';
        }
    }

    for (int i = 0; i < dims; i++) {
        for (int j = 0; j < dims; j++) {
            cout << asteroids_map[i][j];
        }
        cout << endl;
    }
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
    int x_pos = 0, y_pos = 0;
    int count = 0;
    while (input.get(temp)) {
        if (temp == '\n') {
            x_pos = 0;
            y_pos++;
            continue;
        } else if (temp == '#') {
            Point absolute(x_pos, y_pos);
            if (absolute == kCenter) {
                x_pos++;
                continue;
            }
            Point relative = absolute - kCenter;
            double angle = CalculateAngle(relative);
            if (angle == -0.0) { angle = 0.0; }
            stringstream angle_str;
            angle_str << setprecision(10) << angle;
            asteroids[atof(angle_str.str().c_str())].emplace_back(relative);
            count++;
        }
        x_pos++;
    }
    cout << count << "/" << y_pos*y_pos << " asteroids registered" << endl;
    cout << "Using " << kCenter << " as the center" << endl;

    // Collect keys
    vector<double> keys;
    for (auto iter : asteroids) {
        keys.push_back(iter.first);
    }

    cout << "Some erased asteroids:" << endl;
    bool all_empty = false;
    count = 0;
    set<int> legend = {1,2,3,10,20,50,100,199,200,201,299};
    while (!all_empty) {
        all_empty = true;
        for (size_t i = 0; i < keys.size(); ++i) {
            auto iter = asteroids.find(keys[i]);
            if (iter->second.empty()) {
                continue;
            }
            all_empty = false;
            Point erased = EraseLowest(iter->second);
            count++;
            if (legend.find(count) != legend.end()) {
                cout << count << ": " << erased + kCenter << endl;
            }
            // PrintAsteroids(asteroids, y_pos);
            // cout << "--" << endl;
        }
    }
    return 0;
}
