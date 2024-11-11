#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <typename T> struct token {
    T x;
};

class tokenizer {
    public:
        string expression;
        vector<token> token_vector;
        tokenizer() {
            for (int i = 0; i < expression.length(); i++) {
                while (true) {
                    int j = 0;
                    if (isdigit(expression.at(i))) { 
                        token<int> temp;

                        
                        }
                    }
                }
            }
        }
}