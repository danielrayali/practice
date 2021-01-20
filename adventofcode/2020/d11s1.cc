#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int GetNumOfAdjacentOccupiedSeats(vector<string>& seats, int row, int column) {
    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int x = row + i;
            int y = column + j;
            if (((x == row) && (y == column)) || (x < 0) || (y < 0) || (x >= seats.size()) || (y >= seats.at(0).size())) {
                continue;
            }
            if (seats.at(x).at(y) == '#') {
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
                if (GetNumOfAdjacentOccupiedSeats(seats, i, j) == 0) {
                    new_seats.at(i).at(j) = '#';
                }
            } else if (seats.at(i).at(j) == '#') {
                if (GetNumOfAdjacentOccupiedSeats(seats, i, j) >= 4) {
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

int main(int argc, char* argv[]) {
    ifstream input("d11s1.txt");
    vector<string> seats1;
    while (!input.eof()) {
        string line;
        getline(input, line);
        seats1.emplace_back(line);
        cout << "Read: " << seats1.back() << endl;
    }

    cout << "Initial seat map: " << endl;
    Print(seats1);

    vector<string> seats2 = Iterate(seats1);
    cout << "After round 1: " << endl;
    Print(seats2);
    if (seats1 == seats2) {
        cout << "Seat maps are equal too early" << endl;
        return 0;
    }

    seats1 = Iterate(seats2);
    cout << "After round 2: " << endl;
    Print(seats1);
    if (seats1 == seats2) {
        cout << "Seat maps are equal too early" << endl;
        return 0;
    }


    seats2 = Iterate(seats1);
    cout << "After round 3: " << endl;
    Print(seats2);
    if (seats1 == seats2) {
        cout << "Seat maps are equal too early" << endl;
        return 0;
    }

    seats1 = Iterate(seats2);
    cout << "After round 4: " << endl;
    Print(seats1);
    if (seats1 == seats2) {
        cout << "Seat maps are equal too early" << endl;
        return 0;
    }

    seats2 = Iterate(seats1);
    cout << "After round 5: " << endl;
    Print(seats2);
    if (seats1 == seats2) {
        cout << "Seat maps are equal after 5 rounds" << endl;
        return 0;
    }

    return 0;
}