#include <iostream>
#include <fstream>

using namespace std;

struct PasswordEntry {
    int lo_count = 0;
    int hi_count = 0;
    char letter = 'A';
    string password = "(empty)";
};

ostream& operator<<(ostream& out, const PasswordEntry& entry) {
    out << entry.lo_count << "-" << entry.hi_count << " ";
    out << entry.letter << ": " << entry.password;
    return out;
}

PasswordEntry ParsePasswordEntry(string& entry_str) {
    PasswordEntry password_entry;
    size_t lo_pos = entry_str.find_first_not_of("0123456789");
    string lo_str = entry_str.substr(0, lo_pos);
    password_entry.lo_count = atoi(lo_str.c_str());

    size_t hi_pos = entry_str.find_first_not_of("0123456789", (lo_pos + 1));
    string hi_str = entry_str.substr((lo_pos + 1), (hi_pos - lo_pos) + 1);
    password_entry.hi_count = atoi(hi_str.c_str());

    password_entry.letter = entry_str.at(hi_pos + 1);
    password_entry.password = entry_str.substr(hi_pos + 4);
    return password_entry;
}

bool IsEntryValid(PasswordEntry& password_entry) {
    bool lo_contains = (password_entry.password.at(password_entry.lo_count - 1) == password_entry.letter);
    bool hi_contains = (password_entry.password.at(password_entry.hi_count - 1) == password_entry.letter);
    cout << "Validation: " << lo_contains << " " << hi_contains << " " << (lo_contains ^ hi_contains) << endl;
    return lo_contains ^ hi_contains;
}

int main(int argc, char* argv[]) {
    ifstream input("d2s1.txt");
    int num_valid = 0;
    while (!input.eof()) {
        string temp;
        getline(input, temp);
        cout << "Read: " << temp << endl;

        PasswordEntry password_entry = ParsePasswordEntry(temp);
        cout << "Parsed entry: " << password_entry << endl;

        if (IsEntryValid(password_entry)) {
            num_valid++;
        }
    }
    cout << "Number of valid passwords: " << num_valid << endl;
    return 0;
}
