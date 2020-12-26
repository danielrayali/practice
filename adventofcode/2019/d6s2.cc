#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

struct Orbiter {
    vector<string> center_of_masses;  // Objects that this orbits
    vector<string> orbiters;  // Things that orbit this object
};

void FindPaths(const unordered_map<string, Orbiter>& orbit_map,
               const string& cur,
               const string& prev,
               const string& to,
               vector<int>& paths,
               int current_value) {
    for (auto center : orbit_map.at(cur).center_of_masses) {
        if (center == prev) {
            continue;
        }
        if (center == to) {
            paths.push_back(current_value);
        } else {
            FindPaths(orbit_map, center, cur, to, paths, current_value + 1);
        }
    }
    for (auto orbiter : orbit_map.at(cur).orbiters) {
        if (orbiter == prev) {
            continue;
        }
        if (orbiter == to) {
            paths.push_back(current_value);
        } else {
            FindPaths(orbit_map, orbiter, cur, to, paths, current_value + 1);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Give a file to parse" << endl;
        return 0;
    }

    string center, orbital;
    unordered_map<string, Orbiter> orbit_map;
    ifstream input(argv[1]);
    int num_orbits = 0;
    while (!input.eof()) {
        getline(input, center, ')');
        getline(input, orbital);

        auto it = orbit_map.find(center);
        if (it != orbit_map.end()) {
            it->second.orbiters.push_back(orbital);
        } else {
            orbit_map.emplace(make_pair(center, Orbiter()));
            orbit_map[center].orbiters.push_back(orbital);
        }

        it = orbit_map.find(orbital);
        if (it != orbit_map.end()) {
            it->second.center_of_masses.push_back(center);
        } else {
            orbit_map.emplace(make_pair(orbital, Orbiter()));
            orbit_map[orbital].center_of_masses.push_back(center);
        }
    }

    int lowest_path = numeric_limits<int>::max();
    vector<int> paths;
    FindPaths(orbit_map, "YOU", "", "SAN", paths, 0);
    for (auto path : paths) {
        if (path < lowest_path) {
            lowest_path = path;
        }
    }
    cout << "Lowest path is " << lowest_path - 1 << endl;
    return 0;
}
