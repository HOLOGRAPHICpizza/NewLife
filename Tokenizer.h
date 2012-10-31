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
	ERROR,
	EOF_TOKEN
};

struct Token {
	std::string text;
	TokenType type;
};

class Tokenizer {
private:
	std::istream& ins;
	
	std::string buffer;
	
	enum BufferState {
		EMPTY_BS,
		ID_KEYWORD_COND_BS,
		WHITESPACE_BS,
		COMMENT_BS,
		ERROR_BS,
		EOF_BS
	};
	
	BufferState bufferState;
	
	bool tokenReady;


	// process the next char from ins
	void nextChar();
	
	
	static TokenType tokenType(BufferState bufferState, const std::string& tokenText);
public:
	Tokenizer(std::istream& ins);
	
	// This will copy token,
	// but return value optimization makes this OK
	Token getToken();
	Token getNonSeparatorToken();
};

#endif
