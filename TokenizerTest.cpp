#include <iostream>

#include "Token.h"

using namespace std;

int main(int argc, char** argv) {
	Identifier x;
	x.text = "taco";
	
	cout << x.text << '\n';
}
