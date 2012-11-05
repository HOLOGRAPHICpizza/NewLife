#include <iostream>

#include "Tokenizer.h"

using namespace std;

int main(int argc, char** argv) {
	Tokenizer tokenizer = Tokenizer(cin);
	Token token;

	token = tokenizer.getNonSeparatorToken();
	
	cout << token.text << '\n';
}
