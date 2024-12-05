/*
Created: 11/11/2024
Last Change: 12/05/2024
Designed by Fancy Calculator Inc.
EECS 348: Group Project
Description: The following code defines the parser class located in the
ParserandEvaluator.cpp file. 
*/
#ifndef PARSERANDEVALUATOR_H
#define PARSERANDEVALUATOR_H

#include <vector>
#include <string>
#include <stdexcept>

class parser {
public:
    // Constructor to initialize the parser with a vector of tokens
    explicit parser(const std::vector<std::string>& inputTokens);

    // Used by the main to obtain the final result of the parser
    double evaluate();

private:
    // Stores the tokenized input of the user
    std::vector<std::string> tokens; 
    // Stores the current index in the vector of tokens
    int curIndex;

    // Returns the current token in the token vector
    std::string getCurToken() const;
    // Consumes/Advances to the next token
    void consumeToken();
    // Parses top priority operators
    double parseTopPrior(); 
    // Parses mid priority operators
    double parseMidPrior();
    // Parses low priority operators
    double parseLowPrior();
    // Starts the recursion process and handles the addition operator
    double parseExpression();
};

#endif
