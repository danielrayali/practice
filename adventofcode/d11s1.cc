#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

class IntCodeComputer {
 public:
    IntCodeComputer(const vector<long long>& codes) : codes_(codes) {}

    ~IntCodeComputer() = default;

    void Process(const vector<long long>& input, vector<long long>& output) {
        long long input_idx = 0;
        for (long long& i = position_; i < codes_.size(); ++i) {
            long long op = codes_[i] % 100;
            if (op == 99) {
                done_ = true;
                return;
            } else if (op == 1 || op == 2) {
                long long lpos = GetArgumentPosition1();
                long long rpos = GetArgumentPosition2();

                // Output positions will never be in immediate mode
                long long opos = GetArgumentPosition3();
                if (op == 1) {
                    codes_[opos] = codes_[lpos] + codes_[rpos];
                } else {
                    codes_[opos] = codes_[lpos] * codes_[rpos];
                }
                i += 3;
            } else if (op == 3) {
                long long pos = GetArgumentPosition1();
                long long value = 0;
                if (input_idx < input.size()) {
                    value = input[input_idx++];
                } else {
                    cout << "Provide input: ";
                    cin >> value;
                }

                codes_[pos] = value;
                i++;
            } else if (op == 4) {
                long long pos = GetArgumentPosition1();
                // Here, we are going to return so add two to position
                i += 2;
                output.push_back(codes_[pos]);
                return;
            } else if ((op == 5) || (op == 6)) {
                long long tpos = GetArgumentPosition1();
                long long vpos = GetArgumentPosition2();

                if (((op == 5) && (codes_[tpos] != 0)) ||
                    ((op == 6) && (codes_[tpos] == 0))) {
                    i = codes_[vpos] - 1;
                } else {
                    i += 2;
                }
            } else if ((op == 7) || (op == 8)) {
                long long lpos = GetArgumentPosition1();
                long long rpos = GetArgumentPosition2();
                long long opos = GetArgumentPosition3();
                if (op == 7) {
                    codes_[opos] = (codes_[lpos] < codes_[rpos]);
                }
                if (op == 8) {
                    codes_[opos] = (codes_[lpos] == codes_[rpos]);
                }
                i += 3;
            } else if (op == 9) {
                long long pos = GetArgumentPosition1();
                long long adjustment = codes_[pos];
                relative_base_ += adjustment;
                i += 1;
            } else {
                cerr << "Unknown op code: " << codes_[i] << endl;
                return;
            }
        }
        cerr << "Reached end of input" << endl;
    }

    bool IsDone() const {
        return done_;
    }

 private:
    vector<long long> codes_;
    bool done_ = false;
    long long position_ = 0;
    long long relative_base_ = 0;

    long long GetArgumentPosition1() {
        long long pos = codes_[position_ + 1];
        long long truncated = (codes_[position_] % 1000);
        if (truncated >= 100) {
            pos = position_ + 1;
        }
        if (truncated >= 200) {
            pos = relative_base_ + codes_[position_ + 1];
        }
        return pos;
    }

    long long GetArgumentPosition2() {
        long long pos = codes_[position_ + 2];
        long long truncated = (codes_[position_] % 10000);
        if (truncated >= 1000) {
            pos = position_ + 2;
        }
        if (truncated >= 2000) {
            pos = relative_base_ + codes_[position_ + 2];
        }
        return pos;
    }

    long long GetArgumentPosition3() {
        long long pos = codes_[position_ + 3];
        long long truncated = (codes_[position_] % 100000);
        if (truncated >= 10000) {
            pos = position_ + 3;
        }
        if (truncated >= 20000) {
            pos = relative_base_ + codes_[position_ + 3];
        }
        return pos;
    }
};

char GetNewDir(char dir, int turn) {
    if (turn == 0) {
        switch (dir) {
        case '^': return '<';
        case '<': return 'v';
        case '>': return '^';
        case 'v': return '>';
        default: throw runtime_error("Direction is not right");
        }
    } else if (turn == 1) {
        switch (dir) {
        case '^': return '>';
        case '<': return '^';
        case '>': return 'v';
        case 'v': return '<';
        default: throw runtime_error("Direction is not right");
        }
    }
    throw runtime_error("GetNewDir() error");
}

pair<int,int> GetNewPos(char dir, pair<int,int> pos, int turn) {
    if (turn == 0) {
        switch (dir) {
        case '^': return pair<int,int>{pos.first-1, pos.second  };
        case '<': return pair<int,int>{pos.first  , pos.second-1};
        case '>': return pair<int,int>{pos.first  , pos.second+1};
        case 'v': return pair<int,int>{pos.first+1, pos.second  };
        default: throw runtime_error("Direction is not right");
        }
    } else if (turn == 1) {
        switch (dir) {
        case '^': return pair<int,int>{pos.first+1, pos.second  };
        case '<': return pair<int,int>{pos.first  , pos.second+1};
        case '>': return pair<int,int>{pos.first  , pos.second-1};
        case 'v': return pair<int,int>{pos.first-1, pos.second  };
        default: throw runtime_error("Direction is not right");
        }
    }
    throw runtime_error("GetNewPos() error");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Give a file to parse" << endl;
        return 0;
    }

    vector<long long> codes;
    string path(argv[1]);
    ifstream in_stream(path);
    while (!in_stream.eof()) {
        string current;
        getline(in_stream, current, ',');
        codes.push_back(atoll(current.c_str()));
    }

    IntCodeComputer computer(codes);
    vector<long long> in{0};
    pair<int,int> pos{0,0};
    set<pair<int,int>> whites;
    char dir = '^';
    while (!computer.IsDone()) {
        vector<long long> out;
        computer.Process(in, out);
        if (out.size() > 1) {
            throw runtime_error("Out is too large");
        }

        if (out[0] == 1) {
            whites.insert(pos);
        } else if (out[0] == 0) {
            auto iter = whites.find(pos);
            if (iter != whites.end()) {
                whites.erase(iter);
            }
        }

        in[0] = out[0];
        out.clear();
        computer.Process(in, out);

        if (out.size() > 1) {
            throw runtime_error("Out is too large");
        }

        dir = GetNewDir(dir, out[0]);
        pos = GetNewPos(dir, pos, out[0]);
    }

    // cout << "Output size: " << out.size() << endl;
    // for (int i = 0; i < out.size(); ++i) {
    //     cout << "Output[" << i << "]: " << out[0] << endl;
    // }

    return 0;
}
