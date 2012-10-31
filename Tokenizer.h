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
};

struct Token {
	std::string text;
	TokenType type;
};

class Tokenizer {
public:
	Tokenizer(istream& ins);
	Token GetToken(Token& token);
};

#endif
