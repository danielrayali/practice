#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <utility>

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

class DirectionalMap {
 public:
    DirectionalMap() : x_(0), y_(0), dir_(NORTH) {}

    ~DirectionalMap() = default;

    bool HasCurrentBeenVisited() const {
        auto iter = visited_.find(make_pair(x_, y_));
        return (iter != visited_.end());  // If not in the list, it has not been visited
    }

    void VisitCurrent() {
        if (visited_.find(make_pair(x_, y_)) == visited_.end()) {
            visited_.emplace(x_, y_);
        }
    }

    void ClearVisit() {
        auto iter = visited_.find(make_pair(x_, y_));
        if (iter != visited_.end()) {
            visited_.erase(iter);
        }
    }

    void MoveLeft() {
        switch (dir_) {
        case NORTH:
            dir_ = WEST;
            x_--;
            break;
        case EAST:
            dir_ = NORTH;
            y_++;
        case SOUTH:
            dir_ = EAST;
            x_++;
        case WEST:
            dir_ = SOUTH;
            y_--;
        }
    }

    void MoveRight() {
        switch (dir_) {
        case NORTH:
            dir_ = EAST;
            x_++;
            break;
        case EAST:
            dir_ = SOUTH;
            y_--;
        case SOUTH:
            dir_ = WEST;
            x_--;
        case WEST:
            dir_ = NORTH;
            y_++;
        }
    }

    size_t GetNumVisited() const {
        return visited_.size();
    }

 private:
    std::set<std::pair<long long, long long>> visited_;
    long long x_;
    long long y_;
    enum Dir {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };
    Dir dir_;
};

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

    DirectionalMap dir_map;
    IntCodeComputer computer(codes);
    vector<long long> in;
    in.push_back(0);
    vector<long long> out;
    while (!computer.IsDone()) {
        in[0] = (dir_map.HasCurrentBeenVisited() ? 1 : 0);

        computer.Process(in, out);
        if (computer.IsDone()) {
            throw runtime_error("Unexpected termination of program (0)");
        }

        if (out.size() != 1) {
            throw runtime_error("Unexpected output size: " + to_string(out.size()));
        }

        if (out[0] == 0) {
            dir_map.ClearVisit();
        } else if (out[0] == 1) {
            dir_map.VisitCurrent();
        } else {
            throw runtime_error("Unexpected output value: " + to_string(out[0]));
        }

        out.clear();
        computer.Process(in, out);
        if (computer.IsDone()) {
            throw runtime_error("Unexpected termination of program (1)");
        }

        if (out.size() != 1) {
            throw runtime_error("Unexpected output size: " + to_string(out.size()));
        }

        if (out[0] == 0) {
            dir_map.MoveLeft();
        } else if (out[0] == 1) {
            dir_map.MoveRight();
        } else {
            throw runtime_error("Unexpected output value: " + to_string(out[0]));
        }

        out.clear();
    }

    // 3437 is too high
    cout << "Number of visited locations: " << dir_map.GetNumVisited() << endl;
    return 0;
}
