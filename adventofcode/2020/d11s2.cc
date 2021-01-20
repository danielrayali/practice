#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool ContainsOccupiedVisibleSeat(vector<string>& seats, int x, int y, int slope_x, int slope_y) {
    int x_start = x, y_start = y;
    if ((slope_x == 0) && (slope_y == 0)) {
        return false;
    }

    x += slope_x;
    y += slope_y;

    while ((x >= 0) && (y >= 0) && (y < seats.size()) && (x < seats.at(0).size())) {
        if (seats.at(y).at(x) == '#') {
            // cout << x_start << ", " << y_start << " can see " << x << ", " << y << endl;
            return true;
        } else if (seats.at(y).at(x) == 'L') {
            return false;
        }

        x += slope_x;
        y += slope_y;
    }

    return false;
}

int GetNumOfOccupiedVisibleSeats(vector<string>& seats, int row, int column) {
    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (ContainsOccupiedVisibleSeat(seats, column, row, i, j)) {
                count++;
            }
        }
    }
    return count;
}

// If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
// If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
// Otherwise, the seat's state does not change.
vector<string> Iterate(vector<string>& seats) {
    vector<string> new_seats(seats);
    for (int i = 0; i < seats.size(); ++i) {
        for (int j = 0; j < seats.at(i).size(); ++j) {
            if (seats.at(i).at(j) == 'L') {
                if (GetNumOfOccupiedVisibleSeats(seats, i, j) == 0) {
                    new_seats.at(i).at(j) = '#';
                }
            } else if (seats.at(i).at(j) == '#') {
                if (GetNumOfOccupiedVisibleSeats(seats, i, j) >= 5) {
                    new_seats.at(i).at(j) = 'L';
                }
            } else if (seats.at(i).at(j) != '.') {
                cout << "Unknown character: " << seats.at(i).at(j) << endl;
                cout << "Location: " << i << ", " << j << endl;
                return {};
            }
        }
    }
    return new_seats;
}

void Print(vector<string>& seats) {
    for (auto line : seats) {
        cout << line << endl;
    }
}

int CountOccupiedSeats(const vector<string>& seats) {
    int count = 0;
    for (auto outter : seats) {
        for (auto inner : outter) {
            if (inner == '#') {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    ifstream input("d11s1.txt");
    vector<string> seats[2];
    while (!input.eof()) {
        string line;
        getline(input, line);
        seats[0].emplace_back(line);
        cout << "Read: " << seats[0].back() << endl;
    }

    cout << "Initial seat map: " << endl;
    Print(seats[0]);

    int round = 0;
    int index_left = 0, index_right = 1;
    while (seats[index_left] != seats[index_right]) {
        seats[index_right] = Iterate(seats[index_left]);
        round++;
        cout << "After round " << round << ": " << endl;
        Print(seats[index_right]);
        swap(index_left, index_right);
    }

    cout << "Seats have converged after round: " << round << endl;
    cout << "Number of occupied seats: " << CountOccupiedSeats(seats[index_right]) << endl;
    return 0;
}
