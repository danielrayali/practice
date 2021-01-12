#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

bool ContainsSumsValues(const deque<long long>& values, long long sum) {
    for (int i = 0; i < values.size(); ++i) {
        for (int j = 0; j < values.size(); ++j) {
            if (i == j) {
                continue;
            }
            const long long test = (values[i] + values[j]);
            if (test == sum) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    ifstream input("d9s1.txt");
    deque<long long> values;
    const int preamble_length = 25;
    while (!input.eof() && (values.size() != preamble_length)) {
        long long temp;
        input >> temp;
        cout << "Read: " << temp << endl;
        values.push_back(temp);
    }

    if (values.size() != preamble_length) {
        cout << "Not enough numbers to fill the preamble" << endl;
        return 0;
    }

    while (!input.eof()) {
        long long temp;
        input >> temp;
        cout << "Read: " << temp << endl;

        if (!ContainsSumsValues(values, temp)) {
            cout << "Value found that is not a sum of a pair of previous values" << endl;
            cout << "Value: " << temp << endl;
        }

        values.pop_front();
        values.push_back(temp);
    }

    return 0;
}
