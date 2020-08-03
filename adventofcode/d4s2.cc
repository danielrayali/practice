#include <iostream>
#include <fstream>
#include <vector>

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

bool ContainsEvenRepeats(int number) {
    string num_str = to_string(number);
    int prev = -1, cur = 0;
    int repeats = 0;
    for (size_t i = 0; i < num_str.size(); ++i) {
        cur = static_cast<int>(num_str[i]);
        if (prev == cur) {
            repeats++;
            prev = cur;
            continue;
        } else if ((repeats > 0) && ((repeats & 0x1) == 0)) {
            return true;
        }
        repeats = 0;
        prev = cur;
    }
    if ((repeats > 0) && ((repeats & 0x1) == 0)) {
        return true;
    }
    return false;
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
    vector<int> old_passwords;
    for (int i = start; i < end; ++i) {
        if (IsPassword(i)) {
            cout << "Password found: " << i << endl;
            old_passwords.push_back(i);
        }
    }

    int num_passwords = 0;
    for (auto password : old_passwords) {
        if (!ContainsEvenRepeats(password)) {
            num_passwords++;
        } else {
            cout << "Password eliminated: " << password << endl;
        }
    }

    cout << "Num of passwords: " << num_passwords << endl;

    return 0;
}
