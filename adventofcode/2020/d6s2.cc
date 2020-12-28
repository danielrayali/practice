#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input("d6s1.txt");
    vector<vector<string>> groups;
    while (!input.eof()) {
        vector<string> group;
        string line;
        getline(input, line);
        while (line != "" && !input.eof()) {
            group.emplace_back(line);
            getline(input, line);
        }

        if (!line.empty()) {
            group.emplace_back(line);
        }

        if (!group.empty()) {
            groups.emplace_back(group);
        }
    }

    int count_total = 0;
    for (auto group : groups) {
        int counts[26];
        for (int i = 0; i < 26; i++) {
            counts[i] = 0;
        }

        cout << "Group:" << endl;
        for (auto person : group) {
            for (auto letter : person) {
                counts[letter - 'a']++;
            }
            cout << "  Person: " << person << endl;
        }
        cout << "Counts: ";
        for (int i = 0; i < 26; i++) {
            cout << counts[i] << " ";
            if (counts[i] == group.size()) {
                count_total++;
            }
        }
        cout << endl;
        cout << "Current count total: " << count_total << endl;
    }

    return 0;
}
