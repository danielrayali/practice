#include <iostream>
#include <fstream>
#include <set>
#include <cstring>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

struct Claim {
  Claim(const std::string& input) {
    size_t pos = input.find_first_of(" ");
    string claim_num_str = input.substr(1, pos - 1);
    // cout << "claim_num_str: " << claim_num_str << endl;
    claim_num = atoi(claim_num_str.c_str());
    
    size_t at_pos = input.find_first_of("@");
    size_t comma_pos = input.find_first_of(",");
    string from_left_str = input.substr(at_pos + 1, comma_pos - (at_pos + 1));
    // cout << "from_left_str: " << from_left_str << endl;
    from_left = atoi(from_left_str.c_str());

    size_t colon_pos = input.find_first_of(":");
    string from_top_str = input.substr(comma_pos + 1, colon_pos - (comma_pos + 1));
    // cout << "from_top_str: " << from_top_str << endl;
    from_top = atoi(from_top_str.c_str());

    size_t x_pos = input.find_first_of("x");
    string width_str = input.substr(colon_pos + 1, x_pos - (colon_pos + 1));
    // cout << "width_str: " << width_str << endl;
    width = atoi(width_str.c_str());

    string height_str = input.substr(x_pos + 1);
    // cout << "height_str: " << height_str << endl;
    height = atoi(height_str.c_str());
    // cout << "---------------" << endl;

    top_left.first = from_left;
    top_left.second = from_top;
    bottom_right.first = from_left + width;
    bottom_right.second = from_top + height;
  }

  int claim_num;
  int from_left;
  int from_top;
  pair<int,int> top_left;
  pair<int,int> bottom_right;
  int width;
  int height;
};

int CalculateShared(Claim& left, Claim& right) {
  int from_left = max(left.from_left, right.from_left);
  int from_top = max(left.from_top, right.from_top);
  int width = min((left.from_left + left.width), (right.from_left + right.width)) - from_left;
  int height = min((left.from_top + left.height), (right.from_top + right.height)) - from_top;
  return width * height;
}

bool HasOverlap(Claim& left, Claim& right) {
  if (left.top_left.first > right.bottom_right.first || 
      right.top_left.first > left.bottom_right.first)
    return false;

  if (left.top_left.second > right.bottom_right.second ||
      right.top_left.second > left.bottom_right.second)
    return false;

  return true;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Give a file to parse" << endl;
    return 0;
  }

  vector<Claim> inputs;
  string path(argv[1]);
  ifstream in(path);
  while (!in.eof()) {
    string temp;
    getline(in, temp);
    inputs.emplace_back(temp);
  }

  int total = 0;
  for (size_t i = 0; i < inputs.size(); ++i) {
    for (size_t j = i + 1; j < inputs.size(); ++j) {
      Claim& left = inputs[i];
      Claim& right = inputs[j];
      
      if (HasOverlap(left, right))
        total += CalculateShared(left, right);
    }
  }

  cout << "Total pair-wise overlap count: " << total << endl;
  return 0;
}
