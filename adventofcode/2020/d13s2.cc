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
        if (bus_id_str != "1") {
            cout << "Read: x = " << (bus_ids.size() - 1) << " mod " << bus_id << endl;
        }
    }

    long long product = 1;
    for (auto bus_id : bus_ids) {
        product *= bus_id;
    }

    vector<long long> y;
    for (auto bus_id : bus_ids) {
        y.push_back(product / bus_id);
    }

    vector<long long> z;
    for (int i = 0; i < y.size(); ++i) {
        z.push_back((1/y[i]) % bus_ids[i]);
    }

    int timestamp = 0;
    for (int i = 0; i < y.size(); ++i) {
        timestamp += i * y[i] * z[i];
    }

    cout << "Timestamp: " << timestamp << endl;

    return 0;
}
