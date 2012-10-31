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

		case EMPTY_BS:
		case ERROR_BS:
			return ERROR;
			break;
		
		case EOF_BS:
			return EOF_TOKEN;
			break;
	}
}

void Tokenizer::nextChar() {
	char c;
	ins.get(c);
	buffer.push_back(c);
	
	// Have we reached EOF?
	if(ins.good()) {
		bufferState = COMMENT_BS;
		//debug << '"' << buffer << "\"\n";
	}
	else
	{
		//debug << "EOF" << '\n';
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
	return t;
}
	
Token Tokenizer::getNonSeparatorToken() {
	return getToken();
}

