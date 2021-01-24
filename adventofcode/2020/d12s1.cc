#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Forward(int& north, int& east, int& direction, const int spaces) {
    while ((direction < 0) || (direction >= 360)) {
        direction = (direction + 360) % 360;
    }

    switch (direction) {
    case 0:
        east += spaces;
        break;
    case 90:
        north += spaces;
        break;
    case 180:
        east -= spaces;
        break;
    case 270:
        north -= spaces;
        break;
    default:
        cout << "Don't know how to handle: " << direction << endl;
        throw std::exception();
    }
}

int main(int argc, char* argv[]) {
    ifstream input("d12s1.txt");
    vector<string> instructions;
    while (!input.eof()) {
        string line;
        getline(input, line);
        cout << "Read: " << line << endl;
        instructions.emplace_back(line);
    }

    int north = 0, east = 0;
    int angle = 0;
    for (auto instruction : instructions) {
        switch (instruction[0]) {
        case 'N':
            north += atoi(instruction.substr(1).c_str());
            break;
        case 'S':
            north -= atoi(instruction.substr(1).c_str());
            break;
        case 'E':
            east += atoi(instruction.substr(1).c_str());
            break;
        case 'W':
            east -= atoi(instruction.substr(1).c_str());
            break;
        case 'L':
            angle += atoi(instruction.substr(1).c_str());
            break;
        case 'R':
            angle -= atoi(instruction.substr(1).c_str());
            break;
        case 'F':
            Forward(north, east, angle, atoi(instruction.substr(1).c_str()));
            break;
        default:
            cout << "Don't know how to process: " << instruction << endl;
            return 0;
        }
    }

    cout << "Ship movements complete" << endl;
    cout << "Ending position: (" << north << "," << east << ")" << endl;
    cout << "Ending angle: " << angle << endl;
    cout << "Manhattan distance from (0,0): " << abs(north) + abs(east) << endl;
    return 0;
}