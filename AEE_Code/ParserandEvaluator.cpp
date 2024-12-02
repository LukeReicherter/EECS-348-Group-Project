#include "ParserandEvaluator.h"
#include <cctype> // For isdigit
#include <cmath> // For pow() and fmod()

double evaluator::evaluate(double left, const string& op, double right) {
    // Checks if a number inside of parenthesis needs to be negated
    if (op == "-(") {
        // Returns the number inside the parenthesis negated
        return -right;
    }
    // Checks if the input operator is an addition sign
    if (op == "+") {
        // Evaluates the left number plus the right number
        return left + right;
    }
    // Checks if the input operator is a multiplication sign
    if (op == "*") {
        // Evaluates the left number times the right number
        return left * right;
    }
    // Checks if the input operator is a division sign
    if (op == "/") {
        // Checks if the left number is being divided by zero
        if (right == 0) {
            // Throws a runtime error due to dividing by zero
            throw runtime_error("Division by zero error");
        }
        // Runs if the division operation is valid
        else {
            // Evaluates the left number divided by the right
            return left / right;
        }
    }
    // Checks if the input operator is an exponentiation sign
    if (op == "**") {
        // Evaluates the left number raised to the right number
        return pow(left, right);
    }
    // Checks if the input operator is a modulo sign
    if (op == "%") {
        // Evaluated the left number modded by the right number
        return fmod(left, right);
    }
    // Returns zero if no valid operation is found (should not happen as all invalid operators are found in the tokenizer)
    return 0;
}
// Constructor
parser::parser(const std::vector<std::string>& tokens) : tokens(tokens) {}

// Obtains the precedence of the given operator
int parser::getPrecedence(const std::string& op) const {
    // Checks if the operator is an exponentiation
    if (op == "**") {
        // Returns 0, which corresponds to the highest precedence
        return 2;
    }
    // Checks if the operator is a multiplication, division, or modulo sign
    else if (op == "*" || op == "/" || op == "%") {
        // Returns 1, which corresponds to the scond highest precedence
        return 1;
    }
    // Checks if the operator is a addition sign
    else if (op == "+" || op == "-(") {
        // Returns 2, which corresponds to the third highest precedence
        return 0;
    }
    // Runs if string is not an existing operator
    else {
        // Returns 3, which does not correspond to operator precedence
        return -1;
    }
}

double parser::parse() {
    vector<string> postfix_vector;
    stack<string> postfix_stack;
    for (int i = 0; i < tokens.size(); i++) {
        if (isdigit(tokens[i][1])) {
            postfix_vector.push_back(tokens[i]);
        }
        else if (tokens[i] == "(" || tokens[i] == "-(") {
            postfix_stack.push(tokens[i]);
        }
        else if (tokens[i] == ")") {
            while (!postfix_stack.empty() && postfix_stack.top() != "(" && postfix_stack.top() != "-(") {
                postfix_vector.push_back(postfix_stack.top());
                postfix_stack.pop();
            }
            if (!postfix_stack.empty() && (postfix_stack.top() == "(" || postfix_stack.top() == "-(")) {
                if (postfix_stack.top() == "-(") {
                    postfix_vector.push_back(postfix_stack.top());
                }
                postfix_stack.pop();
            }
        }
        else {
            while (!postfix_stack.empty() && (getPrecedence(postfix_stack.top()) > getPrecedence(tokens[i]) || (getPrecedence(postfix_stack.top()) == getPrecedence(tokens[i]) && tokens[i] != "**"))) {
                postfix_vector.push_back(postfix_stack.top());
                postfix_stack.pop();
            }
            postfix_stack.push(tokens[i]);
        }
    }
    while (!postfix_stack.empty()) {
        postfix_vector.push_back(postfix_stack.top());
        postfix_stack.pop();
    }
    for (size_t j = 0; j < tokens.size(); j++) {
        std::cout << postfix_vector[j] << " ";
    }
    std::cout << std::endl;
    return 0;
}
