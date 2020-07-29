#include <iostream>
#include <fstream>
#include <set>
#include <cstring>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Give a file to parse" << endl;
    return 0;
  }

  string path(argv[1]);
  int twos = 0;
  int threes = 0;
  ifstream in(path);
  int counts[26];
  while (!in.eof()) {
    string current;
    getline(in, current);

    bool two = false;
    bool three = false;
    memset(counts, 0, 26 * sizeof(int));
    for (char letter : current)
      counts[letter - 'a']++;

    for (char letter : current) {
      if (counts[letter - 'a'] == 2)
        two = true;
      if (counts[letter - 'a'] == 3)
        three = true;
    }
    
    if (two)
      twos++;
    if (three)
      threes++;

    // cout << current << " " << two << " " << three << endl;
  }

  cout << "Twos found: " << twos << endl;
  cout << "Threes found: " << threes << endl;
  cout << "Multiplied: " << twos * threes << endl;

  return 0;
}
