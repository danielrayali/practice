#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class Memory {
public:
    Memory() = default;

    ~Memory() = default;

    void SetMask(const string& mask_instruction) {
        string mask_values = mask_instruction.substr(7);
        zero_mask_ = ~0;
        one_mask_ = 0;
        for (int i = 0; i < mask_values.size(); ++i) {
            if (mask_values[i] == 'X') {
                zero_mask_ = (zero_mask_ << 1) | 0x1;
                one_mask_ <<= 1;
            } else if (mask_values[i] == '0') {
                zero_mask_ <<= 1;
                one_mask_ <<= 1;
            } else if (mask_values[i] == '1') {
                zero_mask_ = (zero_mask_ << 1) | 0x1;
                one_mask_ = (one_mask_ << 1) | 0x1;
            }
        }
        cout << "Zero mask is 0x" << std::hex << zero_mask_ << endl;
        cout << "One mask is 0x" << std::hex << one_mask_ << std::dec << endl;
    }

    void SetValue(const string& value_instruction) {
        ssize_t pos = value_instruction.find_first_of(']');
        int address = atoi(value_instruction.substr(4, (pos - 4)).c_str());
        cout << "Address: " << address << endl;
        uint64_t value = strtoull(value_instruction.substr(pos + 4).c_str(), nullptr, 0);
        value &= zero_mask_;
        value |= one_mask_;
        cout << "New value: " << value << endl;
        memory_[address] = value;

    }

    uint64_t GetValueCount() const {
        uint64_t count = 0;
        for (auto iter : memory_) {
            count += iter.second;
        }
        return count;
    }

private:
    uint64_t zero_mask_ = 0;
    uint64_t one_mask_ = 0;
    map<uint64_t, uint64_t> memory_;
};

int main(int argc, char* argv[]) {
    ifstream input("d14s1.txt");
    Memory memory;
    while (!input.eof()) {
        string line;
        getline(input, line);
        cout << "Read: " << line << endl;

        if (line.substr(0, 3) == "mem") {
            memory.SetValue(line);
        } else {
            memory.SetMask(line);
        }
    }

    cout << "Value count: " << memory.GetValueCount() << endl;

    return 0;
}
