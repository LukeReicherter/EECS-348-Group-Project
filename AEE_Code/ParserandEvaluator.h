#ifndef PARSERANDEVALUATOR_H
#define PARSERANDEVALUATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <stdexcept>

using std::runtime_error;
using std::string;
using std::vector;
using std::stack;

class evaluator {
public :
    static double evaluate(double left, const string& op, double right);
};

class parser {
private:

    const vector<string>& tokens;

    int getPrecedence(const string& op) const;

public:
    explicit parser(const vector<string>& tokens);
    double parse();
};

#endif