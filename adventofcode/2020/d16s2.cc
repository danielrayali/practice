#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

typedef vector<pair<int, int>> Ranges;
typedef map<string, Ranges> Fields;

vector<string> Split(string input, string delim) {
    vector<string> output;
    size_t pos = 0, last = 0;
    while (pos < input.size()) {
        while ((pos < input.size()) && (input.substr(pos, delim.size()) != delim)) {
            pos++;
        }
        output.push_back(input.substr(last, (pos - last)));
        last = pos + delim.size();
        pos = last;
    }

    return output;
}

bool IsValueValid(const int value, const Ranges& ranges) {
    for (auto range : ranges) {
        if ((value >= range.first) && (value <= range.second)) {
            return true;
        }
    }
    return false;
}

bool IsValueValid(const int value, const Fields& fields) {
    for (auto field : fields) {
        if (IsValueValid(value, field.second)) {
            return true;
        }
    }
    return false;
}

bool IsTicketValid(const vector<int> ticket, const Fields& fields, int* invalid) {
    for (auto value : ticket) {
        if (!IsValueValid(value, fields)) {
            if (invalid != nullptr) {
                *invalid = value;
            }
            return false;
        }
    }
    return true;
}

vector<int> GetTicketValues(const string& line) {
    vector<string> ticket_values_str = Split(line, ",");
    vector<int> ticket_values;
    for (auto cur_value_str : ticket_values_str) {
        ticket_values.push_back(atoi(cur_value_str.c_str()));
    }
    return ticket_values;
}

void PrintFields(const vector<Fields>& fields) {
    cout << "Size of each possible fields: ";
    for (auto iter : fields) {
        cout << iter.size() << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    ifstream input("d16s1.txt");
    string line;
    Fields all_fields;
    getline(input, line);
    while (!line.empty()) {
        cout << "Read: " << line << endl;
        vector<string> name_split = Split(line, ":");
        vector<string> range_split = Split(name_split[1], " or ");
        vector<pair<int,int>> ranges;
        for (auto cur : range_split) {
            cout << "Range split: " << cur << endl;
            vector<string> min_max_split = Split(cur, "-");
            int min = atoi(min_max_split[0].c_str());
            int max = atoi(min_max_split[1].c_str());
            ranges.emplace_back(min, max);
        }
        all_fields.emplace(name_split[0], move(ranges));
        getline(input, line);
    }

    // Read "your ticket:"
    getline(input, line);

    // Read the ticket values
    getline(input, line);
    vector<int> ticket_values = GetTicketValues(line);

    // Validate your ticket
    if (!IsTicketValid(ticket_values, all_fields, nullptr)) {
        cout << "Your ticket is not valid" << endl;
        return 0;
    }

    getline(input, line);  // Read newline
    getline(input, line);  // Read "nearby tickets:"

    // Set up all possible fields to deduce field
    vector<Fields> possible_fields(ticket_values.size(), all_fields);

    // Read neaby ticket values
    int count = 0;
    while (!input.eof()) {
        getline(input, line);
        cout << "Read: " << line << endl;
        ticket_values = GetTicketValues(line);
        int invalid = 0;
        if (!IsTicketValid(ticket_values, all_fields, &invalid)) {
            count += invalid;
            continue;
        }

        for (size_t i = 0; i < ticket_values.size(); i++) {
            Fields remaining = possible_fields[i];
            bool erase_occurred = false;
            for (auto read_iter : possible_fields[i]) {
                auto write_iter = remaining.find(read_iter.first);
                if (!IsValueValid(ticket_values[i], write_iter->second)) {
                    cout << ticket_values[i] << " not valid for " << write_iter->first << " ";
                    for (auto range_iter : write_iter->second) { cout << range_iter.first << "-" << range_iter.second << " "; }
                    cout << endl;
                    remaining.erase(write_iter);
                    erase_occurred = true;
                }
            }

            PrintFields(possible_fields);
            possible_fields[i] = remaining;
            PrintFields(possible_fields);
            if (erase_occurred && (possible_fields[i].size() == 1)) {
                vector<int> to_remove;
                to_remove.push_back(i);
                while (to_remove.size() > 0) {
                    int current_index = to_remove.back();
                    to_remove.pop_back();
                    auto iter = possible_fields[current_index].begin();
                    cout << "Removing " << iter->first << " from all others" << endl;
                    for (int j = 0; j < ticket_values.size(); j++) {
                        if (current_index == j) {
                            continue;
                        }
                        if ((possible_fields[j].erase(iter->first) > 0) && (possible_fields[j].size() == 1)) {
                            to_remove.push_back(j);
                        }
                    }
                }
            }
        }
    }

    cout << "Size of each possible fields: ";
    for (auto iter : possible_fields) {
        cout << iter.size() << " ";
    }
    cout << endl;

    cout << "Field attributes: ";
    for (auto iter : possible_fields) {
        cout << iter.begin()->first << "|";
    }
    cout << endl;

    // Answer:
    // 139 departure time
    // 61 departure station
    // 101 departure track
    // 53 departure location
    // 59 departure platform
    // 137 departure date
    // 139*61*101*53*59*137=366871907221

    cout << "Count is " << count << endl;
    return 0;
}
