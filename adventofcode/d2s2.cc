#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

void Process(vector<int>& opcodes) {
    for (int i = 0; i < opcodes.size(); i += 4) {
        if (opcodes[i] == 99)
            break;

        int op = opcodes[i];
        int lpos = opcodes[i + 1];
        int rpos = opcodes[i + 2];
        int opos = opcodes[i + 3];
        if (op == 1) {
            opcodes[opos] = opcodes[lpos] + opcodes[rpos];
        } else if (op == 2) {
            opcodes[opos] = opcodes[lpos] * opcodes[rpos];
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Give a file to parse" << endl;
        return 0;
    }

    vector<int> opcodes;
    string path(argv[1]);
    ifstream in(path);
    cout << "Inputs: ";
    while (!in.eof()) {
        int current = 0;
        in >> current;
        char temp;
        in >> temp;
        opcodes.push_back(current);
        cout << current << " ";
    }
    cout << endl;

    // Apply error correction
    vector<int> attempt;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            attempt = opcodes;
            attempt[1] = i;
            attempt[2] = j;
            Process(attempt);
            if (attempt[0] == 19690720) {
                cout << "Noun: " << i << "\nVerb: " << j << endl;
                cout << "100 * " << i << " + " << j << " = " << 100 * i + j << endl;
                break;
            }
        }
    }

    return 0;
}
