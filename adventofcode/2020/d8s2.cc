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

    enum class ExitStatus {
        INDEX_OUT_OF_BOUNDS,
        FOUND_REPEAT_INSTRUCTION,
        ENCOUNTERED_UNEXPECTED_INSTRUCTION
    };

    ExitStatus Execute() {
        while (true) {
            if (index_ >= instructions_.size()) {
                cout << "Instruction index went out of bounds" << endl;
                cout << "  Index: " << index_ << endl;
                cout << "  Number of instructions: " << instructions_.size() << endl;
                return ExitStatus::INDEX_OUT_OF_BOUNDS;
            }
            if (executed_indicies_.find(index_) != executed_indicies_.end()) {
                cout << "Found repeated instruction: " << index_ << endl;
                return ExitStatus::FOUND_REPEAT_INSTRUCTION;
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
                return ExitStatus::ENCOUNTERED_UNEXPECTED_INSTRUCTION;
            }
        }
    }

    int GetCounter() {
        return counter_;
    }

    void SetCounter(int counter) {
        counter_ = counter;
    }

private:
    int counter_ = 0;

    vector<string> instructions_;

    int index_ = 0;

    set<int> executed_indicies_;
};

int FindNextJmpLocation(const vector<string>& instructions, int start) {
    for (int i = start; i < instructions.size(); ++i) {
        string operation, argument;
        Split(instructions[i], operation, argument);
        if (operation == "jmp") {
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    fstream input("d8s1.txt");
    vector<string> instructions;
    while (!input.eof()) {
        string instruction;
        getline(input, instruction);
        cout << "Read: " << instruction << endl;
        instructions.emplace_back(instruction);
    }

    int jmp_location = -1;
    while (true) {
        // Modify the jmp command
        jmp_location = FindNextJmpLocation(instructions, (jmp_location + 1));
        if (jmp_location < 0) {
            break;
        }
        string modified_jmp = instructions[jmp_location];
        string operation, argument;
        Split(modified_jmp, operation, argument);
        modified_jmp = "nop " + argument;
        cout << "  Modified jmp command at " << jmp_location << endl;
        cout << "  Previous command: " << instructions[jmp_location] << endl;
        cout << "  New command: " << modified_jmp << endl;

        vector<string> modified_instructions = instructions;
        modified_instructions[jmp_location] = modified_jmp;

        Program program;
        program.SetInstructions(modified_instructions);
        const int counter_before = program.GetCounter();
        Program::ExitStatus exit_status = program.Execute();

        cout << "  Program complete" << endl;
        cout << "  Counter before execution: " << counter_before << endl;
        cout << "  Counter after execution: " << program.GetCounter() << endl;
        cout << "  Exit status: ";
        switch (exit_status) {
        case Program::ExitStatus::INDEX_OUT_OF_BOUNDS:
            cout << "program terminated normally, running out of instructions" << endl;
            break;
        case Program::ExitStatus::FOUND_REPEAT_INSTRUCTION:
            cout << "found a repeat instruction" << endl;
            break;
        case Program::ExitStatus::ENCOUNTERED_UNEXPECTED_INSTRUCTION:
            cout << "encountered unexpected instruction" << endl;
            return 0;
        default:
            cout << "Unknown exit status" << endl;
            return 0;
        }
    }

    return 0;
}
