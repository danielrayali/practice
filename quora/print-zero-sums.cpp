#include <iostream>
#include <unordered_map>
#include <utility>
using namespace std;

void PrintWindow(int* data, int pos, int size) {
	for (int i = 0; i < size; ++i) {
		cout << data[pos + i] << " ";
	}
	cout << endl;
}

// Print all sub-arrays with 0 sum
void PrintZeroSums(int* data, int size) {
	for (int window_size = 1; window_size < (size + 1); ++window_size) {
		for (int window_pos = 0; (window_pos + window_size) <= size; ++window_pos) {
			int window_sum = 0;
			for (int count_pos = window_pos; count_pos < (window_pos + window_size); ++count_pos) {
				window_sum += data[count_pos];
			}
			if (window_sum == 0) {
				PrintWindow(data, window_pos, window_size);
			}
		}
	}
}

void PrintZeroSumsFaster(int* data, int size) {
	unordered_map<int,int> sum_to_pos;
	sum_to_pos.insert(make_pair<int,int>(0,-1));
	int sum = 0;
	for (int pos = 0; pos < size; ++pos) {
		sum += data[pos];

		auto it = sum_to_pos.find(sum);

		while (it != sum_to_pos.end() && it->first == sum) {
			PrintWindow(data, it->second + 1, (pos - it->second));
			it++;
		}

		pair<int,int> node(sum,pos);
		sum_to_pos.insert(node);
	}
}

int main() {
	// your code goes here
	int size = 11;
	int data[size];
	cout << "Input: ";
	for (int i = -size / 2; i < size / 2 + 1; ++i) {
		data[i + size / 2] = i;
		cout << data[i + size / 2] << " ";
	}
	cout << endl;

	PrintZeroSums(data, size);
	PrintZeroSumsFaster(data, size);

	return 0;
}

