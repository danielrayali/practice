#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

struct Point {
    float x;
    float y;
};

float CalculateSlope(const Point first, const Point second) {
    return sqrt(pow((second.x - first.x), 2.0f) + pow((second.y - first.y), 2.0f));
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    string path(argv[1]);
    ifstream input(path);
    vector<vector<bool>> asteroids(1);
    char temp;
    while (input.get(temp)) {
        if (temp == '\n') {
            asteroids.emplace_back();
        } else if (temp == '#') {
            asteroids.back().emplace_back(true);
        } else {
            asteroids.back().emplace_back(false);
        }
    }

    size_t max_unique_slopes = 0;
    for (int x_left = 0; x_left < asteroids.size(); ++x_left) {
        for (int y_left = 0; y_left < asteroids.at(x_left).size(); ++y_left) {
            Point left;
            left.x = x_left;
            left.y = y_left;
            unordered_set<float> unique_slopes;
            for (int x_right = 0; x_right < asteroids.size(); ++x_right) {
                for (int y_right = 0; y_right < asteroids.at(x_right).size(); ++y_right) {
                    Point right;
                    right.x = x_right;
                    right.y = y_right;
                    float slope = CalculateSlope(left, right);
                    unique_slopes.insert(slope);
                }
            }
            if (unique_slopes.size() > max_unique_slopes) {
                max_unique_slopes = unique_slopes.size();
            }
        }
    }

    cout << "Max observable asteroids: " << max_unique_slopes << endl;
    return 0;
}
