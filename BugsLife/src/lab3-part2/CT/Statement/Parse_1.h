//  Name: Joshua Angelucci, Michael Craft
//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Statement_Parse_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_STATEMENT_PARSE_1
#define CT_STATEMENT_PARSE_1 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Statement/Parse.h"
#include "CI/BL_Tokenizing_Machine/1.h"
#include "CT/BL_Tokenizing_Machine/Get_1.h"

///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

concrete_template <
        concrete_instance class Statement_Base,
        /*!
            implements
                abstract_instance Statement_Kernel <Statement_Base>
        !*/
        concrete_instance class Tokenizing_Machine =
            BL_Tokenizing_Machine_Get_1 <
                    BL_Tokenizing_Machine_1
                >
    >
class Statement_Parse_1 :
    implements
        concrete_instance Statement_Parse <Statement_Base, Tokenizing_Machine>,
    extends
        concrete_instance Statement_Base
{
private:

    local_procedure_body Parse_IF_Statement (
            alters Character_IStream& str,
            alters Tokenizing_Machine& m,
            alters Text& token_text,
            alters Integer& token_kind,
            produces Statement_Parse_1& stmnt
        )
    /*!
	requires
	    str.is_open = true and
	    token_text = "IF" and
	    token_kind = KEYWORD and
	    m.ready_to_dispense = false
	ensures
	    if there exists x, y: string of character, s: STATEMENT 
		   (#token_text * #m.buffer * #str.content = x * y and
		    STATEMENT_TO_STRING_OF_TOKENS (s) =
			REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (x)))
	    then
		str.is_open = true and
		str.ext_name = #str.ext_name and
		there exists z: string of character 
		    (#token_text * #m.buffer * #str.content =
			 z * token_text * m.buffer * str.content and
		     STATEMENT_TO_STRING_OF_TOKENS (stmnt) =
			 REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (z)) and
		     m.ready_to_dispense = false)
    !*/
    {
	object Statement_Parse_1 if_body;
	object Text cond_text;
	object Integer cond;
	
	// condition
	debug(token_text);
	m.Get_Next_Non_Separator_Token (str, cond_text, token_kind);
	debug(cond_text);
	assert(token_kind == CONDITION, "Expected if condition."); 
	
	Parse_Condition (cond_text, cond);
	
	// THEN
	m.Get_Next_Non_Separator_Token (str, token_text, token_kind);
	assert(token_text == "THEN", "Expected \"THEN\" after if condition.");   
	
	// Parse if body
	m.Get_Next_Non_Separator_Token (str, token_text, token_kind);      
	if_body.Parse_Block (str, m, token_text, token_kind);
	
	// END or ELSE	    
	assert((token_text == "END") or (token_text == "ELSE"), "Expected END or ELSE."); 
	debug(token_text);
	
	if (token_text == "ELSE")
	{
	    object Statement_Parse_1 else_body;

	    // Parse else body
	    m.Get_Next_Non_Separator_Token (str, token_text, token_kind);
	    else_body.Parse_Block (str, m, token_text, token_kind);
	    
	    // END
	    assert(token_text == "END", "Expected \"END\" at end of else statement.");   

	    stmnt.Compose_If_Else (cond, if_body, else_body);
	}
	else // if END
	{
	    stmnt.Compose_If (cond, if_body);
	}
	
	// IF
	m.Get_Next_Non_Separator_Token (str, token_text, token_kind);
	assert(token_text == "IF", "Expected \"IF\" at end of if statement.");   
    }

    local_procedure_body Parse_WHILE_Statement (
            alters Character_IStream& str,
            alters Tokenizing_Machine& m,
            alters Text& token_text,
            alters Integer& token_kind,
            produces Statement_Parse_1& stmnt
        )
    /*!
	requires
	    str.is_open = true and
	    token_text = "WHILE" and
	    token_kind = KEYWORD and
	    m.ready_to_dispense = false
	ensures
	    if there exists x, y: string of character, s: STATEMENT 
		   (#token_text * #m.buffer * #str.content = x * y and
		    STATEMENT_TO_STRING_OF_TOKENS (s) =
			REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (x)))
	    then
		str.is_open = true and
		str.ext_name = #str.ext_name and
		there exists z: string of character 
		    (#token_text * #m.buffer * #str.content =
			 z * token_text * m.buffer * str.content and
		     STATEMENT_TO_STRING_OF_TOKENS (stmnt) =
			 REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (z)) and
		     m.ready_to_dispense = false)
    !*/
    {
	object Text cond_text;
	object Integer cond;
	object Statement_Parse_1 while_body;
	
	// condition
	m.Get_Next_Non_Separator_Token (str, cond_text, token_kind);
	assert(token_kind == CONDITION, "Expected while condition."); 
	
	Parse_Condition (cond_text, cond);
	debug(cond_text);
	debug(cond);
	
	// DO
	m.Get_Next_Non_Separator_Token (str, token_text, token_kind);
	assert(token_text == "DO", "Expected \"DO\" after while condition.");   
	
	// Parse while body
	m.Get_Next_Non_Separator_Token (str, token_text, token_kind);      
	while_body.Parse_Block (str, m, token_text, token_kind);
	
	// END
	assert(token_text == "END", "Expected \"END\" at end of while loop.");   
	
	// WHILE
	m.Get_Next_Non_Separator_Token (str, token_text, token_kind);
	assert(token_text == "WHILE", "Expected \"WHILE\" at end of while loop.");   
	
	stmnt.Compose_While (cond, while_body);
    }

    local_procedure_body Parse_Condition (
            preserves Text cond,
            produces Integer& value
        )
    /*!
	requires
	    IS_CONDITION_NAME (cond)
	ensures
	    cond = CONDITION_TO_TOKEN (value)
    !*/
    {	
	// assign correct enumeration for condition
	if (cond == "next-is-empty")
	{
	    value = 0;
	}
	else if (cond == "next-is-not-empty")
	{
	    value = 1;
	}
	else if (cond == "next-is-wall")
	{
	    value = 2;
	}
	else if (cond == "next-is-not-wall")
	{
	    value = 3;
	}
	else if (cond == "next-is-friend")
	{
	    value = 4;
	}
	else if (cond == "next-is-not-friend")
	{
	    value = 5;
	}
	else if (cond == "next-is-enemy")
	{
	    value = 6;
	}
	else if (cond == "next-is-not-enemy")
	{
	    value = 7;
	}
	else if (cond == "random")
	{
	    value = 8;
	}
	else // true
	{
	    value = 9;
	}		
    }

public:

    procedure_body Parse (
            alters Character_IStream& str,
            alters Tokenizing_Machine& m,
            alters Text& token_text,
            alters Integer& token_kind
        )
    {
	object Statement_Parse_1 if_block;
	object Statement_Parse_1 while_block;

	if (token_kind == IDENTIFIER)
	{
	    self.Compose_Call (token_text);
	}
        else if (token_text == "IF")
	{
	    Parse_IF_Statement (str, m, token_text, token_kind, self);
	}
	else // WHILE
	{
	    Parse_WHILE_Statement (str, m, token_text, token_kind, self);
	}	
	
	m.Get_Next_Non_Separator_Token (str, token_text, token_kind); 
    }

    procedure_body Parse_Block (
            alters Character_IStream& str,
            alters Tokenizing_Machine& m,
            alters Text& token_text,
            alters Integer& token_kind
        )
    {	
	object Statement_Parse_1 stmnt;
	object Integer i;

	debug(token_text);
	while (token_kind == IDENTIFIER or token_text == "IF" or token_text == "WHILE")
	{
	    debug(token_text);
	    assert(token_kind == IDENTIFIER or token_text == "IF" or token_text == "WHILE", "Expected identifier or IF or WHILE");
	    stmnt.Parse (str, m, token_text, token_kind);

	    self.Add_To_Block (i, stmnt);

	    i++;
	}
    }

};

#endif // CT_STATEMENT_PARSE_1
