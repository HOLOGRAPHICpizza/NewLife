#ifndef __TOKENIZER
#define __TOKENIZER

#include <string>
#include <istream>

enum TokenType {
	KEYWORD,
	IDENTIFIER,
	CONDITION,
	WHITESPACE,
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
		ID_KW_COND_BS,
		WHITESPACE_BS,
		COMMENT_BS,
		ERROR_BS
	};
	
	BufferState bufferState;
	
	bool tokenReady, EOFReached;

	/**
	 * Process the next input char
	 *
	 * ensures: if not at EOF:
	 * 				buffer += [next character]
	 *
	 * 				if bufferState == EMPTY_BS:
	 * 					bufferState == newBufferState(buffer)
	 * 				else:
	 * 					tokenReady == [does the new char begin the next token?]
	 * 			else:
	 * 				EOFReached == true
	 */
	void nextChar();
	
	// Given a buffer state and a string, identify the token type
	static TokenType tokenType(BufferState bufferState, const std::string& tokenText);
	
	// Choose the new buffer state for a character
	static BufferState newBufferState(const std::string& buffer);

	// alphapetic character?
	static bool isAlphaChar(char c);

	// digit character?
	static bool isDigitChar(char c);

	// whitespace character?
	static bool isWhitespaceChar(char c);

	// Is a valid identifier character?
	static bool isIdentifierChar(char c);

	// valid token start char?
	static bool canStartToken(char c);

	// Is this string (which must be valid chars) an id, keyword, or condition?
	static TokenType idKwOrCond(const std::string& tokenText);
public:
	Tokenizer(std::istream& ins);
	
	// This will copy token,
	// but return value optimization makes this OK
	Token getToken();
	Token getNonSeparatorToken();
};

#endif
