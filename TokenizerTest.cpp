#include <iostream>

#include "Token.h"

using namespace std;

int main(int argc, char** argv) {
	Tokenizer tokenizer = new Tokenizer(cin);
	Token token;

	token = tokenizer.GetToken();
	
	cout << token.text << '\n';
}
