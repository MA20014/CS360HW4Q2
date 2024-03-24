#include <iostream>
#include <vector>

using namespace std;

class Term {
public:
    int coefficient;
    int exponent;

    Term(int coeff = 0, int exp = 0) : coefficient(coeff), exponent(exp) {}
};

class Polynomial {
private:
    vector<Term> terms;

public:
    // Default constructor
    Polynomial() {}

    // Destructor
    ~Polynomial() {}

    // Set function to add terms to the polynomial
    void setTerm(int coeff, int exp) {
        terms.push_back(Term(coeff, exp));
    }

    // Get function to retrieve the terms of the polynomial
    vector<Term> getTerms() const {
        return terms;
    }

    // Overloaded addition operator (+)
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        int i = 0, j = 0;
        while (i < terms.size() && j < other.terms.size()) {
            if (terms[i].exponent == other.terms[j].exponent) {
                result.setTerm(terms[i].coefficient + other.terms[j].coefficient, terms[i].exponent);
                i++;
                j++;
            } else if (terms[i].exponent > other.terms[j].exponent) {
                result.setTerm(terms[i].coefficient, terms[i].exponent);
                i++;
            } else {
                result.setTerm(other.terms[j].coefficient, other.terms[j].exponent);
                j++;
            }
        }
        while (i < terms.size()) {
            result.setTerm(terms[i].coefficient, terms[i].exponent);
            i++;
        }
        while (j < other.terms.size()) {
            result.setTerm(other.terms[j].coefficient, other.terms[j].exponent);
            j++;
        }
        return result;
    }

    // Overloaded subtraction operator (-)
    Polynomial operator-(const Polynomial& other) const {
        Polynomial result;
        int i = 0, j = 0;
        while (i < terms.size() && j < other.terms.size()) {
            if (terms[i].exponent == other.terms[j].exponent) {
                result.setTerm(terms[i].coefficient - other.terms[j].coefficient, terms[i].exponent);
                i++;
                j++;
            } else if (terms[i].exponent > other.terms[j].exponent) {
                result.setTerm(terms[i].coefficient, terms[i].exponent);
                i++;
            } else {
                result.setTerm(-other.terms[j].coefficient, other.terms[j].exponent);
                j++;
            }
        }
        while (i < terms.size()) {
            result.setTerm(terms[i].coefficient, terms[i].exponent);
            i++;
        }
        while (j < other.terms.size()) {
            result.setTerm(-other.terms[j].coefficient, other.terms[j].exponent);
            j++;
        }
        return result;
    }

    // Overloaded assignment operator (=)
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            terms = other.terms;
        }
        return *this;
    }

    // Overloaded multiplication operator (*)
    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;
        for (const auto& term1 : terms) {
            for (const auto& term2 : other.terms) {
                int newCoefficient = term1.coefficient * term2.coefficient;
                int newExponent = term1.exponent + term2.exponent;
                bool termExists = false;

                // Check if a term with the same exponent exists in the result polynomial
                for (auto& term : result.terms) {
                    if (term.exponent == newExponent) {
                        term.coefficient += newCoefficient;
                        termExists = true;
                        break;
                    }
                }

                // If the term doesn't exist, add it to the result polynomial
                if (!termExists) {
                    result.setTerm(newCoefficient, newExponent);
                }
            }
        }
        return result;
    }

    // Overloaded addition assignment operator (+=)
    Polynomial& operator+=(const Polynomial& other) {
        *this = *this + other;
        return *this;
    }

    // Overloaded subtraction assignment operator (-=)
    Polynomial& operator-=(const Polynomial& other) {
        *this = *this - other;
        return *this;
    }

    // Overloaded multiplication assignment operator (*=)
    Polynomial& operator*=(const Polynomial& other) {
        *this = *this * other;
        return *this;
    }

    // Print function to display the polynomial
    void print() const {
        if (terms.empty()) {
            cout << "0";
        } else {
            for (size_t i = 0; i < terms.size(); ++i) {
                if (i != 0 && terms[i].coefficient > 0) {
                    cout << " + ";
                }
                cout << terms[i].coefficient;
                if (terms[i].exponent > 0) {
                    cout << "x";
                    if (terms[i].exponent > 1) {
                        cout << "^" << terms[i].exponent;
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Example usage
    Polynomial p1, p2;

    // Set terms for Polynomial p1
    p1.setTerm(2, 3); // 2x^3
    p1.setTerm(-1, 2); // -1x^2
    p1.setTerm(4, 0); // 4

    // Set terms for Polynomial p2
    p2.setTerm(3, 2); // 3x^2
    p2.setTerm(2, 1); // 2x^1
    p2.setTerm(5, 0); // 5

    // Addition
    Polynomial p3 = p1 + p2;
    cout << "Addition: ";
    p3.print();

    // Subtraction
    Polynomial p4 = p1 - p2;
    cout << "Subtraction: ";
    p4.print();

    // Multiplication
    Polynomial p5 = p1 * p2;
    cout << "Multiplication: ";
    p5.print();

    return 0;
}