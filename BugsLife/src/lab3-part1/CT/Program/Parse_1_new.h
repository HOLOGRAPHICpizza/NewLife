//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Program_Parse_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_PROGRAM_PARSE_1
#define CT_PROGRAM_PARSE_1 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Program/Parse.h"
#include "CI/BL_Tokenizing_Machine/1.h"
#include "CT/BL_Tokenizing_Machine/Get_1.h"
        
///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

concrete_template <
        concrete_instance class Statement,
        /*!
            implements
                abstract_instance Statement_Kernel <Statement>,
            implements
                abstract_instance Statement_Parse <
                        Statement,
                        Tokenizing_Machine
                    >
        !*/
        concrete_instance class Program_Base,
        /*!
            implements
                abstract_instance Program_Kernel <Statement>
        !*/
        concrete_instance class Tokenizing_Machine =
            BL_Tokenizing_Machine_Get_1 <
                    BL_Tokenizing_Machine_1
                >
        /*!
            implements
                abstract_instance BL_Tokenizing_Machine_Kernel,
            implements
                abstract_instance BL_Tokenizing_Machine_Get
        !*/
    >
class Program_Parse_1 :
    implements
        concrete_instance Program_Parse <Statement>,
    extends
        concrete_instance Program_Base
{
private:

    local_procedure_body Parse_Instruction_Definition (
            alters Character_IStream& str,
            alters Tokenizing_Machine& m,
            alters Text& token_text,
            alters Integer& token_kind,
            produces Text& name,
            produces Statement& body
        )
    /*!
    requires
        str.is_open = true and
        token_text = "INSTRUCTION" and
        token_kind = KEYWORD and
        m.ready_to_dispense = false
    ensures
        if there exists x, y: string of character,
                i: IDENTIFIER, s: STATEMENT 
           (#token_text * #m.buffer * #str.content = x * y and
            INSTRUCTION_TO_STRING_OF_TOKENS (i, s) =
            REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (x)))
        then
        str.is_open = true and
        str.ext_name = #str.ext_name and
        there exists z: string of character 
            (#token_text * #m.buffer * #str.content =
             z * token_text * m.buffer * str.content and
             INSTRUCTION_TO_STRING_OF_TOKENS (name, body) =
             REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (z)) and
             token_kind = WHICH_TOKEN (token_text) and
             m.ready_to_dispense = false)
    !*/
    {       
	object Text name_end;

        // name
	// check for extra possible errors, token test != other instruction in context
	m.Get_Next_Non_Separator_Token(str, name, token_kind);
	assert(token_kind == IDENTIFIER, "\"" + name + "\" is not a valid instruction name.");
    
	// IS
	m.Get_Next_Non_Separator_Token(str, token_text, token_kind);
	assert(token_text == "IS", "\"IS\" must follow instruction name.");
    
	// body
	body.Parse_Block(str, m, token_text, token_kind);
    
	// END
	m.Get_Next_Non_Separator_Token(str, token_text, token_kind);
	assert(token_text == "END", "\"END\" must follow program body.");
	
	// name again
	m.Get_Next_Non_Separator_Token(str, token_text, token_kind);
	assert(token_text == name, "Program begin and end indentifiers must match.");
    }

public:

    procedure_body Parse (
            alters Character_IStream& str
        )
    {
        object Text token_text, p_name;
	object Integer token_kind;
        object Statement p_body;
    
        // PROGRAM
        m.Get_Next_Non_Separator_Token(str, token_text, token_kind);
        assert(token_text == "PROGRAM", "Program must begin with \"PROGRAM\"");
        
	// program name
	m.Get_Next_Non_Separator_Token(str, p_name, token_kind);
	assert(token_kind == IDENTIFIER, "\"" + p_name + "\" is not a valid program name.");
	
	// IS
        m.Get_Next_Non_Separator_Token(str, token_text, token_kind);
	assert(token_text == "IS", "\"IS\" must follow program name.");
	
	// parse instructions (if any)
	m.Get_Next_Non_Separator_Token(str, token_text, token_kind); // This could be BEGIN

	while(token_text != "BEGIN") // go all the way until we hit "BEGIN"
	{
	    assert(token_text == "INSTRUCTION", "Malformed instruction definition.");
	    
	    // parse instruction and add to context
	    object Text name;
	    object Statement body;
	    Parse_Instruction_Definition(str, m, token_text, token_kind, name, body);
	    self.Add_To_Context(name, body);
	    
	    // get next token (next instruction or BEGIN)
	    m.Get_Next_Non_Separator_Token(str, token_text, token_kind);
	}
	
	// BEGIN check
	assert(token_text == "BEGIN", "Expected \"BEGIN\" keyword.");

	// parse body and add to program
	p_body.Parse_Block(str, m, token_text, token_kind);
	self.Swap_Body(p_body);
	
	// END
	m.Get_Next_Non_Separator_Token(str, token_text, token_kind);
        assert(token_text == "END", "\"END\" must follow program body.");
    
	// program name end
	m.Get_Next_Non_Separator_Token(str, token_text, token_kind);
	assert(token_text == p_name, "Program begin and end indentifiers must match.");
	
	self.Swap_Name(p_name);
    }
};

#endif // CT_PROGRAM_PARSE_1