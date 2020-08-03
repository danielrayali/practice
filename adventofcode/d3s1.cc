#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

struct Point {
    int x;
    int y;

    Point(int _x, int _y) : x(_x), y(_y) {}
    Point() : x(0), y(0) {}
};

typedef unordered_map<int, unordered_set<int>> PointMap;

Point AddPoints(const Point& origin, const string& move, PointMap& point_map) {
    int value = atoi(move.substr(1).c_str());
    Point next = origin;
    if (move[0] == 'R') {
        next.y += value;
        for (int i = origin.y + 1; i <= next.y; ++i) {
            point_map[origin.x].insert(i);
        }
    } else if (move[0] == 'L') {
        next.y -= value;
        for (int i = origin.y - 1; i >= next.y; --i) {
            point_map[origin.x].insert(i);
        }
    } else if (move[0] == 'U') {
        next.x += value;
        for (int i = origin.x + 1; i <= next.x; ++i) {
            point_map[i].insert(origin.y);
        }
    } else if (move[0] == 'D') {
        next.x -= value;
        for (int i = origin.x - 1; i >= next.x; --i) {
            point_map[i].insert(origin.y);
        }
    }
    return next;
}

vector<Point> GetPoints(Point& origin, const string& move) {
    int value = atoi(move.substr(1).c_str());
    vector<Point> points;
    if (move[0] == 'R') {
        for (int i = origin.y + 1; i <= (origin.y + value); ++i) {
            points.emplace_back(origin.x, i);
        }
        origin.y += value;
    } else if (move[0] == 'L') {
        for (int i = origin.y - 1; i >= (origin.y - value); --i) {
            points.emplace_back(origin.x, i);
        }
        origin.y -= value;
    } else if (move[0] == 'U') {
        for (int i = origin.x + 1; i <= (origin.x + value); ++i) {
            points.emplace_back(i, origin.y);
        }
        origin.x += value;
    } else if (move[0] == 'D') {
        for (int i = origin.x - 1; i >= (origin.x - value); --i) {
            points.emplace_back(i, origin.y);
        }
        origin.x -= value;
    }
    return points;
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
    point_map[0].insert(0);
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
    int lowest_distance = std::numeric_limits<int>::max();
    while (getline(linestream2, move, ',')) {
    //    cout << "Processing " << move << endl;
        vector<Point> points = GetPoints(position, move);
        for (auto point : points) {
            auto xit = point_map.find(point.x);
            if (xit != point_map.end()) {
                auto yit = xit->second.find(point.y);
                if (yit != xit->second.end()) {
                    cout << "Intersection found: " << point.x << "," << point.y << endl;
                    int distance = abs(point.x) + abs(point.y);
                    cout << "Distance from center: " << distance << endl;
                    if (distance < lowest_distance) {
                        lowest_distance = distance;
                    }
                }
            }
        }
    }

    cout << "Lowest distance: " << lowest_distance << endl;

    return 0;
}
