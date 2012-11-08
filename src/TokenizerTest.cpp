#include <iostream>
#include <fstream>

#include "Tokenizer.h"

using namespace std;

int main(int argc, char** argv) {
	ifstream in;
	in.open("test.txt");

	Tokenizer tokenizer = Tokenizer(in);
	Token token;

	token = tokenizer.getNonSeparatorToken();
	cout << '"' << token.text << "\"\n";
	token = tokenizer.getNonSeparatorToken();
	cout << '"' << token.text << "\"\n";
	token = tokenizer.getNonSeparatorToken();
	cout << '"' << token.text << "\"\n";
	token = tokenizer.getNonSeparatorToken();
	cout << '"' << token.text << "\"\n";
	token = tokenizer.getNonSeparatorToken();
	cout << '"' << token.text << "\"\n";
	token = tokenizer.getNonSeparatorToken();
	cout << '"' << token.text << "\"\n";

	in.close();
}
