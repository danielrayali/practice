#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Process(vector<int>& codes) {
    for (int i = 0; i < codes.size(); ++i) {
        int op = codes[i] % 100;
        //cout << "op: " << codes[i] << endl;
        if (op == 99) {
            return;
        } else if (op == 1 || op == 2) {
            int lpos = codes[i + 1];
            if ((codes[i] % 1000) >= 100) {
                lpos = i + 1;
            }
            int rpos = codes[i + 2];
            if (codes[i] >= 1000) {
                rpos = i + 2;
            }

            // Output positions will never be in immediate mode
            int opos = codes[i + 3];
            if (op == 1) {
                // cout << "Positions: " << opos << "=" << lpos << "+" << rpos << endl;
                // cout << "Values:    " << codes[lpos] + codes[rpos] << "=" << codes[lpos] << "+" << codes[rpos] << endl;
                codes[opos] = codes[lpos] + codes[rpos];
            } else {
                // cout << "Positions: " << opos << "=" << lpos << "*" << rpos << endl;
                codes[opos] = codes[lpos] * codes[rpos];
                // cout << "Values:    " << codes[lpos] * codes[rpos] << "=" << codes[lpos] << "*" << codes[rpos] << endl;
            }
            i += 3;
        } else if (op == 3) {
            int pos = codes[i + 1];
            cout << "Provide input: ";
            int value = 0;
            cin >> value;

            codes[pos] = value;
            i++;
        } else if (op == 4) {
            int pos = codes[i + 1];
            if ((codes[i] % 1000) >= 100) {
                pos = i + 1;
            }
            cout << "Output operation: " << codes[pos] << endl;
            i++;
        } else {
            cerr << "Unknown op code" << endl;
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Give a file to parse" << endl;
        return 0;
    }

    vector<int> codes;
    string path(argv[1]);
    ifstream in(path);
    while (!in.eof()) {
        string current;
        getline(in, current, ',');
        codes.push_back(atoi(current.c_str()));
        // cout << "Code[" << codes.size()-1 << "]=" << codes.back() << endl;
    }

    Process(codes);

    // cout << "Output sequence: ";
    // for (int i = 0; i < codes.size(); ++i) {
    //     cout << codes[i] << " ";
    // }
    // cout << endl;

    return 0;
}
