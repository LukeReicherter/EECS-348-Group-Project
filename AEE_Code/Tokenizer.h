/*
Created: 11/11/2024
Last Change: 12/05/2024
Designed by Fancy Calculator Inc.
EECS 348: Group Project
Description: The following code defines the tokenizer class located in the
Tokenizer.cpp file. 
*/
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

class tokenizer {
public:
    // Stores the users expression
    std::string expression;
    // Will store the tokenized expression
    vector<string> token_vector;

    // Constructor
    tokenizer(const string& expr);
    // Tokenizes the input, returns true if no errors are found
    bool tokenize();
    // Prints the token vector
    // Not needed, used for testing
    //void print_tokens();
};

#endif
