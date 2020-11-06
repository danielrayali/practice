#include <iostream>

using namespace std;

bool IsPalidrome(const string& input) {
    size_t left = 0;
    size_t right = input.size() - 1;
    while (left < right) {
        if (input[left] != input[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input>" << endl;
        return 1;
    }
    string input(argv[1]);
    cout << input << " palidrome? " << IsPalidrome(input) << endl;
    return 0;
}

