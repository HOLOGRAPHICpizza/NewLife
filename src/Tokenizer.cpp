#include "Tokenizer.h"
#include "debug.h"

// The constructor initializer list initializes the ins reference
Tokenizer::Tokenizer(std::istream& inputStream) :
		ins(inputStream) {
	tokenReady = false;
	EOFReached = false;
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

Tokenizer::BufferState Tokenizer::newBufferState(const std::string& buffer) {
	BufferState ret;

	// alphabetic character?
	if(isAlphaChar(buffer[0])) {
		ret = ID_KW_COND_BS;
	}

	// whitespace?
	else if(isWhitespaceChar(buffer[0])) {
		ret = WHITESPACE_BS;
	}

	// comment?
	else if(buffer[0] == '#') {
		ret = COMMENT_BS;
	}

	// other crap
	else {
		ret = ERROR_BS;
	}

	return ret;
}

void Tokenizer::nextChar() {
	char c;
	ins.get(c);

	// Have we not reached EOF?
	if (ins.good()) {

		buffer.push_back(c);

		switch (bufferState) {

		case EMPTY_BS:
			// identify which new buffer type to assume
			bufferState = newBufferState(buffer);
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
		}
	} else {
		EOFReached = true;
	}
}

Token Tokenizer::getToken() {
	// get characters until the token is ready
	while (not tokenReady && not EOFReached) {
		nextChar();
	}

	Token t;

	if(EOFReached) {
		// does the buffer still have crap in it?
		if(buffer.length() > 0) {
			// swapping will set the buffer to ""
			t.text.swap(buffer);
			t.type = tokenType(bufferState, t.text);
		}
		else {
			t.type = EOF_TOKEN;
		}
	}
	else {
		// The token is now all but the last char of buffer
		t.text = buffer.substr(0, buffer.length() - 1);
		t.type = tokenType(bufferState, t.text);

		// Set the new buffer and buffer state
		buffer = std::string(1, buffer[buffer.length() - 1]);
		bufferState = newBufferState(buffer);
		tokenReady = false;
	}
	return t;
}

Token Tokenizer::getNonSeparatorToken() {
	Token token;
	do {
		token = getToken();
	} while (token.type == WHITESPACE);

	return token;
}

