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
    int buffer[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; ++j) {
            buffer[i][j] = 2;
        }
    }
    while (in.peek() != EOF) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; ++j) {
                char temp[2] = {'\0', '\0'};
                in.read(temp, 1);
                value = atoi(temp);
                if (buffer[i][j] == 2) {
                    buffer[i][j] = value;
                }
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; ++j) {
            if (buffer[i][j] == 0) {
                cout << "X";
            } else if (buffer[i][j] == 1) {
                cout << " ";
            } else {
                cout << "E";
            }
        }
        cout << endl;
    }
    return 0;
}
