#include "Tokenizer.h"
#include "ParserandEvaluator.h"
#include <iostream>

int main() {
    while (true) {
        string expr;
        cout << "Enter an arithmetic expression: ";
        getline(cin, expr);
        tokenizer tk(expr);
        if (tk.tokenize()) {
            cout << "Tokens: ";
            tk.print_tokens();
            parser ps(tk.token_vector);
            ps.parse();
        } else {
            cout << "Failed to tokenize the expression due to errors." << endl;
        }
    }
}
