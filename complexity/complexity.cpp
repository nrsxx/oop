#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

struct Literal {
    bool neg;
    int index;
};

class Clause {
    friend ostream& operator<<(ostream&, const Clause&);
private:
    Literal literals[3];
public:
    Literal& operator[](size_t index) {
        return literals[index];
    }
    bool evaluate(const vector<bool>& vars) {
        bool result = literals[0].neg != vars[literals[0].index];
        result = result || (literals[1].neg != vars[literals[1].index]);
        result = result || (literals[2].neg != vars[literals[2].index]);
        return result;
    }
};

class Equation {
    friend ostream& operator<<(ostream&, const Equation&);
private:
    vector<Clause> equation_;
    int numberOfVars_;

    // returns the index of the first unsatisfied clause if it exists, -1 if satisfied
    int evaluate(const vector<bool> &vars) {
        for (int i = 0; i < equation_.size(); ++i) {
            if (!equation_[i].evaluate(vars)) {
                return i;
            }
        }
        return -1;
    }
    // creates bijection between sets of n variables and numbers 0..2^n
    vector<bool> transform(long long num) {
        vector<bool> answer(numberOfVars_);
        for (int i = 0; i < numberOfVars_; ++i) {
            answer[i] = num % 2;
            num /= 2;
        }
        return answer;
    }
public:
    Equation(const vector<Clause> &equation, int numberOfVars)
        : equation_(equation), numberOfVars_(numberOfVars) {
    }

    // generates random equation with the given number of clauses
    Equation(int numberOfClauses, int numberOfVars) : numberOfVars_(numberOfVars) {
        equation_.resize(numberOfClauses);
        for (int i = 0; i < numberOfClauses; ++i) {
            for (int j = 0; j < 3; ++j) {
                equation_[i][j].neg = rand() % 2;
                equation_[i][j].index = rand() % numberOfVars;
            }
        }
    }

    // return satisfiable values of variables if it exists, empty vector otherwise
    vector<bool> solve() {
        vector<bool> answer;
        for (long long i = 0; i < pow(2, numberOfVars_); ++i) {
            answer = transform(i);
            if (evaluate(answer) == -1) {
                return answer;
            }
        }
        answer.resize(0);
        return answer;
    }
};

// reads a literal from the keyboard
void readLiteral(std::istringstream &inStream, Literal &literal) {
    char character;

    inStream >> character;

    if (character == '!') {
        literal.neg = true;

        // skips 'x'
        inStream >> character;
    } else {
        literal.neg = false;
    }

    // skips '_'
    inStream >> character;

    inStream >> literal.index;
}

// reads a clause from the keyboard
void readClause(std::istringstream &inStream, Clause &clause) {
    char character;

    // skips '('
    inStream >> character;

    for (int i = 0; i < 2; ++i) {
        readLiteral(inStream, clause[i]);

        // skips "||"
        inStream >> character;
        inStream >> character;
    }

    readLiteral(inStream, clause[2]);

    // skips ')'
    inStream >> character;
}

// reads an equation from the keyboard
Equation readEquation() {
    int numberOfVariables;
    string inputLine;

    cout << "Enter number of variables:" << endl;
    std::getline(cin, inputLine);
    std::istringstream numStream(inputLine);
    numStream >> numberOfVariables;

    cout << "Enter equation (use only \"x_0\", ... , \"x_{numberOfVariables - 1}\" variables)" << endl;
    cout << "Example: \"(x_0 || !x_1 || x_2) & (!x_0 || x_1 || x_2)\" :" << endl;
    std::getline(cin, inputLine);


    vector<Clause> equation;

    std::istringstream inStream(inputLine);
    char character;

    Clause currentClause;

    while (!inStream.eof()) {
        readClause(inStream, currentClause);
        equation.push_back(currentClause);

        // skips '&'
        inStream >> character;
    }

    return Equation(equation, numberOfVariables);
}

// prints the result of Equation::solve()
void printResult(vector<bool> vars) {
    if (vars.size() == 0) {
        cout << "Unsatisfied." << endl;
        return;
    }

    cout << "Satisfied:" << endl;

    for (int i = 0; i < vars.size(); ++i) {
        cout << "x_" << i << " = " << vars[i] << "; ";
    }

    cout << endl;
}

void testRandom(int numberOfClauses, int numberOfVariables) {
    Equation equation(numberOfClauses, numberOfVariables);
    cout << equation;
    printResult(equation.solve());
}

ostream& operator<<(ostream& os, const Literal& l) {
    if (l.neg) {
        os << "!";
    }
    os << "x_" << l.index;
    return os;
}

ostream& operator<<(ostream& os, const Clause& c) {
    os << "(" << c.literals[0] << " || " << c.literals[1] << " || " << c.literals[2] << ")";
    return os;
}

ostream& operator<<(ostream& os, const Equation& e) {
    if (e.equation_.size() > 0) {
        os << e.equation_[0];
    }
    for (int i = 1; i < e.equation_.size(); ++i) {
        os << " & " << e.equation_[i];
    }
    os << endl;
    return os;
}

int main() {
    srand(time(NULL));

    //testRandom(2, 6);

    Equation equation = readEquation();
    printResult(equation.solve());

    return 0;
}
