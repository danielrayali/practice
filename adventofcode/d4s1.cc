#include <iostream>
#include <fstream>

using namespace std;

bool IsPassword(int number) {
    string num_str = to_string(number);
    // cout << "Processing string: " << num_str << endl;
    int prev = -1;
    bool double_found = false;
    for (size_t i = 0; i < num_str.size(); ++i) {
        int cur = num_str[i];
        if (cur < prev) {
            return false;
        } else if (cur == prev) {
            double_found = true;
        }
        prev = cur;
    }
    return double_found;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Give a file to parse" << endl;
        return 0;
    }

    string path(argv[1]);
    ifstream in(path);
    int start = 0, end = 0;
    in >> start;
    char temp;
    in >> temp;
    in >> end;

    cout << "Processing from " << start << " to " << end << endl;
    int num_passwords = 0;
    for (int i = start; i < end; ++i) {
        if (IsPassword(i)) {
            cout << "Password found: " << i << endl;
            num_passwords++;
        }
    }

    cout << "Num of passwords: " << num_passwords << endl;

    return 0;
}
