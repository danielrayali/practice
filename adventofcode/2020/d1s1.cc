#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input("d1s1.txt");
    vector<int> data;
    cout << "Read: ";
    while (!input.eof()) {
        int temp = 0;
        input >> temp;
        cout << temp << " ";
        data.emplace_back(temp);
    }
    cout << endl;

    sort(data.begin(), data.end());
    cout << "Sorted: ";
    for (auto value : data) {
        cout << value << " ";
    }
    cout << endl;

    cout << "Finding first two values that sum to 2020" << endl;
    auto left = data.begin();
    auto right = data.rbegin();
    while (*left < *right) {
        cout << "Considering " << *left << " and " << *right << endl;
        if (*left + *right < 2020) {
            left++;
        } else if (*left + *right > 2020) {
            right++;
        } else {
            cout << "Pair found: " << *left << " and " << *right << endl;
            cout << "Their product is " << *left * *right << endl;
            break;
        }
    }
    return 0;
}

