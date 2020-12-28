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
        bitset<26> answers;
        cout << "Group:" << endl;
        for (auto person : group) {
            for (auto letter : person) {
                answers.set(letter - 'a');
            }
            cout << "  Person: " << person << " count=" << answers.count() << endl;
        }
        count_total += answers.count();
    }
    cout << "Count total: " << count_total << endl;

    return 0;
}
