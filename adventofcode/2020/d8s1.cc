#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

void Split(const string& input, string& operation, string& argument) {
    cout << "Splitting " << input << endl;
    size_t i = 0;
    while (isspace(input[i])) {
        i++;
    }

    int start_operation = i;
    while (!isspace(input[i])) {
        i++;
    }

    operation = input.substr(start_operation, (i - start_operation));
    cout << "  Operation: " << operation << endl;

    while (isspace(input[i])) {
        i++;
    }

    argument = input.substr(i);
    cout << "  Argument: " << argument << endl;
}

class Program {
public:
    Program() = default;

    ~Program() = default;

    void SetInstructions(const vector<string>& instructions) {
        instructions_ = instructions;
    }

    void Execute() {
        while (true) {
            if (index_ >= instructions_.size()) {
                cout << "Instruction index went out of bounds" << endl;
                cout << "  Index: " << index_ << endl;
                cout << "  Number of instructions: " << instructions_.size() << endl;
                return;
            }
            if (executed_indicies_.find(index_) != executed_indicies_.end()) {
                cout << "Found repeated instruction: " << index_ << endl;
                return;
            }

            string instruction = instructions_[index_];
            string operation, argument;
            Split(instruction, operation, argument);

            if (operation == "acc") {
                counter_ += atoi(argument.c_str());
                executed_indicies_.emplace(index_);
                index_++;
            } else if (operation == "jmp") {
                executed_indicies_.emplace(index_);
                index_ += atoi(argument.c_str());
            } else if (operation == "nop") {
                executed_indicies_.emplace(index_);
                index_++;
            } else {
                cout << "Encountered unexpected instruction: " << instructions_[index_] << endl;
                return;
            }
        }
    }

    int GetCounter() {
        return counter_;
    }

private:
    int counter_ = 0;

    vector<string> instructions_;

    int index_ = 0;

    set<int> executed_indicies_;
};

int main(int argc, char* argv[]) {
    fstream input("d8s1.txt");
    vector<string> instructions;
    while (!input.eof()) {
        string instruction;
        getline(input, instruction);
        cout << "Read: " << instruction << endl;
        instructions.emplace_back(instruction);
    }

    Program program;
    program.SetInstructions(instructions);

    const int counter_before = program.GetCounter();
    program.Execute();

    cout << "Program complete" << endl;
    cout << "Counter before execution: " << counter_before << endl;
    cout << "Counter after execution: " << program.GetCounter() << endl;
    return 0;
}
