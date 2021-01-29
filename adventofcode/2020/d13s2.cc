#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input("d13s1.txt");
    string arrival_str;
    getline(input, arrival_str);
    const long long earliest_start = atoll(arrival_str.c_str());
    cout << "Read: " << earliest_start << endl;

    vector<long long> bus_ids;
    while (!input.eof()) {
        string bus_id_str;
        getline(input, bus_id_str, ',');
        if (bus_id_str == "x") {
            bus_id_str = "1";
        }
        long long bus_id = atoll(bus_id_str.c_str());
        bus_ids.push_back(bus_id);
        cout << "Read: " << bus_id << endl;
    }

    // First find the largest jump we'll be able to do
    long long largest = -1;
    size_t largest_index = 0;
    for (size_t i = 0; i < bus_ids.size(); ++i) {
        if (bus_ids[i] > largest) {
            largest = bus_ids[i];
            largest_index = i;
        }
    }
    cout << "Largest bus ID: " << largest << endl;
    cout << "Largest bus ID index: " << largest_index << endl;

    // Find the first timestamp divisibe by the largest bus ID
    long long timestamp = earliest_start;
    while (timestamp != numeric_limits<long long>::max()) {
        if (timestamp % 571 == 0) {
            break;
        }
        timestamp++;
    }
    cout << "Largest timestamp found: " << timestamp << endl;

    // Subtract its position to get the timestamp that needs to match in index 0
    timestamp -= largest_index;

    // Iterate over all data that will match the largest
    int count = 0;
    while (true) {
        bool found = true;
        for (long long i = 0; i < bus_ids.size(); ++i) {
            if (((timestamp + i) % bus_ids[i]) != 0) {
                if (count > 100000000) {
                    cout << "Timestamp " << (timestamp + i) << " for index " << i;
                    cout << " doesn't work for bus ID " << bus_ids[i] << endl;
                    count = 0;
                }
                count++;
                found = false;
                break;
            }
        }
        if (found) {
            break;
        }

        timestamp += largest;
    }

    cout << "Timestamp: " << timestamp << endl;

    return 0;
}
