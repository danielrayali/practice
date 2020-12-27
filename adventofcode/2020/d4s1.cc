#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

struct Passport {
    vector<string> keys;
    vector<string> values;

    void Parse(const string& input) {
        string::size_type start_pos = 0;
        string::size_type end_pos;
        while (true) {
            // Find key
            start_pos = input.find_first_not_of(" ", start_pos);
            end_pos = input.find(":", start_pos);
            keys.push_back(input.substr(start_pos, (end_pos - start_pos)));

            // Find value
            start_pos = (end_pos + 1);
            end_pos = input.find(" ", start_pos);
            values.push_back(input.substr(start_pos, (end_pos - start_pos)));

            // Find start of the next one, or bail
            if (end_pos == string::npos) {
                break;
            }

            start_pos = (end_pos + 1);
        }
    }

    bool IsValid() const {
        // byr (Birth Year)
        // iyr (Issue Year)
        // eyr (Expiration Year)
        // hgt (Height)
        // hcl (Hair Color)
        // ecl (Eye Color)
        // pid (Passport ID)
        static set<string> required = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
        int count = 0;
        for (auto key : keys) {
            if (required.find(key) != required.end()) {
                count++;
            }
        }
        return (count == 7);
    }
};

ostream& operator<<(ostream& out, Passport passport) {
    out << "Parsed passport:          ";
    for (int i = 0; i < passport.keys.size(); ++i) {
        out << " " << passport.keys[i] << ":" << passport.values[i];
    }
    return out;
}

int main(int argc, char* argv[]) {
    ifstream input("d4s1.txt");
    vector<string> passport_strs;
    string passport_str;
    while (!input.eof()) {
        string line;
        getline(input, line);
        cout << "Read: " << line << endl;
        if (line != "") {
            passport_str += " ";
            passport_str += line;
        } else {
            passport_strs.push_back(passport_str);
            passport_str.clear();
        }
    }

    // We may bail out with valid passport string data. Add here.
    if (!passport_str.empty()) {
        passport_strs.emplace_back(passport_str);
    }

    int valid_passports = 0;
    for (auto passport_str : passport_strs) {
        cout << "Parsing passport string: \"" << passport_str << "\"" << endl;
        Passport passport;
        passport.Parse(passport_str);
        cout << passport << endl;
        cout << "Validity: " << passport.IsValid() << endl;
        if (passport.IsValid()) {
            valid_passports++;
        }
    }

    cout << "Total number of valid passports: " << valid_passports << endl;
    return 0;
}
