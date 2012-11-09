#ifndef __PROGRAM
#define __PROGRAM

#include <string>
#include <vector>
#include <istream>

enum InstructionCode {
	MOVE = 0x00,
	TURNLEFT = 0x01,
	TURNRIGHT = 0x02,
	INFECT = 0x03,
	SKIP = 0x04,
	HALT = 0x05,
	JUMP = 0x06,
	JUMP_IF_NOT_NEXT_IS_EMPTY = 0x07,
	JUMP_IF_NOT_NEXT_IS_NOT_EMPTY = 0x08,
	JUMP_IF_NOT_NEXT_IS_WALL = 0x09,
	JUMP_IF_NOT_NEXT_IS_NOT_WALL = 0x0A,
	JUMP_IF_NOT_NEXT_IS_FRIEND = 0x0B,
	JUMP_IF_NOT_NEXT_IS_NOT_FRIEND = 0x0C,
	JUMP_IF_NOT_NEXT_IS_ENEMY = 0x0D,
	JUMP_IF_NOT_NEXT_IS_NOT_ENEMY = 0x0E,
	JUMP_IF_NOT_RANDOM = 0x0F,
	JUMP_IF_NOT_TRUE = 0x10
};

class Program {
private:
	std::string name;
	
	/**
	 * list of statement refrences
	 * Statements must be created and deleted
	 */
	std::vector<Statement*> context;
	
	Statement* body;
public:
	Program();
	~Program();
	
	void parse(std::istream& ins);
	
	/**
	 * return const refrence to generated code
	 * this will be destroyed when program goes out of scope
	 */
	const std::vector<InstructionCode>& generateCode();
};

#endif
