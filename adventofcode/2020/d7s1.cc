#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Bag {
    // Contains the color of bags within this one
    vector<string> contains_colors;

    // Contains the number of bags at the same index in contains_colors
    vector<int> contains_counts;
};

ostream& operator<<(ostream& out, const Bag& bag) {
    if (bag.contains_counts.empty() || bag.contains_colors.empty()) {
        out << "no other bags";
    } else {
        out << bag.contains_counts[0] << " " << bag.contains_colors[0] << " bags";
        for (int i = 1; i < bag.contains_colors.size(); i++) {
            out << ", " << bag.contains_counts[i] << " " << bag.contains_colors[i] << " bags";
        }
    }
    out << ".";
    return out;
}

void Contains(const map<string, Bag>& bags, string color, set<string>& can_contain) {
    cout << "Searching for " << color << endl;
    for (auto container_iter : bags) {
        cout << "  Considering " << container_iter.first << endl;
        if (container_iter.first == color) {
            cout << "  Skipping " << color << " because its the color we're looking for" << endl;
            continue;
        }

        for (int i = 0; i < container_iter.second.contains_colors.size(); i++) {
            if (container_iter.second.contains_colors[i] == color) {
                cout << "  Found that " << container_iter.first << " contains " << color << endl;
                auto result = can_contain.insert(container_iter.first);
                if (!result.second) {
                    cout << "  " << container_iter.first << " was already counted when inserting" << endl;
                }
                Contains(bags, container_iter.first, can_contain);
                cout << "Back to searching for " << color << endl;
            }
        }
    }
    cout << "Done searching for " << color << endl;
}

int main(int argc, char* argv[]) {
    ifstream input("d7s1.txt");
    map<string, Bag> bags;
    while (!input.eof()) {
        cout << "Reading new bag rule" << endl;
        string temp;
        string containing_color;
        input >> temp;  // light
        cout << "Read: " << temp << endl;
        containing_color += temp;
        input >> temp;  // red
        cout << "Read: " << temp << endl;
        containing_color += " " + temp;

        input >> temp;  // bags
        cout << "Read: " << temp << endl;
        input >> temp;  // contain
        cout << "Read: " << temp << endl;

        Bag bag;
        while (temp != "bags." && temp != "bag.") {
            input >> temp;  // 1 or "no"
            cout << "Read: " << temp << endl;
            if (temp == "no") {
                input >> temp;  // other
                cout << "Read: " << temp << endl;
                input >> temp;  // bags.
                cout << "Read: " << temp << endl;
                break;
            }
            int temp_int = atoi(temp.c_str());
            bag.contains_counts.push_back(temp_int);

            string color;
            input >> temp;  // bright
            color += temp;
            input >> temp;  // white
            color += " " + temp;
            cout << "Read: " << color << endl;
            bag.contains_colors.push_back(color);

            input >> temp;  // "bag,", "bags," or "bags."
            cout << "Read: " << temp << endl;
        }
        bags.emplace(containing_color, bag);
    }

    for (auto iter : bags) {
        cout << iter.first << " bags contain " << iter.second << endl;
    }

    set<string> can_contain;
    Contains(bags, "shiny gold", can_contain);

    cout << "Total count: " << can_contain.size() << endl;
    return 0;
}
