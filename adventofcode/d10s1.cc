#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

struct Point {
    int x = 0;
    int y = 0;
};

int CalculateGCD(const int a, const int b) {
    if (b == 0) {
        return a;
    }
    return CalculateGCD(b, a % b);
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
            asteroids.back().push_back(true);
        } else {
            asteroids.back().push_back(false);
        }
    }

    size_t max_unique_slopes = 0;
    for (int x_left = 0; x_left < asteroids.size(); ++x_left) {
        for (int y_left = 0; y_left < asteroids.at(x_left).size(); ++y_left) {
            if (!asteroids.at(x_left).at(y_left)) {
                continue;
            }

            set<pair<int,int>> unique_slopes;
            for (int x_right = 0; x_right < asteroids.size(); ++x_right) {
                for (int y_right = 0; y_right < asteroids.at(x_right).size(); ++y_right) {
                    if (!asteroids.at(x_right).at(y_right)) {
                        continue;
                    }

                    if ((x_left == x_right) && (y_left == y_right)) {
                        continue;
                    }

                    int x_diff = x_left - x_right;
                    int y_diff = y_left - y_right;
                    int gcd = CalculateGCD(abs(x_diff), abs(y_diff));
                    unique_slopes.insert({x_diff / gcd, y_diff / gcd});
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
