#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
struct token {
    T value;
};

class tokenizer {
public:
    string expression;
    vector< token<string> > token_vector;

    tokenizer(const string& expr);
    bool tokenize();
    void print_tokens();

};

#endif // TOKENIZER_H