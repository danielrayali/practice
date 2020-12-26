#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

int Process(vector<int> codes, vector<int> inputs) {
    int input_idx = 0;
    int output = -1;
    for (int i = 0; i < codes.size(); ++i) {
        int op = codes[i] % 100;
        if (op == 99) {
            return output;
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
            // cout << "Provide input: ";

            int value = 0;
            if (input_idx < inputs.size()) {
                // cout << inputs[input_idx] << " (auto provided)" << endl;
                value = inputs[input_idx++];
            } else {
                cin >> value;
            }

            codes[pos] = value;
            i++;
        } else if (op == 4) {
            int pos = codes[i + 1];
            if ((codes[i] % 1000) >= 100) {
                pos = i + 1;
            }
            if (output != -1) {
                cerr << "Too many output operations to return just one" << endl;
                cerr << "Returning first output: " << output << endl;
            } else {
                // cout << "Output operation: " << codes[pos] << endl;
                output = codes[pos];
            }
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
            return output;
        }
    }
    return output;
}

list<list<int>> Permute(list<int> input) {
    if (input.empty()) {
        return {};
    }

    if (input.size() == 1) {
        return { input };
    }

    list<list<int>> results;
    for (auto it = input.begin(); it != input.end(); it++) {
        list<int> temp(input);
        temp.remove(*it);
        list<list<int>> sub_permutes = Permute(temp);
        for (auto sub_permute : sub_permutes) {
            list<int> to_add;
            to_add.push_back(*it);
            to_add.insert(to_add.end(), sub_permute.begin(), sub_permute.end());
            results.push_back(to_add);
        }
    }
    return results;
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

    int max = -1;
    list<list<int>> permutes = Permute({0,1,2,3,4});
    for (auto permute : permutes) {
        int result = 0;
        for (int i : permute) {
            result = Process(codes, {i, result});
        }

        if (result > max) {
            max = result;
        }
    }

    cout << "Max: " << max << endl;

    return 0;
}
