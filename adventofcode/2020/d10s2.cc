#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// nums:     0  3  4  5 6 7 8 9 10 14
// # paths:                 ? 1  1  1

// nums:     0  3  4  5 6 7 8 9 10 14
// # paths:               ? 2 1  1  1

// nums:     0  3  4  5 6 7 8 9 10 14
// # paths:             ? 4 2 1  1  1

// nums:     0  3  4  5 6 7 8 9 10 14
// # paths:           ? 7 4 2 1  1  1

// nums:     0  3  4  5 6 7 8 9 10 14
// # paths:        ? 13 7 4 2 1  1  1

// nums:     0  3  4  5 6 7 8 9 10 14
// # paths:     ? 24 13 7 4 2 1  1  1

// nums:     0  3  4  5 6 7 8 9 10 14
// # paths: 44 44 24 13 7 4 2 1  1  1

unsigned long long CountJoltagePaths(const vector<int>& values) {
    vector<unsigned long long> paths(values.size(), 1);
    for (int i = (values.size() - 2); i >= 0; i--) {
        paths[i] = paths[i + 1];
        for (int j = 2; j < 4; j++) {
            if ((i + j) >= values.size()) {
                continue;
            } else if ((values[i + j] - values[i]) < 4) {
                paths[i] += paths[i + j];
            }
        }
    }
    return paths[0];
}

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

    unsigned long long num_paths = CountJoltagePaths(values);
    cout << "Number of Joltage adapter arrangements: " << num_paths << endl;
    return 0;
}
