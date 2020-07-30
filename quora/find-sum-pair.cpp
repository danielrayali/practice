#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintSumPairs(int* data, int size, int sum) {
    for (int left = 0; left < size; left++) {
        for (int right = left + 1; right < size; ++right) {
            if (data[left] + data[right] == sum) {
                cout << data[left] << "+" << data[right] << endl;
            }
        }
    }
}

void PrintSumPairsFaster(int* data, int size, int sum) {
    vector<int> vec(data, &data[size]);
    sort(vec.begin(), vec.end());
    int left = size / 2 - 1, right = size / 2;
    while (left > 0 && right < size) {
        if (vec[left] + vec[right] == sum) {
            cout << vec[left] << "+" << vec[right] << endl;
            if (right < size)
                right++;
            else if (left > 0)
                left--;
        } else if (vec[left] + vec[right] < sum) {
            right++;
        } else {
            left--;
        }
    }
}

int main(int argc, char* argv[]) {
    const int size = 6;
    int data[size] = { 8,7,2,5,3,1 };
    PrintSumPairs(data, size, 10);
    PrintSumPairsFaster(data, size, 10);
    return 0;
}

