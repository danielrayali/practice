#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int Process(vector<int>& codes, vector<int> inputs, bool& done, int& position) {
    int input_idx = 0;
    int output = -1;
    for (int& i = position; i < codes.size(); ++i) {
        int op = codes[i] % 100;
        if (op == 99) {
            done = true;
            return inputs[0];
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
            int value = 0;
            if (input_idx < inputs.size()) {
                value = inputs[input_idx++];
            } else {
                cout << "Provide input: ";
                cin >> value;
            }

            codes[pos] = value;
            i++;
        } else if (op == 4) {
            int pos = codes[i + 1];
            if ((codes[i] % 1000) >= 100) {
                pos = i + 1;
            }
            // Here, we are going to return so add two to position
            i += 2;
            if (output != -1) {
                cerr << "Too many output operations to return just one" << endl;
                cerr << "Returning first output: " << output << endl;
            } else {
                // cout << "Output operation: " << codes[pos] << endl;
                output = codes[pos];
                return output;
            }
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
    cerr << "Reached end of input" << endl;
    return output;
}

vector<vector<int>> Permute(vector<int> input) {
    if (input.empty()) {
        return {};
    }

    if (input.size() == 1) {
        return { input };
    }

    vector<vector<int>> results;
    for (auto it = input.begin(); it != input.end(); it++) {
        const size_t pos = (it - input.begin());
        vector<int> temp(input);
        temp.erase(temp.begin() + pos);
        vector<vector<int>> sub_permutes = Permute(temp);
        for (auto sub_permute : sub_permutes) {
            vector<int> to_add;
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

    vector<vector<int>> permutes = Permute({5,6,7,8,9});
    vector<vector<int>> amp_codes(5, codes);
    vector<int> max_phases = {0,0,0,0,0};
    int max = -1;
    for (auto permute : permutes) {
        // cout << "Trying: " << permute[0] << " "
        //      << permute[1] << " "
        //      << permute[2] << " "
        //      << permute[3] << " "
        //      << permute[4] << endl;
        // Prime the phase inputs
        int result = 0;
        vector<int> positions = {0,0,0,0,0};
        bool amp_done[5] = {false, false, false, false, false};
        for (int i = 0; i < 5; i++) {
            // cout << "Loop" << endl;
            amp_codes[i] = codes;
            result = Process(amp_codes[i], {permute[i], result}, amp_done[i], positions[i]);
        }

        // Run each amplifier repeatedly by passing the output of one into the next one.
        // Feedback the last amplifier's output into the first amplifier. Run until all
        // amplifiers are done by waiting for the last amplifier to be done
        while (!amp_done[4]) {
            for (int i = 0; i < 5; ++i) {
                if (!amp_done[i]) {
                    result = Process(amp_codes[i], {result}, amp_done[i], positions[i]);
                }
            }
        }

        if (result > max) {
            max = result;
            max_phases = permute;
        }
    }

    cout << "Max amplifier value: " << max << endl;
    cout << "Max phase settings: " << max_phases[0] << " "
            << max_phases[1] << " "
            << max_phases[2] << " "
            << max_phases[3] << " "
            << max_phases[4] << endl;
    return 0;
}
