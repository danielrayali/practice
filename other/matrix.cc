#include <iostream>
#include <vector>

using namespace std;

// Input assumed square, equal length row/column, pass x/y of the "top" value
void RotatePoint(vector<vector<int>>& input, int x, int y) {
    int top_y = y;
    int top_x = x;
    int right_y = x;
    int right_x = input[right_y].size() - (y + 1);
    int bottom_y = input.size() - (y + 1);
    int bottom_x = input[bottom_y].size() - (x + 1);
    int left_y = input.size() - (x + 1);
    int left_x = y;

    int temp = input[top_y][top_x];
    input[top_y][top_x] = input[right_y][right_x];
    input[right_y][right_x] = input[bottom_y][bottom_x];
    input[bottom_y][bottom_x] = input[left_y][left_x];
    input[left_y][left_x] = temp;
}

int main(int argc, char* argv[]) {
    vector<vector<int>> input;
    for (int i = 0; i < 10; i++) {
        input.push_back({});
        for (int j = 0; j < 10; j++) {
            input.at(i).push_back(i*10 + j);
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << input[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--" << endl;

    for (int i = 0; i < input.size() / 2; ++i) {
        for (int j = i; j < input.size() - (1 + i); ++j) {
            RotatePoint(input, j, i);
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << input[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
