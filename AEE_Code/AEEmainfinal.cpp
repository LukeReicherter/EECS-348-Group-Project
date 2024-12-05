/*
Created: 11/11/2024
Last Change: 12/05/2024
Designed by Fancy Calculator Inc.
EECS 348: Group Project
Description: The following code will take a user input expression as a string and
return a result as a double. If an invalid expression is entered, an error message 
will print to screen. The user will be able to continue to enter expressions until 
"END" is typed into the input.

The current valid operands and operators are as follows:
- Numbers (Including Decimals)
- Unary operators (+ and -)
- Parenthesis
- Operators (**, *, /, %, +)

IMPORTANT NOTE: - not included in operators because it is converted to + -some_operand
if it is used as an operator. - is always considered unary
Example: 10 - 10 is still a valid string, but will become 10 + -10 when tokenized
*/
#include "Tokenizer.h"
#include "ParserandEvaluator.h"
#include <iostream>
#include <iomanip>

#define PRECISION 5 // Sets the precision of the result equal to 5

int main() {
    // Loop that won't break until break statement
    while (true) {
        // Initiates a string named expr, used to store the user input
        string expr;
        // Prints the prompt for the user, starts with an endl to make the output look cleaner
        cout << endl << "Enter an arithmetic expression (enter 'END' to stop program): ";
        // Obtains the input and stores it in the expr variable
        getline(cin, expr);
        // Checks if the user input END or end
        if (expr == "END" || expr == "end") {
            // Ends the while loop, therefore ending the entire program
            break;
        }
        // Sends the expression to the tokenizer
        tokenizer tk(expr);
        // Checks if the expression is able to be tokenized
        if (tk.tokenize()) {
            // If the tokenizer returns true, the expr variable has been properly tokenized
            // The program will attempt to parse the vector of tokens
            try {
                // Sends the token_vector to the parser
                parser parser(tk.token_vector);
                // Uses the evaluate function to obtain the result
                double result = parser.evaluate();
                // Prints the result to the user with a precision equal to the PRECISION value
                cout << result << std::setprecision(PRECISION) << endl;
            }
            // If the program fails to parse, the catch statement runs
            catch(...) {
                // Prints failure message to the screen
                cout << "Failed to evaluate tokens, please try again" << endl;
            }
        } 
        // Runs if expr fails to tokenize
        else {
            // Prints failure message to screen
            cout << "Failed to tokenize the expression due to errors." << endl;
        }
    }
}
