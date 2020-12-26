#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Give a file to parse" << endl;
    return 0;
  }

  string path(argv[1]);
  int total = 0;
  set<int> history;
  history.emplace(0);
  while (true) {
    ifstream in(path);
    while (!in.eof()) {
      int current = 0;
      in >> current;
      total += current;

      if (history.find(total) != history.end()) {
        cout << "First repeat: " << total << endl;
        return 0;
      }

      history.emplace(total);
    }
  }

  cout << "No repeat found!" << endl;
  return 0;
}
