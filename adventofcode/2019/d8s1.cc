#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Give a file to parse" << endl;
        return 0;
    }

    string path(argv[1]);
    ifstream in(path);
    int value = 0;
    const int width = 25;
    const int height = 6;
    int min_zeros = numeric_limits<int>::max();
    int result = -1;
    while (in.peek() != EOF) {
        int counts[3] = {0,0,0};
        for (int i = 0; i < width * height; ++i) {
            char temp[2] = {'\0', '\0'};
            in.read(temp, 1);
            value = atoi(temp);
            counts[value]++;
        }
        if (counts[0] < min_zeros) {
            min_zeros = counts[0];
            result = counts[1] * counts[2];
        }
    }
    // 2376 is too low
    cout << "Result: " << result << endl;
    return 0;
}
