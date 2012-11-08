#include <iostream>
#include <fstream>

#include "Tokenizer.h"

using namespace std;

int main(int argc, char** argv) {
	ifstream in;
	in.open("test.txt");

	Tokenizer tokenizer = Tokenizer(in);
	Token token;

	while(token.type != EOF_TOKEN) {
		token = tokenizer.getToken();
		cout << '"' << token.text << "\"\n";
	}

	in.close();
}
