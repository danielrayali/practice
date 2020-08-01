#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Point {
    int x;
    int y;
    int steps;

    Point(int _x, int _y, int _steps) : x(_x), y(_y), steps(_steps) {}
    Point() : x(0), y(0), steps(0) {}
};

// std::unordered_set does not know how to hash a pair. Provide the hash
// structure in the PointMap type to allow us to use a unordered_set<pair<int,int>>
struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first;
    }
};

typedef unordered_map<int, unordered_set<pair<int, int>, pair_hash>> PointMap;

Point AddPoints(const Point& origin, const string& move, PointMap& point_map) {
    int value = atoi(move.substr(1).c_str());
    Point next = origin;
    if (move[0] == 'R') {
        next.y += value;
        for (int i = origin.y + 1; i <= next.y; ++i) {
            next.steps++;
            point_map[origin.x].emplace(i, next.steps);
        }
    } else if (move[0] == 'L') {
        next.y -= value;
        for (int i = origin.y - 1; i >= next.y; --i) {
            next.steps++;
            point_map[origin.x].emplace(i, next.steps);
        }
    } else if (move[0] == 'U') {
        next.x += value;
        for (int i = origin.x + 1; i <= next.x; ++i) {
            next.steps++;
            point_map[i].emplace(origin.y, next.steps);
        }
    } else if (move[0] == 'D') {
        next.x -= value;
        for (int i = origin.x - 1; i >= next.x; --i) {
            next.steps++;
            point_map[i].emplace(origin.y, next.steps);
        }
    }
    return next;
}

vector<Point> GetPoints(Point& origin, const string& move) {
    int value = atoi(move.substr(1).c_str());
    int steps = origin.steps;
    vector<Point> points;
    if (move[0] == 'R') {
        for (int i = origin.y + 1; i <= (origin.y + value); ++i) {
            steps++;
            points.emplace_back(origin.x, i, steps);
        }
        origin.y += value;
    } else if (move[0] == 'L') {
        for (int i = origin.y - 1; i >= (origin.y - value); --i) {
            steps++;
            points.emplace_back(origin.x, i, steps);
        }
        origin.y -= value;
    } else if (move[0] == 'U') {
        for (int i = origin.x + 1; i <= (origin.x + value); ++i) {
            steps++;
            points.emplace_back(i, origin.y, steps);
        }
        origin.x += value;
    } else if (move[0] == 'D') {
        for (int i = origin.x - 1; i >= (origin.x - value); --i) {
            steps++;
            points.emplace_back(i, origin.y, steps);
        }
        origin.x -= value;
    }
    origin.steps = steps;
    return points;
}

int Find(const unordered_set<pair<int,int>, pair_hash>& data, const int pos) {
    for (const pair<int,int>& it : data) {
        if (it.first == pos) {
            return it.second;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Give a file to parse" << endl;
        return 0;
    }

    string path(argv[1]);
    ifstream in(path);
    string line;

    getline(in, line);
    stringstream linestream(line);
    string move;
    PointMap point_map;
    point_map[0].emplace(0, 0);
    Point position;
    while (getline(linestream, move, ',')) {
    //    cout << "Processing " << move << endl;
        position = AddPoints(position, move, point_map);
    }

    // for (auto out : point_map) {
    //     for (auto in : out.second) {
    //         cout << out.first << ", " << in << endl;
    //     }
    // }

    getline(in, line);
    stringstream linestream2(line);
    position.x = 0;
    position.y = 0;
    position.steps = 0;
    int lowest_distance = std::numeric_limits<int>::max();
    while (getline(linestream2, move, ',')) {
    //    cout << "Processing " << move << endl;
        vector<Point> points = GetPoints(position, move);
        for (auto point : points) {
            // cout << "Point steps: " << point.steps << endl;
            auto xit = point_map.find(point.x);
            if (xit != point_map.end()) {
                int steps = Find(xit->second, point.y);
                if (steps > -1) {
                    cout << "Intersection found: " << point.x << "," << point.y << endl;
                    cout << "First wire steps: " << steps << endl;
                    cout << "Second wire steps: " << point.steps << endl;
                    if (lowest_distance > (steps + point.steps)) {
                        lowest_distance = (steps + point.steps);
                    }
                }
            }
        }
    }

    cout << "Lowest distance: " << lowest_distance << endl;

    return 0;
}
