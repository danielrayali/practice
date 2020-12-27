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
        if (count != 7) {
            return false;
        }

        for (int i = 0; i < keys.size(); ++i) {
            if (keys[i] == "byr") {
                if (values[i].size() != 4) {
                    return false;
                }
                int value = atoi(values[i].c_str());
                if ((value < 1920) || (value > 2002)) {
                    cout << "byr is bad: " << value << endl;
                    return false;
                }
            } else if (keys[i] == "iyr") {
                if (values[i].size() != 4) {
                    return false;
                }
                int value = atoi(values[i].c_str());
                if ((value < 2010) || (value > 2020)) {
                    cout << "iyr is bad: " << value << endl;
                    return false;
                }
            } else if (keys[i] == "eyr") {
                if (values[i].size() != 4) {
                    return false;
                }
                int value = atoi(values[i].c_str());
                if ((value < 2020) || (value > 2030)) {
                    cout << "eyr is bad: " << value << endl;
                    return false;
                }
            } else if (keys[i] == "hcl") {
                if (values[i].size() != 7) {
                    cout << "hcl is bad1: " << values[i] << endl;
                    return false;
                }
                if (values[i][0] != '#') {
                    cout << "hcl is bad2: " << values[i] << endl;
                    return false;
                }
                if (values[i].find_first_not_of("0123456789abcdef", 1) != string::npos) {
                    cout << "hcl is bad3: " << values[i] << endl;
                    return false;
                }
            } else if (keys[i] == "ecl") {
                static const set<string> colors = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
                if (colors.find(values[i]) == colors.end()) {
                    cout << "ecl is bad: " << values[i] << endl;
                    return false;
                }
            } else if (keys[i] == "pid") {
                if (values[i].size() != 9) {
                    cout << "pid is bad1: " << values[i] << endl;
                    return false;
                }
                if (values[i].find_first_not_of("0123456789") != string::npos) {
                    cout << "pid is bad2: " << values[i] << endl;
                    return false;
                }
            } else if (keys[i] == "hgt") {
                size_t pos = values[i].find("cm");
                if (pos != string::npos) {
                    string value_str = values[i].substr(0, pos);
                    int value = atoi(value_str.c_str());
                    if ((value < 150) || (value > 193)) {
                        cout << "hgt is bad1: " << values[i] << endl;
                        return false;
                    } else {
                        continue;
                    }
                }
                pos = values[i].find("in");
                if (pos != string::npos) {
                    string value_str = values[i].substr(0, pos);
                    int value = atoi(value_str.c_str());
                    if ((value < 59) || (value > 76)) {
                        cout << "hgt is bad2: " << values[i] << endl;
                        return false;
                    } else {
                        continue;
                    }
                }
                // If we couldn't find "cm" or "in", it is invalid
                cout << "hgt is bad3: " << values[i] << endl;
                return false;
            }
        }
        return true;
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
        bool is_valid = passport.IsValid();
        cout << "Validity: " << is_valid << endl;
        if (is_valid) {
            valid_passports++;
        }
    }

    cout << "Total number of valid passports: " << valid_passports << endl;
    return 0;
}
