#include "Tokenizer.h"

class Tokenizer {
private:
	istream ins;
public:
	Tokenizer(istream ins) {
		this.ins = ins;
	}
	
	Token GetToken() {
		Token t;
		t.type = ERROR;
		ins >> t.text;
		return t;
	}
}

