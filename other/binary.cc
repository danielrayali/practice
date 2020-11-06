#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <binary_left> <binary_right>" << endl;
        return 1;
    }
    string left(argv[1]);
    string right(argv[2]);
    bool overflow = false;
    string out;
    int left_idx = left.size() - 1;
    int right_idx = right.size() - 1;
    while (left_idx >= 0 || right_idx >= 0 || overflow) {
        int ones = (overflow ? 1 : 0);
        if (left_idx >= 0)
            ones += (left[left_idx] == '1' ? 1 : 0);
        if (right_idx >= 0)
            ones += (right[right_idx] == '1' ? 1 : 0);
        if (ones == 3) {
            out = '1' + out;
            overflow = true;
        } else if (ones == 2) {
            out = '0' + out;
            overflow = true;
        } else if (ones == 1) {
            out = '1' + out;
            overflow = false;
        } else {
            out = '0' + out;
            overflow = false;
        }
        left_idx--;
        right_idx--;
    }

    cout << out << endl;

    return 0;
}
