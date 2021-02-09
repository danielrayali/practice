#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

struct History {
    int recent = -1;
    int earlier = -1;

    History() : recent(-1), earlier(-1) {}

    History(int _recent) : recent(_recent), earlier(-1) {}

    ~History() = default;
};

int Process(unordered_map<int, History>& memory, int& value, int turn) {
    auto iter = memory.find(value);
    if (iter == memory.end()) {
        // cout << "Creating node for value " << value << " on turn " << turn << endl;
        memory.emplace(value, turn);
        return 0;
    } else {
        // cout << "Memory found entry for " << value << " on turn " << turn << endl;
        int return_value = 0;
        if (iter->second.earlier != -1) {
            // cout << "Value has been said twice" << endl;
            return_value = (iter->second.recent - iter->second.earlier);
        } else {
            // cout << "Value has been said once" << endl;
            // cout << "Earlier: " << iter->second.earlier << endl;
            // cout << "Recent: " << iter->second.recent << endl;
        }

        iter = memory.find(return_value);
        if (iter == memory.end()) {
            memory.emplace(return_value, turn);
        } else {
            iter->second.earlier = iter->second.recent;
            iter->second.recent = turn;
            // cout << "Setting new values for " << return_value << endl;
            // cout << "Earlier: " << iter->second.earlier << endl;
            // cout << "Recent: " << iter->second.recent << endl;
        }
        return return_value;
    }
}

int main(int argc, char* argv[]) {
    ifstream input("d15s1.txt");
    unordered_map<int, History> memory;
    int turn = 1;
    int value = 0;
    while (!input.eof()) {
        string value_str;
        getline(input, value_str, ',');
        cout << "Turn/value: " << turn << "/" << value_str << endl;

        value = atoi(value_str.c_str());
        memory.emplace(value, turn);
        turn++;
    }

    for (int i = 0; i < 2020; i++) {
        value = Process(memory, value, turn);
        cout << "Turn/value: " << turn << "/" << value << endl;
        turn++;
    }

    return 0;
}
