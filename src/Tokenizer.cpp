#include "Tokenizer.h"
#include "debug.h"

// The constructor initializer list initializes the ins reference
Tokenizer::Tokenizer(std::istream& inputStream) :
		ins(inputStream) {
	tokenReady = false;
	bufferState = EMPTY_BS;
}

TokenType Tokenizer::idKwOrCond(const std::string& t) {
	TokenType result;

	if ((t == "IF") or (t == "THEN") or (t == "ELSE") or (t == "END")
			or (t == "WHILE") or (t == "DO") or (t == "INSTRUCTION")
			or (t == "PROGRAM") or (t == "BEGIN") or (t == "IS")) {
		result = KEYWORD;
	}

	else if ((t == "true") or (t == "random") or (t == "next-is-empty")
			or (t == "next-is-not-empty") or (t == "next-is-wall")
			or (t == "next-is-not-wall") or (t == "next-is-friend")
			or (t == "next-is-not-friend") or (t == "next-is-enemy")
			or (t == "next-is-not-enemy")) {
		result = CONDITION;
	}

	else {
		result = IDENTIFIER;
	}

	return result;
}

TokenType Tokenizer::tokenType(BufferState bufferState,
		const std::string& tokenText) {
	TokenType ret;

	switch (bufferState) {

	case EMPTY_BS:
	case ERROR_BS:
		ret = ERROR;
		break;

	case ID_KW_COND_BS:
		ret = idKwOrCond(tokenText);
		break;

	case WHITESPACE_BS:
		ret = WHITESPACE;
		break;

	case COMMENT_BS:
		ret = COMMENT;
		break;

	case EOF_BS:
		ret = EOF_TOKEN;
		break;
	}

	return ret;
}

bool Tokenizer::isAlphaChar(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Tokenizer::isDigitChar(char c) {
	return c >= '0' && c <= '9';
}

bool Tokenizer::isWhitespaceChar(char c) {
	return c == ' ' || c == '\n' || c == '\t';
}

bool Tokenizer::isIdentifierChar(char c) {
	return isAlphaChar(c) || isDigitChar(c) || c == '-';
}

bool Tokenizer::canStartToken(char c) {
	return isAlphaChar(c) || isWhitespaceChar(c) || c == '#';
}

Tokenizer::BufferState Tokenizer::newBufferState(char c) {
	// alphabetic character?
	if(isAlphaChar(c)) {
		return ID_KW_COND_BS;
	}

	// whitespace?
	else if(isWhitespaceChar(c)) {
		return WHITESPACE_BS;
	}

	// comment?
	else if(c == '#') {
		return COMMENT_BS;
	}

	// other crap
	else {
		return ERROR_BS;
	}
}

void Tokenizer::nextChar() {
	char c;
	ins.get(c);
	buffer.push_back(c);

	// Have we not reached EOF?
	if (ins.good()) {
		switch (bufferState) {

		case EMPTY_BS:
			// identify which new buffer type to assume
			bufferState = newBufferState(c);
			break;

		case ID_KW_COND_BS:
			// if this is not an identifier char we have reached token end
			if(!isIdentifierChar(c))
				tokenReady = true;
			break;

		case WHITESPACE_BS:
			// if this is not whitespace we have reached end
			if(!isWhitespaceChar(c))
				tokenReady = true;
			break;

		case COMMENT_BS:
			// if this is newline we have reached end
			if(c == '\n')
				tokenReady = true;
			break;

		case ERROR_BS:
			// if this is a valid starting char, end token
			if(canStartToken(c))
				tokenReady = true;
			break;

		case EOF_BS:
			tokenReady = true;
			break;
		}
	} else {
		if (buffer.length() > 0) {
			tokenReady = true;
		} else {
			bufferState = EOF_BS;
		}
	}
}

Token Tokenizer::getToken() {
	// get characters until the token is ready
	while (not tokenReady) {
		nextChar();
	}

	// The token is now all but the last char of buffer
	Token t;
	t.text = buffer.substr(0, buffer.length() - 1);
	t.type = tokenType(bufferState, t.text);

	// Set the new buffer and buffer state
	buffer = buffer.substr(buffer.length() - 1);
	bufferState = newBufferState(buffer[0]);

	return t;
}

Token Tokenizer::getNonSeparatorToken() {
	Token token;
	do {
		token = getToken();
	} while (token.type == WHITESPACE);

	return token;
}

