#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

const char kBase64Table[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
    'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
    't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

const char kBase64Pad = '=';

#include <bitset>

std::string CovertToBase64(const std::vector<uint8_t>& input) {
    std::string output;
    output.resize(input.size() * 8 / 6 + 1);
    size_t from_last = 2;
    output[0] = kBase64Table[(input[0] & 0xFC) >> 2];
    size_t j = 1;
    for (size_t i = 1; i < input.size(); ++i) {
        uint8_t prev = input[i - 1];
        prev <<= (6 - from_last);
        prev &= 0b00111111;

        uint8_t current = input[i];
        current >>= (from_last + 2);
        output[j] = kBase64Table[prev | current];

        j++;
        from_last += 2;
        if (from_last > 6) {
            current = input[i] & 0xFC;
            current >>= 2;
            output[j] = kBase64Table[current];
            from_last = 2;
            j++;
        }
    }

    // Set the last byte
    uint8_t last = input.back();
    last <<= (8 - from_last);
    last >>= (8 - from_last);
    output[j] = kBase64Table[last];
    return output;
}

vector<uint8_t> ConvertHexStringToHex(const std::string& input) {
    vector<uint8_t> output(input.size() / 2, 0);
    int j = 0;
    for (int i = 0; i < input.size(); i += 2) {
        output[j] = std::stoi(input.substr(i, 2), nullptr, 16);
        j++;
    }
    return output;
}

int main(int argc, char* argv[]) {
    string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    vector<uint8_t> input_data = ConvertHexStringToHex(input);
    string output = CovertToBase64(input_data);
    cout << "Output size " << output.size() << endl;
    cout << output << endl;
    return 0;
}