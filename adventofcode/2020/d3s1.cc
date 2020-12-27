#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<bool>& row) {
    for (auto entry : row) {
        if (entry) {
            out << "#";
        } else {
            out << ".";
        }
    }
    return out;
}

ostream& operator<<(ostream& out, const vector<vector<bool>>& grid) {
    for (auto row : grid) {
        out << row << '\n';
    }
    return out;
}

int CountTreesEncountered(vector<vector<bool>>& grid, int row_add, int column_add) {
    int row = row_add;
    int column = column_add;
    int trees_encountered = 0;
    while (row < grid.size()) {
        cout << "Considering position " << row << " " << column << ": ";
        if (grid.at(row).at(column)) {
            cout << "X" << endl;
            trees_encountered++;
        } else {
            cout << "O" << endl;
        }
        column = (column + column_add) % grid.at(0).size();
        row += row_add;
    }
    return trees_encountered;
}

int main(int argc, char* argv[]) {
    ifstream input("d3s1.txt");
    vector<vector<bool>> grid;
    while (!input.eof()) {
        string temp;
        getline(input, temp);
        cout << "Read:          " << temp << endl;

        vector<bool> row;
        for (auto entry : temp) {
            row.push_back((entry == '#') ? true : false);
        }

        cout << "Row collected: " << row << endl;
        grid.emplace_back(row);
    }
    cout << "Grid collected:\n" << grid;

    vector<int> row_adds = { 1, 1, 1, 1, 2 };
    vector<int> col_adds = { 1, 3, 5, 7, 1 };
    vector<int> total_trees_encountered;
    for (size_t i = 0; i < row_adds.size(); ++i) {
        cout << "Attempting to count tress with a slope of " << row_adds[i] << " / " << col_adds[i] << endl;
        int trees_encountered = CountTreesEncountered(grid, row_adds[i], col_adds[i]);
        cout << "Encountered " << trees_encountered << " trees" << endl;
        total_trees_encountered.push_back(trees_encountered);
    }

    cout << "All trees encountered: ";
    uint64_t product = 1;
    for (auto encountered : total_trees_encountered) {
        cout << encountered << " ";
        product *= encountered;
    }
    cout << endl;

    cout << "Product of all encounters: " << product << endl;
    return 0;
}
