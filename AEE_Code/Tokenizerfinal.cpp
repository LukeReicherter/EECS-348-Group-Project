
#include "Tokenizer.h"
#include <cctype> // For isdigit

// Constructor
tokenizer::tokenizer(const string& expr) : expression(expr) {}

// Function to tokenize the input expression
bool tokenizer::tokenize() {
    // neg_condition keeps track of the minus operator
    bool neg_condition = false;
    // parenthesis_check keeps track of the amount of parenthesis
    int parenthesis_check = 0;
    // This loop iterates through the input string to separate tokens by type
    for (int i = 0; i < expression.length();) {
        // Checks if char is a digit or a decimal
        if (isdigit(expression[i]) || expression[i] == '.') {
            // Checks if the last token was a digit
            if (!token_vector.empty() && (isdigit(token_vector.back().back()))) {
                // Displays an error message
                cout << "Invalid Input Error" << endl;
                // Returns false to end the tokenizer
                return false;
            }
            // Checks if an expression in parenthesis is being multiplied
            if (!token_vector.empty() && (token_vector.back() == ")")) {
                // Initiates a string called mult and sets it equal to a multiplication operator
                string mult = "*";
                // Adds mult to the vector of tokens
                token_vector.push_back(mult);
            }
            // Initiates a string called num, will store the current number token
            string num;
            // Checks a negative sign needs to be applied
            if (neg_condition) {
                // Adds negative sign to num
                num += "-";
                // Inverts the current negative condition
                neg_condition = !neg_condition;
            }
            // decimal_check determines if a decimal has already been added to the current number
            bool decimal_check = false;
            // This while loop will continue to add digits to num until no digit is detected at index i
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                // Checks if the current char is a decimal
                if (expression[i] == '.') {
                    // Checks if a decimal has already been added
                    if (decimal_check) {
                        // Displays an error message
                        cout << "Invalid Input Error" << endl;
                        // Returns false to end the tokenizer
                        return false;
                    }
                    // Inverts the current decimal condition
                    decimal_check = !decimal_check;
                }
                num += expression[i];
                // Adds 1 to the current index
                i++;
            }
            // Checks if a the current number has a decimal as the last char in the string
            if (num.back() == '.') {
                // Adds a zero to num, important when checking if the last token is a number
                num += "0";
            }
            // Adds num to the vector of tokens
            token_vector.push_back(num);
        }
        // Checks if char is a space
        else if (isspace(expression[i])) {
            // Adds 1 to the current index
            i++;
        }
        // Checks if char is a left parenthesis
        else if (expression[i] == '(') {
            // Checks if the expression in parenthesis is being multiplied
            if (!token_vector.empty() && (isdigit(token_vector.back().back()) || token_vector.back() == ")")) {
                // Initiates a string called mult and sets it equal to a multiplication operator
                string mult = "*";
                // Adds mult to the vector of tokens
                token_vector.push_back(mult);
            }
            // Initiates a string called left_paren and sets it equal to the char at the current index
            string left_paren;
             // Checks if the neg_condition is true to determine if a negative will be applied to the parenthesis
            if (neg_condition) {
                // Adds a negaive sign to the parenthesis. Indicates that the number in the parenthesis will be negated
                left_paren += "-";
                // Inverts the current negative condition
                neg_condition = !neg_condition;
            }
            // Adds the left parenthesis to the left_paren variable
            left_paren += expression[i];
            // Adds 1 to the parenthesis check
            parenthesis_check += 1;
            // Adds 1 to the current index
            i++;
            // Adds left_paren to the vector of tokens
            token_vector.push_back(left_paren);
        }
        // Checks if char is a right parenthesis
        else if (expression[i] == ')') {
            // Checks to make sure last token is a number
            if (!token_vector.empty() && (isdigit(token_vector.back().back()) || token_vector.back() == ")" || token_vector.back() == "(")) {
                // Initiates a string called right_paren and sets it equal to the char at the current index
                string right_paren;
                // Adds the right parenthesis to the right_paren variable
                right_paren += expression[i];
                // Subtracts 1 from the parenthesis check
                parenthesis_check -= 1;
                // Checks if parenthesis_check is less than 0
                if (parenthesis_check < 0) {
                    // Displays an error message
                    cout << "Unmatched Parenthesis Error" << endl;
                    // Returns false to end the tokenizer
                    return false;
                }
                // Adds 1 to the current index
                i++;
                // Adds right_paren to the vector of tokens
                token_vector.push_back(right_paren);
            }
            // Runs if the right parenthesis is in an invalid position
            else {
                // Displays an error message
                cout << "Invalid Input Error" << endl;
                // Returns false to end the tokenizer
                return false;
            }
        }
        // Checks if char is a minus operator
        else if (expression[i] == '-') {
            // Checks if the last token in the vector is a digit
            if (!token_vector.empty() && (isdigit(token_vector.back().back()) || token_vector.back() == ")")) {
                // Initiates a string called plus and sets it equal to an addition operator
                string plus = "+";
                // Adds plus to the vector of tokens
                token_vector.push_back(plus);
            }
            // Inverts the current negative condition 
            neg_condition = !neg_condition;
            // Adds 1 to the current index
            i++;
        }
        // Checks if token vector is empty
        else if (token_vector.empty()) {
            // Displays an error message
            cout << "Invalid Input Error" << endl;
            // Returns false to end the tokenizer
            return false;
        }
        // Checks if char is a multiplication operator
        else if (expression[i] == '*') {
            // Checks if the last token is also an multiplication operator
            if (token_vector.back() == "*") {
                // Converts the last token into an exponentiation operator
                token_vector.back() += "*";
                // Adds 1 to the current index
                i++;
            }
            // Checks if last token is a number or a parenthesis
            else if (isdigit(token_vector.back().back()) || token_vector.back() == ")") {
                // Initiates a string called mult and sets it equal to a multiplication operator
                string mult = "*";
                // Adds mult to the vector of tokens
                token_vector.push_back(mult);
                // Adds 1 to the current index
                i++;
            }
            // Runs if multiplication operator is in an invalid position
            else {
                // Displays an error message
                cout << "Invalid Input Error" << endl;
                // Returns false to end the tokenizer
                return false;
            }
        }
        // Checks if char is a division operator
        else if (expression[i] == '/') {
            // Checks if last token is a number or a parenthesis
            if (isdigit(token_vector.back().back()) || token_vector.back() == ")") {
                // Initiates a string called div and sets it equal to a division operator
                string div = "/";
                // Adds div to the vector of tokens
                token_vector.push_back(div);
                // Adds 1 to the current index
                i++;
            }
            // Runs if the division operator is in an invalid position
            else {
                // Displays an error message
                cout << "Invalid Input Error" << endl;
                // Returns false to end the tokenizer
                return false;
            }
        }
        // Checks if char is an addition operator
        else if (expression[i] == '+') {
            // Checks if the last token is a number or a parenthesis
            if (isdigit(token_vector.back().back()) || token_vector.back() == ")") {
                // Initiates a string called plus and sets it equal to an addition operator
                string plus = "+";
                // Adds plus to the vector of tokens
                token_vector.push_back(plus);
                // Adds 1 to the current index
                i++;
            }
            // Runs if the addition operator is in an invalid position
            else {
                // Displays an error message
                cout << "Invalid Input Error" << endl;
                // Returns false to end the tokenizer
                return false;
            }
        }
        // Checks if char is a modulo operator
        else if (expression[i] == '%') {
            if (isdigit(token_vector.back().back()) || token_vector.back() == ")") {
                // Initiates a string called mod and sets it equal to a modulo operator
                string mod = "%";
                // Adds mod to the vector of tokens
                token_vector.push_back(mod);
                // Adds 1 to the current index
                i++;
            }
            // Runs if the modulo operator is in an invalid position
            else {
                // Displays an error message
                cout << "Invalid Input Error" << endl;
                // Returns false to end the tokenizer
                return false;
            }
        }
        // Runs if an unknown char is detected
        else {
            // Displays an error message
            cout << "Unknown Character Error" << endl;
            // Returns false to end the tokenizer
            return false;
        }
    }
    // Checks if the correct amount of parenthesis have been entered
    if (parenthesis_check != 0) {
        // Displays an error message
        cout << "Unmatched Parenthesis Error" << endl;
        // Returns false to end the tokenizer
        return false;
    }
    // Checks if the last token is an operator
    else if (!token_vector.empty() && (!isdigit(token_vector.back().back()) && token_vector.back() != ")")) {
        // Displays an error message
        cout << "Invalid Input Error" << endl;
        // Returns false to end the tokenizer
        return false;
    }   
    // Runs if expression is fully tokenized with no errors
    else {
        // Returns true to end the tokenizer
        return true;
    }
};
// Function used to print tokens, for testing purposes
//void tokenizer::print_tokens() {
    //for (int i = 0; i < token_vector.size(); i++) {
        //cout << token_vector[i] << " ";
    //}
    //cout << endl;
//}
