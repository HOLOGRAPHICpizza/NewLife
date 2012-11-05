#include "Tokenizer.h"
#include "debug.h"

// The constructor initializer list initializes the ins refrence
Tokenizer::Tokenizer(std::istream& inputStream) : ins(inputStream) {
	tokenReady = false;
	bufferState = EMPTY_BS;
}

TokenType Tokenizer::tokenType(
	BufferState bufferState, 
	const std::string& tokenText)
{
	switch(bufferState) {
		case COMMENT_BS:
			return COMMENT;
			break;

		case EOF_BS:
			return EOF_TOKEN;
			break;

		case EMPTY_BS:
		case ERROR_BS:
		default:
			return ERROR;
			break;
	}
}

Tokenizer::BufferState Tokenizer::newBufferState(char c) {
	return ID_KW_COND_BS;
}

bool Tokenizer::isIdKwCondChar(char c) {
	return true;
}

void Tokenizer::nextChar() {
	char c;
	ins.get(c);
	buffer.push_back(c);
	
	// Have we reached EOF?
	if(ins.good()) {
		switch(bufferState) {
			case EMPTY_BS:
				// identify which new buffer type to assume
				bufferState = newBufferState(c);
				break;
			
			case ID_KW_COND_BS:
			default:
				if(!isIdKwCondChar(c))
					tokenReady = true;
				break;
		}
	}
	else
	{
		if(buffer.length() > 0) {
			tokenReady = true;
		}
		else
		{
			bufferState = EOF_BS;
		}
	}
}

Token Tokenizer::getToken() {
	// get characters until the token is ready
	while(not tokenReady) {
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
	} while(token.type == WHITESPACE);
	
	return token;
}

