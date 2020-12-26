#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input("d1s1.txt");
    vector<int> data;
    set<int> data_lookup;
    cout << "Read: ";
    while (!input.eof()) {
        int temp = 0;
        input >> temp;
        cout << temp << " ";
        data.emplace_back(temp);
        data_lookup.emplace(temp);
    }
    cout << endl;

    sort(data.begin(), data.end());
    cout << "Sorted: ";
    for (auto value : data) {
        cout << value << " ";
    }
    cout << endl;

    cout << "Finding three values that sum to 2020" << endl;
    for (auto outter : data) {
        for (auto inner : data) {
            int diff = abs(2020 - (outter + inner));
            if ((diff < 0) || (diff == outter) || (diff == inner)) {
                continue;
            }
            cout << "Considering " << outter << " and " << inner << ". Looking for " << diff << endl;
            if (data_lookup.find(diff) != data_lookup.end()) {
                cout << "Found three values that sum to 2020: " << outter << " " << inner << " " << diff << endl;
                cout << "Their product is " << outter * inner * diff << endl;
                return 0;
            }
        }
    }
    return 0;
}

