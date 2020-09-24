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
    size_t best_x, best_y;
    for (int y_a = 0; y_a < asteroids.size(); ++y_a) {
        for (int x_a = 0; x_a < asteroids.at(y_a).size(); ++x_a) {
            if (!asteroids.at(y_a).at(x_a)) {
                continue;
            }

            set<pair<int,int>> unique_slopes;
            for (int y_b = 0; y_b < asteroids.size(); ++y_b) {
                for (int x_b = 0; x_b < asteroids.at(y_b).size(); ++x_b) {
                    if (!asteroids.at(y_b).at(x_b)) {
                        continue;
                    }

                    if ((y_a == y_b) && (x_a == x_b)) {
                        continue;
                    }

                    int x_diff = y_a - y_b;
                    int y_diff = x_a - x_b;
                    int gcd = CalculateGCD(abs(x_diff), abs(y_diff));
                    unique_slopes.insert({x_diff / gcd, y_diff / gcd});
                }
            }
            if (unique_slopes.size() > max_unique_slopes) {
                max_unique_slopes = unique_slopes.size();
                best_x = x_a;
                best_y = y_a;
            }
        }
    }

    cout << "Max observable asteroids: " << max_unique_slopes << endl;
    cout << "Best location is at " << best_x << "," << best_y << endl;
    return 0;
}
