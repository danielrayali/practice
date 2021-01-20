#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input("d10s1.txt");
    vector<int> values;
    int max = -1;
    while (!input.eof()) {
        int temp;
        input >> temp;
        cout << "Read: " << temp << endl;
        values.push_back(temp);
        if (temp > max) {
            max = temp;
        }
    }

    if (max == -1) {
        cout << "Max value never changed" << endl;
        return 0;
    }

    values.push_back(max + 3);
    values.push_back(0);
    sort(values.begin(), values.end());

    int one_diffs = 0, three_diffs = 0;
    for (int i = 0; i < (values.size() - 1); ++i) {
        if ((values[i + 1] - values[i]) == 1) {
            one_diffs++;
        } else if ((values[i + 1] - values[i]) == 3) {
            three_diffs++;
        }
        if ((values[i + 1] - values[i]) > 3) {
            cout << "Found a pair with a difference higher than 3: ";
            cout << values[i + 1] << " " << values[i] << endl;
        }
    }
    cout << "Number of differences by one: " << one_diffs << endl;
    cout << "Number of differences by three: " << three_diffs << endl;
    cout << "Product of one and three differences: " << one_diffs * three_diffs << endl;
    return 0;
}
