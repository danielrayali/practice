#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Give a file to parse" << endl;
    return 0;
  }

  string path(argv[1]);
  ifstream in(path);
  int total = 0;
  while (in) {
    int current = 0;
    in >> current;
    total += current;
  }

  cout << "Total: " << total << endl;
  return 0;
}
