#include <iostream>
#include <fstream>

using namespace std;

class BitVector {
 public:
    BitVector(const unsigned max) {
        bits_ = new unsigned[1 + (max / kBitsPerElement)];
        for (unsigned i = 0; i < (1 + (max/kBitsPerElement)); ++i)
            bits_[i] = 0;
    }

    ~BitVector() {
        delete [] bits_;
    }

    void Clear(const unsigned number) {
        bits_[number / kBitsPerElement] &= ~(0x1 << (number & 0x3F));
    }

    void Set(const unsigned number) {
        bits_[number / kBitsPerElement] |= (0x1 << (number & 0x3F));
    }

    unsigned Test(const unsigned number) {
        return bits_[number / kBitsPerElement] & (0x1 << (number & 0x3F));
    }

 private:
    unsigned* bits_ = nullptr;
    const int kBitsPerElement = sizeof(unsigned) * 8;
};

int main(int argc, char* argv[]) {
    const unsigned max_value = 10000000;
    const unsigned num_integers = 1000000;

    ofstream output("random.txt");
    BitVector* random_vector = new BitVector(max_value);
    for (int i = 0; i < num_integers; ++i) {
        unsigned value = (rand() % max_value);
        if (random_vector->Test(value) == 0) {
            output << setfill('0') << setw(7) << value << '\n';
            random_vector->Set(value);
        } else {
            i--;
        }
    }
    delete random_vector;
    output.close();  // Ensure the file is closed for future processing

    ifstream input("random.txt");
    BitVector bit_vector(max_value);
    for (int i = 0; i < num_integers; ++i) {
        unsigned temp = 0;
        input >> temp;
        bit_vector.Set(temp);
    }

    ofstream sorted("sorted.txt");
    for (int i = 0; i < max_value; ++i) {
        if (bit_vector.Test(i))
            sorted << setfill('0') << setw(7) << i << '\n';
    }
    return 0;
}
