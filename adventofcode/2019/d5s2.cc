#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Process(vector<int>& codes) {
    for (int i = 0; i < codes.size(); ++i) {
        int op = codes[i] % 100;
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
                codes[opos] = codes[lpos] + codes[rpos];
            } else {
                codes[opos] = codes[lpos] * codes[rpos];
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
        } else if ((op == 5) || (op == 6)) {
            int tpos = codes[i + 1];
            if ((codes[i] % 1000) >= 100) {
                tpos = i + 1;
            }
            int vpos = codes[i + 2];
            if ((codes[i] % 10000) >= 1000) {
                vpos = i + 2;
            }

            if (((op == 5) && (codes[tpos] != 0)) ||
                ((op == 6) && (codes[tpos] == 0))) {
                i = codes[vpos] - 1;
            } else {
                i += 2;
            }
        } else if ((op == 7) || (op == 8)) {
            int lpos = codes[i + 1];
            if ((codes[i] % 1000) >= 100) {
                lpos = i + 1;
            }
            int rpos = codes[i + 2];
            if ((codes[i] % 10000) >= 1000) {
                rpos = i + 2;
            }
            int opos = codes[i + 3];
            if (op == 7) {
                codes[opos] = (codes[lpos] < codes[rpos]);
            }
            if (op == 8) {
                codes[opos] = (codes[lpos] == codes[rpos]);
            }
            i += 3;
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
    }

    Process(codes);

    return 0;
}
