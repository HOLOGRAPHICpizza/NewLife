#ifndef __TOKENIZER
#define __TOKENIZER

#include <string>
#include <istream>

enum TokenType {
	KEYWORD,
	IDENTIFIER,
	CONDITION,
	WHITE_SPACE,
	COMMENT,
	ERROR
}

struct Token {
	std::string text,
	TokenType type
}

class Tokenizer {
public:
	virtual Tokenizer(istream ins);
	virtual Token GetToken() = 0;
}

#endif
