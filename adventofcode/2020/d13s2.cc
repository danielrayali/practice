#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Represents a congruence of the form x ≡ a (mod b) where "a" is the remainder and "b" is the modulus.
// x is unspecified.
struct Congruence {
    long long modulus = -1;
    long long remainder = -1;

    Congruence(const long long _modulus, const long long _remainder) :
        modulus(_modulus), remainder(_remainder) {}

    Congruence(const Polynomial& polynomial) :
        modulus(polynomial.coefficient), remainder(polynomial.constant) {}
};

// Represents a polynomial of the form y = ax + b. Where "a" is the coefficient and "b" is the constant.
// x and y are unspecified variables.
struct Polynomial {
    long long coefficient = -1;
    long long constant = -1;

    Polynomial(const long long _coefficient, const long long _constant) :
        coefficient(_coefficient), constant(_constant) {}

    Polynomial(const Congruence& congruence) :
        coefficient(congruence.modulus), constant(congruence.remainder) {}
};

// Shamelessly stolen from this well answered stack overflow question:
// https://stackoverflow.com/questions/14029516/need-an-efficient-subtraction-algorithm-modulo-a-number
long long ModuloSubtract(const long long minuend, const long long subtrahend, const long long modulus) {
    return ((minuend - subtrahend) % modulus) + ((minuend >= subtrahend) ? 0 : modulus);
}

long long ModuloDivide(const long long dividend, const long long divisor, const long long modulus) {
    if (divisor == 0) {
        throw runtime_error("Cannot divide by zero");
    }
    // Get the multiplicative inverse of the divisor
    long long inverse = 1;
    long long product = divisor;
    while ((product % modulus) != 1) {
        inverse++;
        product = (divisor * inverse);
    }

    return (inverse * dividend) % modulus;
}

// Executes a single iteration of the Chinese remainder theorem
Polynomial CRTIteration(const Polynomial& polynomial, const Congruence& congruence) {
    long long value = ModuloSubtract(congruence.remainder, polynomial.constant, congruence.modulus);
    value = ModuloDivide(value, polynomial.coefficient, congruence.modulus);
    return Polynomial(congruence.modulus, value);
}

ostream& operator<<(ostream& out, const Congruence& congruence) {
    out << "x ≡ " << congruence.remainder << " (mod " << congruence.modulus << ")";
    return out;
}

ostream& operator<<(ostream& out, const Polynomial& polynomial) {
    out << "y = " << polynomial.coefficient << "x + " << polynomial.constant;
    return out;
}

int main(int argc, char* argv[]) {
    ifstream input("d13s1.txt");
    string arrival_str;
    getline(input, arrival_str);
    const long long earliest_start = atoll(arrival_str.c_str());
    cout << "Read: " << earliest_start << endl;

    vector<Congruence> system;
    long long count = 0;
    while (!input.eof()) {
        string bus_id_str;
        getline(input, bus_id_str, ',');
        cout << "Read: " << bus_id_str << endl;
        if (bus_id_str == "x") {
            // bus_id_str = "1";
            continue;
        }

        system.emplace_back(atoll(bus_id_str.c_str()), count);
        count++;
    }

    // Sort by descending moduli
    sort(system.begin(), system.end(), [](const Congruence& a, const Congruence& b) -> bool{
        return a.modulus > b.modulus;
    });

    cout << "System of congruences to solve: " << endl;
    for (auto congruence : system) {
        cout << "  " << congruence << endl;
    }

    Polynomial polynomial(system.front());
    for (int i = 1; i < system.size(); i++) {
        cout << "iteration " << i << endl;
        polynomial = CRTIteration(polynomial, system[i]);
    }

    cout << "Resulting polynomial: " << polynomial << endl;
    cout << "4 - 6 (mod 5) = " << ModuloSubtract(4, 6, 5) << endl;
    cout << "3 / 7 (mod 5) = " << ModuloDivide(3, 7, 5) << endl;
    return 0;
}