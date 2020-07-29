#include <iostream>
#include <fstream>
#include <set>
#include <cstring>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Give a file to parse" << endl;
    return 0;
  }

  vector<string> inputs;
  string path(argv[1]);
  ifstream in(path);
  while (!in.eof()) {
    inputs.emplace_back();
    getline(in, inputs.back());
  }

  sort(inputs.begin(), inputs.end());
  
  size_t i = 0;
  size_t k = 0;
  for (size_t j = 1; j < inputs.size(); ++j) {
    int differences = 0;
    for (k = 0; k < inputs[j].size(); ++k) {
      if (inputs[i][k] != inputs[j][k]) {
        differences++;
        if (differences > 1)
          break;
      }
    }
    if (differences == 1) {
      cout << "Single difference found\n";
      cout << inputs[i] << '\n';
      cout << inputs[j] << '\n';
    }
    i++;
  }

  return 0;
}
