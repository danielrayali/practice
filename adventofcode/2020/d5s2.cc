#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void GetLowRange(int low, int high, int& low_out, int& high_out) {
    int mid = (high + low) / 2;
    low_out = low;
    high_out = mid;
}

void GetHighRange(int low, int high, int& low_out, int& high_out) {
    int mid = (high + low) / 2 + 1;
    low_out = mid;
    high_out = high;
}

int main(int argc, char* argv[]) {
    ifstream input("d5s1.txt");
    vector<string> inputs;
    while (!input.eof()) {
        string temp;
        input >> temp;
        cout << "Read: " << temp << endl;
        inputs.emplace_back(temp);
    }

    vector<int> seat_ids;
    for (auto input : inputs) {
        int low = 0, high = 127;
        for (int i = 0; i < 7; i++) {
            cout << "Input: " << input[i] << endl;
            if (input[i] == 'F') {
                cout << "Old range: " << low << " - " << high << endl;
                GetLowRange(low, high, low, high);
                cout << "New range: " << low << " - " << high << endl;
            }
            if (input[i] == 'B') {
                cout << "Old range: " << low << " - " << high << endl;
                GetHighRange(low, high, low, high);
                cout << "New range: " << low << " - " << high << endl;
            }
        }

        if (low != high) {
            cout << "Did not determine the row: " << low << " - " << high << endl;
            return 0;
        }

        int row = low;
        low = 0;
        high = 7;
        for (int i = 0 + 7; i < 3 + 7; i++) {
            cout << "Input: " << input[i] << " ";
            if (input[i] == 'R') {
                cout << "Old range: " << low << " - " << high << endl;
                GetHighRange(low, high, low, high);
                cout << "New range: " << low << " - " << high << endl;
            }
            if (input[i] == 'L') {
                cout << "Old range: " << low << " - " << high << endl;
                GetLowRange(low, high, low, high);
                cout << "New range: " << low << " - " << high << endl;
            }
        }

        if (low != high) {
            cout << "Did not determine the column: " << low << " - " << high << endl;
            return 0;
        }

        int column = low;
        cout << "Determined row and column: " << row << " " << column << endl;
        int seat_id = row * 8 + column;
        cout << "Seat ID: " << seat_id << endl;
        seat_ids.push_back(seat_id);
    }

    sort(seat_ids.begin(), seat_ids.end());
    for (int i = 1; i < seat_ids.size(); ++i) {
        if ((seat_ids[i] - seat_ids[i - 1]) == 2) {
            cout << "Found missing seat id between: " << seat_ids[i - 1] << " " << seat_ids[i] << endl;
            break;
        }
    }
    return 0;
}
