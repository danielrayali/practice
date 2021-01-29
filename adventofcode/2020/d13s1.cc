#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input("d13s1.txt");
    string arrival_str;
    getline(input, arrival_str);
    const int earliest_start = atoi(arrival_str.c_str());
    cout << "Read: " << earliest_start << endl;

    vector<int> bus_ids;
    while (!input.eof()) {
        string bus_id_str;
        getline(input, bus_id_str, ',');
        if (bus_id_str == "x") {
            continue;
        }
        int bus_id = atoi(bus_id_str.c_str());
        bus_ids.push_back(bus_id);
        cout << "Read: " << bus_id << endl;
    }

    int earliest = earliest_start - 1;
    int earliest_bus_id = 0;
    while (earliest_bus_id == 0) {
        earliest++;
        for (auto bus_id : bus_ids) {
            if ((earliest % bus_id) == 0) {
                earliest_bus_id = bus_id;
                break;
            }
        }
    }

    cout << "Earliest departure identified" << endl;
    cout << "Earliest departure time: " << earliest << endl;
    cout << "Earliest departure bus ID: " << earliest_bus_id << endl;

    const int time_to_wait = (earliest - earliest_start);
    cout << "Time to wait: " << time_to_wait << endl;
    cout << "Product of time to wait and earliest bus ID: " << time_to_wait * earliest_bus_id << endl;

    return 0;
}