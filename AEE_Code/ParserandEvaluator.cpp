/*
Created: 11/11/2024
Last Change: 12/10/2024
Designed by Fancy Calculator Inc.
EECS 348: Group Project
Description: The follwing code will take an input tokenized vector of strings and return the
corresponing result of the expression. Each token will be interpreted by the parser through
separate priority level functions.

The current valid operands and operators are as follows:
- Numbers (Including Decimals)
- Unary operators (+ and -)
- Parenthesis
- Operators (**, *, /, %, +)

IMPORTANT NOTE: - not included in operators because it is converted to + -some_operand
if it is used as an operator. - is always considered unary
Example: 10 - 10 is still a valid string, but will become 10 + -10 when tokenized
*/
#include "ParserandEvaluator.h"
#include <cmath> // For pow()

// Constructor
parser::parser(const std::vector<std::string>& inputTokens) : tokens(inputTokens), curIndex(0) {}
// Aquires the token at the current index
std::string parser::getCurToken() const {
    // Checks if the current index is in the bounds of the token vector
    if (curIndex < tokens.size()) {
        // Returns the token at the current index
        return tokens[curIndex];
    }
    // Return empty string if out of bounds
    return "";
}
// "Consumes" the current index. Refers to how the token has been fully evaluated
void parser::consumeToken() {
    // Checks if the current index is in the bounds of the token vector
    if (curIndex < tokens.size()) {
        // Adds 1 to the current index
        curIndex += 1;
    }
}
// Parser function that deals with parentheses, highest priority
double parser::parseTopPrior() {
    // Sets token equal to the token at the current index
    std::string token = getCurToken();
    // Consumes the token
    consumeToken();
    // Checks if token is a left parenthesis
    if (token == "(") {
        // Parse sub-expression within parentheses using recursion
        double result = parseExpression();
        // Consumes the token
        consumeToken();
        // Returns the result of the expression inside the parenthesis
        return result;
    }
    // Checks if token is a negative left parenthesis
    else if (token == "-(") {
        // Parse sub-expression within parenthesis
        double result = parseExpression();
        // Consumes the token
        consumeToken();
        // Returns the negated result, due to the negative in the parenthesis token
        return -result;
    } 
    // Runs if the token is a number
    else {
        // The if statement below handles multiplication of an operand and an expression in parenthesis without a multiplication operator
        // This statement is no longer needed due to how the tokenizer handles multiplication with parentheses
        // Checks if next token is a left parenthesis
        //if (getCurToken() == "(") {
            // Consumes the left parenthesis token
            //consumeToken();
            // Sets the result equal to the token
            //double result = std::stod(token);
            // Parses the sub-expression within parentheses using recursion, then multiplies the return value by the result
            //result *= parseExpression();
            //}
            // Consumes the token
            // consumeToken();
            // Returns the result of the multiplication
            // return result;
        try {
            // Attempts to turn the current token of type string into a double
            return std::stod(token);
            }
        // Catches the failed conversion
        catch (const std::invalid_argument&) {
            // Throws an invalid number error
            throw std::runtime_error("Invalid number: " + token);
        }
    }
}
// Parser function that deals with exponentiation, middle priority
double parser::parseMidPrior() {
    // Double used to climb the priority functions through recursion, will be used as a base if exponentiation occurs
    double base = parseTopPrior();
    // Loop that won't break until a break statement
    while (true) {
        // Sets token equal to the token at the current index
        std::string token = getCurToken();
        // Checks if the token is an exponentiation operator
        if (token == "**") {
            // Consumes the token
            consumeToken();
            // Double that acts as the exponent, uses recursion to find the number to the left of the exponentiation operator
            double exponent = parseTopPrior();
            // Base acts as a result, uses pow to calculate exponentiation
            base = std::pow(base, exponent);
        } 
        // Runs if exponentiation is not detected
        else {
            // Breaks the while loop
            break;
        }
    }
    // Returns the base (result of the exponentiation)
    return base;
}
// Parser function that deals with multiplication, division, and modulus, low priority
double parser::parseLowPrior() {
    // Double used to climb the priority functions through recursion, will be used if mult, div, or mod occurs
    double result = parseMidPrior();
    // Loop that won't break until a break statement
    while (true) {
        // Sets token equal to the token at the current index
        std::string token = getCurToken();
        // Checks if the token is a low priority operator
        if (token == "*" || token == "/" || token == "%") {
            // Consumes the token
            consumeToken();
            // Double found using recursion, will be used in equation
            double nextValue = parseMidPrior();
            // Checks if token is a multiplication operator
            if (token == "*") {
                // Multiplies the result by the next value
                result *= nextValue;
            }
            // Checks if token is a division operator
            else if (token == "/") {
                // Checks if the denominator is a 0
                if (nextValue == 0) {
                    // Prints the error type to screen
                    std::cout << "Divide by zero error" << std::endl;
                    // Throws divide by zero error
                    throw std::runtime_error("Divide by zero error");
                }
                // Divides the result by the next value
                result /= nextValue;
            }
            // Checks if token is a modulus operator
            else if (token == "%") {
                // Checks to see if "b" is a 0
                if (nextValue == 0) {
                    // Prints the error type to screen
                    std::cout << "Mod by zero error" << std::endl;
                    // Throws a mod by 0 error
                    throw std::runtime_error("Mod by zero error");
                }
                // Sets result equal to result modded by the nextValue
                result = std::fmod(result, nextValue);
            }
        } 
        // Runs if no low priority operation is detected
        else {
            // Breaks the while loop
            break;
        }
    }
    // Returns the result
    return result;
}
// Parser function that starts the recursion, also handles the lowest priority operator (addition)
// Since the tokenizer always treats - as negation or (+ -operand), the minus operator is not included
double parser::parseExpression() {
    // Double used to climb the priority functions through recursion, will be used if addition is detected
    double result = parseLowPrior();
    // Loop that won't break until break statement
    while (true) {
        // Sets token equal to the token at the current index
        std::string token = getCurToken();
        // Checks if token is an addition operator
        if (token == "+") {
            // Consumes the token
            consumeToken();
            // Double found using recursion, will be used in the equation
            double nextValue = parseLowPrior();
            // nextValue is added to result
            result += nextValue;
        } 
        // Runs if no addition is detected
        else {
            // Breaks the while loop
            break;
        }
    }
    // Returns the result
    return result;
}
// Parser function that will be used in main to initiate the parsing process
double parser::evaluate() {
    // Will return the result of the parsing process
    return parseExpression();
}
