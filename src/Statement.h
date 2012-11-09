#ifndef __STATEMENT
#define __STATEMENT

#include <vector>
#include "Tokenizer.h"

enum StatementType {
	BLOCK,
	IF,
	IF_ELSE,
	WHILE,
	CALL
};

enum Condition {
	NEXT_IS_EMPTY,
	NEXT_IS_NOT_EMPTY,
	NEXT_IS_WALL,
	NEXT_IS_FRIEND,
	NEXT_IS_ENEMY,
	NEXT_IS_NOT_ENEMY,
	RANDOM,
	TRUE
};

/**
 * Default type is BLOCK, becomes BLOCK after decompose.
 */
class Statement {
private:
	StatementType type;	
	
	Condition cond;
	std::string inst;
	
	std::vector<Statement*> statements;
public:
	Statement();
	~Statement(;
	
	// pull out tokens to build a statement
	void parse(Tokenizer& tokenizer);
	
	void parseBlock(Tokenizer& tokenizer);
	
	StatementType type();
	
	void composeIf(Condition cond, Statement* body);
	void decomposeIf(Condition& cond, Statement& body;
	
	void composeCall(const std::string& inst);
	void decomposeCall(std::string& inst);
};

#endif
