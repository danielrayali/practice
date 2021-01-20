#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input("d9s1.txt");
    vector<long long> values;
    while (!input.eof()) {
        long long temp;
        input >> temp;
        cout << "Read: " << temp << endl;
        values.push_back(temp);
    }

    const long long to_find = 542529149;
    for (int size = 2; size <= values.size(); ++size) {
        for (int start = 0; start < values.size(); start++) {
            auto start_iter = values.begin() + start;
            auto end_iter = start_iter + size;
            long long sum = 0;
            std::for_each(start_iter, end_iter, [&](long long n) { sum += n; });
            if (sum == to_find) {
                vector<long long> sequence(start_iter, end_iter);
                cout << "  Found the sequence to match " << to_find << ": ";
                std::for_each(start_iter, end_iter, [&](long long n){ cout << n << " "; });
                cout << endl;
                sort(sequence.begin(), sequence.end());
                cout << "  Min: " << sequence.front() << endl;
                cout << "  Max: " << sequence.back() << endl;
                cout << "  Sum of min and max: " << sequence.front() + sequence.back() << endl;
            }
        }
    }

    return 0;
}
