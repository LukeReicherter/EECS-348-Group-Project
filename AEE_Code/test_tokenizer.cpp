#include "Tokenizer.h"
#include <cctype> // For isdigit

// Constructor
tokenizer::tokenizer(const string& expr) : expression(expr) {}

// Function to tokenize the input expression
bool tokenizer::tokenize() {
    string valid_operators = "+-/*%";
    int parenthesis_check = 0;
    for (int i = 0; i < expression.length();) {
            if (isdigit(expression[i])) { 
                string num;
                while (i < expression.length() && isdigit(expression[i])) {
                    num += expression[i];
                    i++;
                }
                token<string> t;
                t.value = num;
                token_vector.push_back(t);
            }
            else if (isspace(expression[i])) {
                i++;
            }
            else if (expression[i] == '(') {
                string paren;
                paren += expression[i];
                token<string> t;
                t.value = paren;
                parenthesis_check += 1;
                token_vector.push_back(t);
                i++;
            }
            else if (expression[i] == ')') {
                string paren;
                paren += expression[i];
                token<string> t;
                t.value = paren;
                parenthesis_check -= 1;
                if (parenthesis_check < 0) {
                    cout << "Unmatched Parenthesis Error";
                    return false;
                }
                token_vector.push_back(t);
                i++;
            }
            else if (valid_operators.find(expression[i]) != string::npos) {
                string op;
                if (i < expression.length()) {
                    if (expression[i] == '*' && expression[i+1] == '*') {
                        op += expression[i];
                        op += expression[i+1];
                        i++;
                    }
                    else {
                        op += expression[i];
                    }
                    if (valid_operators.find(expression[i+1]) != string::npos) {
                        cout << "Incorrect Input Error: Entered '" << expression[i] << "' when expecting a number";
                        return false;
                    }
                }
                else {
                    cout << "Incorrect Input Error: Expected a number after '" << expression[i] <<"'";
                    return false;
                }
                token<string> t;
                t.value = op;
                token_vector.push_back(t);
                i++;
            }
            else {
                cout << "Incorrect Input Error: '" << expression[i] << "' is an invalid character";
                return false;
            }
        }
    return true;
};

void tokenizer::print_tokens() {
    for (size_t i = 0; i < token_vector.size(); i++) {
        cout << token_vector[i].value << " ";
    }
    cout << endl;
}