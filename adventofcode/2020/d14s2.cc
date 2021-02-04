#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

class Memory {
public:
    Memory() = default;

    ~Memory() = default;

    void SetMask(const string& mask_instruction) {
        mask_ = mask_instruction.substr(7);
    }

    void SetValue(const string& value_instruction) {
        ssize_t pos = value_instruction.find_first_of(']');
        uint64_t address = strtoull(value_instruction.substr(4, (pos - 4)).c_str(), nullptr, 0);
        cout << "Address: " << address << endl;
        uint64_t value = strtoull(value_instruction.substr(pos + 4).c_str(), nullptr, 0);
        cout << "Value: " << value << endl;

        vector<uint64_t> addresses = this->GetAddresses(address);
        for (auto address : addresses) {
            memory_[address] = value;
        }
    }

    uint64_t GetValueCount() const {
        uint64_t count = 0;
        for (auto iter : memory_) {
            count += iter.second;
        }
        return count;
    }

private:
    string mask_;
    map<uint64_t, uint64_t> memory_;

    vector<uint64_t> GetAddresses(const uint64_t address) {
        vector<uint64_t> addresses(1, 0);
        uint64_t current_bit = 0x800000000;
        uint64_t current_shift = 35;
        for (int i = 0; i < mask_.size(); ++i) {
            if (mask_[i] == 'X') {
                vector<uint64_t> new_addresses;  // Use this to avoid iterator invalidation
                for (auto& iter : addresses) {
                    iter <<= 1;  // zero case
                    new_addresses.push_back(iter);
                    new_addresses.back() |= 0x1;  // one case
                }
                for (auto& iter : new_addresses) {
                    addresses.push_back(iter);
                }
            } else if (mask_[i] == '0') {
                for (auto& iter : addresses) {
                    iter = (iter << 1) | ((address & current_bit) >> current_shift);
                }
            } else if (mask_[i] == '1') {
                for (auto& iter : addresses) {
                    iter = (iter << 1) | (current_bit >> current_shift);
                }
            }
            current_bit >>= 1;
            current_shift--;
        }
        return addresses;
    }
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
