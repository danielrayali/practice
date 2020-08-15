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

int GetOrbitCount(const unordered_map<string, Orbiter>& orbit_map,
                  const string& cur,
                  const string& prev) {
    int count = orbit_map.at(cur).center_of_masses.size();
    for (auto node : orbit_map.at(cur).center_of_masses) {
        // cout << "Current: " << cur << endl;
        // cout << "COM: " << node << endl;
        count += GetOrbitCount(orbit_map, node, cur);
    }
    return count;
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

    int count = 0;
    for (auto it : orbit_map) {
        count += GetOrbitCount(orbit_map, it.first, "");
    }
    cout << "Count is " << count << endl;

    return 0;
}
