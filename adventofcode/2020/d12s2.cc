#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void RotateLeft(int& waypoint_x, int& waypoint_y, int& ship_x, int& ship_y, int degrees) {
    int start_x = (waypoint_x - ship_x);
    int start_y = (waypoint_y - ship_y);
    cout << "Rotating " << waypoint_x << ", " << waypoint_y;
    cout << " left around " << ship_x << ", " << ship_y;
    cout << " by " << degrees << " degrees" << endl;
    int relative_x = start_x;
    int relative_y = start_y;
    cout << "Staring relative vector: " << relative_x << ", " << relative_y << endl;
    while (degrees > 0) {
        int temp = relative_x;
        relative_x = -relative_y;
        relative_y = temp;
        cout << "New relative: " << relative_x << ", " << relative_y << endl;
        degrees -= 90;
        cout << "Degrees remaining: " << degrees << endl;
    }

    relative_x = (relative_x - start_x);
    relative_y = (relative_y - start_y);
    cout << "Move vector: " << relative_x << ", " << relative_y << endl;
    waypoint_x += relative_x;
    waypoint_y += relative_y;
    cout << "New waypoint: " << waypoint_x << ", " << waypoint_y << endl;
}

void RotateRight(int& waypoint_x, int& waypoint_y, int& ship_x, int& ship_y, int degrees) {
    cout << "Rotating " << waypoint_x << ", " << waypoint_y;
    cout << " right around " << ship_x << ", " << ship_y;
    cout << " by " << degrees << " degrees" << endl;
    RotateLeft(waypoint_x, waypoint_y, ship_x, ship_y, 360 - degrees);
}

void Forward(int& waypoint_x, int& waypoint_y, const int steps, int& ship_x, int& ship_y) {
    cout << "Moving " << ship_x << ", " << ship_y << " forward to ";
    cout << waypoint_x << ", " << waypoint_y << " " << steps << " times." << endl;
    int move_x = (waypoint_x - ship_x);
    int move_y = (waypoint_y - ship_y);
    ship_x += move_x * steps;
    ship_y += move_y * steps;
    waypoint_x += (move_x * steps);
    waypoint_y += (move_y * steps);
    cout << "Ship is now at " << ship_x << ", " << ship_y << endl;
    cout << "Waypoint is now at " << waypoint_x << ", " << waypoint_y << endl;
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

    int waypoint_y = 1, waypoint_x = 10;
    int ship_y = 0, ship_x = 0;
    for (auto instruction : instructions) {
        switch (instruction[0]) {
        case 'N':
            waypoint_y += atoi(instruction.substr(1).c_str());
            break;
        case 'S':
            waypoint_y -= atoi(instruction.substr(1).c_str());
            break;
        case 'E':
            waypoint_x += atoi(instruction.substr(1).c_str());
            break;
        case 'W':
            waypoint_x -= atoi(instruction.substr(1).c_str());
            break;
        case 'L': {
            int degrees = atoi(instruction.substr(1).c_str());
            RotateLeft(waypoint_x, waypoint_y, ship_x, ship_y, degrees);
        }   break;
        case 'R': {
            int degrees = atoi(instruction.substr(1).c_str());
            RotateRight(waypoint_x, waypoint_y, ship_x, ship_y, degrees);
        }   break;
        case 'F':
            Forward(waypoint_x, waypoint_y, atoi(instruction.substr(1).c_str()), ship_x, ship_y);
            break;
        default:
            cout << "Don't know how to process: " << instruction << endl;
            return 0;
        }
    }

    cout << "Ships movements complete" << endl;
    cout << "Ship is at " << ship_x << ", " << ship_y << endl;
    cout << "Waypoint is at " << waypoint_x << ", " << waypoint_y << endl;
    cout << "Ship's Manhattan distance is " << abs(ship_x) + abs(ship_y) << endl;
    return 0;
}