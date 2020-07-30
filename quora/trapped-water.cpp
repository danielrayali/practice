#include <iostream>
#include <vector>

using namespace std;

void FindMaxTrappedWater(int* data, int size) {
    int total_water = 0;
    vector<int> items;
    items.push_back(data[0]);
    for (int i = 1; i < size; ++i) {
        int items_popped = 0;
        while (items.back() < data[i]) {
            items_popped++;
            int item = items.back();
            total_water += (data[i] - item);
            items.pop_back();
        }
        for (int j = 0; j < items_popped + 1; ++j) {
            items.push_back(data[i]);
        }
    }
    cout << total_water << endl;
}

int main(int argc, char* argv[]) {
    const int size = 10;
    int data[size] = {7,0,4,2,5,0,6,4,0,5};
    FindMaxTrappedWater(data, size);
    return 0;
}

