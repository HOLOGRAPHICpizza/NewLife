#include "Statement.h"

Statement::Statement() {
	type = BLOCK;
	statements = std::vector<Statement*>();
}

void Statement::parse(Tokenizer& tokenizer) {
	//
}
	
void Statement::parseBlock(Tokenizer& tokenizer) {
	//
}
	
StatementType Statement::type() {
	return type;
}
	
void Statement::composeIf(Condition cond, Statement* body) {
	type = IF;
	this.cond = cond;
	statements.push_back(body);
}

void Statement::decomposeIf(Condition& cond, Statement& body) {
	type = BLOCK;
	cond = this.cond;
	body = *statements[0];
	statements.pop_back;
}
	
void Statement::composeCall(const std::string& inst) {
	type = CALL;
	this.inst = inst;
}

void Statement::decomposeCall(std::string& inst) {
	type = BLOCK;
	inst = this.inst;
}


