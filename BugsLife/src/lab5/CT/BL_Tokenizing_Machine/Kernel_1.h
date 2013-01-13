// LAB 5 - Michael Craft & Joshua Angelucci
//  /*----------------------------------------------------------------------*\
//  |   Concrete Template : BL_Tokenizing_Machine_Kernel_1
//  \*----------------------------------------------------------------------*/

#ifndef CT_BL_TOKENIZING_MACHINE_KERNEL_1
#define CT_BL_TOKENIZING_MACHINE_KERNEL_1 1

///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "AI/BL_Tokenizing_Machine/Kernel.h"

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

enumeration Buffer_State
{
    EMPTY_BS,
    ID_OR_KEYWORD_OR_CONDITION_BS,
    WHITE_SPACE_BS,
    COMMENT_BS,
    ERROR_BS
};

///---------------------------------------------------------------------

concrete_template <
	concrete_instance class Rep =
	    Representation <
		    Text,
		    Integer,
		    Boolean
		>
    >
class BL_Tokenizing_Machine_Kernel_1 :
    implements
	abstract_instance BL_Tokenizing_Machine_Kernel,
    encapsulates
	concrete_instance Rep
	/*!
	    convention
                CONV (self.buffer_rep, self.buffer_state, self.token_ready)
	    correspondence
                self.buffer = self.buffer_rep and
		self.ready_to_dispense = self.token_ready
	!*/
{
private:

    rep_field_name (Rep, 0, Text, buffer_rep);
    rep_field_name (Rep, 1, Integer, buffer_state);
    rep_field_name (Rep, 2, Boolean, token_ready);

    /*!
        math definition CONV (
	        buffer: string of character
		buffer_state: integer
		token_ready: boolean
	    ): boolean is
	    token_ready =
		there exists c: character
		    (LAST_OF (buffer) = <c> and
		     IS_COMPLETE_TOKEN_TEXT
			 (ALL_BUT_LAST_OF (buffer), c)) and
	    if buffer = empty_string
	    then
		buffer_state = EMPTY_BS
	    else
		there exists str: string of character, c: character
		    ((if token_ready
		      then
			  buffer = str * <c>
		      else
			  buffer = str) and
		     (if IS_KEYWORD (str) or
			 IS_CONDITION_NAME (str) or
			 IS_IDENTIFIER (str)
		      then
			  buffer_state = ID_OR_KEYWORD_OR_CONDITION_BS
		      else if IS_WHITE_SPACE (str)
		      then
			  buffer_state = WHITE_SPACE_BS
		      else if IS_COMMENT (str)
		      then
			  buffer_state = COMMENT_BS
		      else
			  buffer_state = ERROR_BS))
    !*/

    local_procedure_body Initialize ()
    {
	self[buffer_state] = EMPTY_BS;
    }

    local_function_body Boolean Is_White_Space_Character (
	    preserves Character ch
	)
    /*!
	ensures
	    Is_White_Space_Character = (ch is in {' ', '\n', '\t'})
    !*/
    {
	return ((ch == ' ') or (ch == '\n') or (ch == '\t'));
    }

    local_function_body Boolean Is_Digit_Character (
	    preserves Character ch
	)
    /*!
	ensures
	    Is_Digit_Character = IS_DIGIT (ch)
    !*/
    {
	return (('0' <= ch) and (ch <= '9'));
    }
    
    local_function_body Boolean Is_Alphabetic_Character (
	    preserves Character ch
	)
    /*!
	ensures
	    Is_Alphabetic_Character = IS_LETTER (ch)
    !*/
    {
	return ((('A' <= ch) and (ch <= 'Z')) or
		(('a' <= ch) and (ch <= 'z')));
    }

    local_function_body Boolean Is_Identifier_Character (
	    preserves Character ch
	)
    /*!
	ensures
	    Is_Identifier_Character =
		IS_LETTER (ch) or IS_DIGIT (ch) or (ch = '-')
    !*/
    {
	return ((Is_Alphabetic_Character (ch)) or
		(Is_Digit_Character (ch)) or
		(ch == '-'));
    }

    local_function_body Boolean Can_Start_Token (
	    preserves Character ch
	)
    /*!
	ensures
	    Can_Start_Token =
		IS_LETTER (ch) or (ch is in {'#', ' ', '\n', '\t'})
    !*/
    {
	return ((Is_Alphabetic_Character (ch)) or
		(Is_White_Space_Character (ch)) or
		(ch == '#'));
    }
    
    local_function_body Integer Id_Or_Keyword_Or_Condition (
	    preserves Text t
	)
    /*!
	requires
	    IS_IDENTIFIER (t) or
	    IS_KEYWORD (t) or
	    IS_CONDITION (t)
	ensures
	    if IS_KEYWORD (t)
	    then
		Id_Or_Keyword_Or_Condition = KEYWORD
	    else if IS_CONDITION (t)
	    then
		Id_Or_Keyword_Or_Condition = CONDITION
	    else
		Id_Or_Keyword_Or_Condition = IDENTIFIER
    !*/
    {
	object Integer result;

	if ((t == "IF") or (t == "THEN") or (t == "ELSE") or (t == "END") or
	    (t == "WHILE") or (t == "DO") or (t == "INSTRUCTION") or
	    (t == "PROGRAM") or (t == "BEGIN") or (t == "IS"))
	{
	    result = KEYWORD;
	}
	else if ((t == "true") or (t == "random") or (t == "next-is-empty") or
		 (t == "next-is-not-empty") or (t == "next-is-wall") or
		 (t == "next-is-not-wall") or (t == "next-is-friend") or
		 (t == "next-is-not-friend") or (t == "next-is-enemy") or
		 (t == "next-is-not-enemy"))
	{
	    result = CONDITION;
	}
	else
	{
	    result = IDENTIFIER;
	}    

	return result;
    }

    local_function_body Integer Buffer_Type (
	    preserves Character ch
	)
    /*!
	ensures
	    if IS_LETTER (ch)
	    then
		Buffer_Type = ID_OR_KEYWORD_OR_CONDITION_BS
	    else if ch is in {' ', '\n', '\t'}
	    then
		Buffer_Type = WHITE_SPACE_BS
	    else if ch = '#'
	    then
		Buffer_Type = COMMENT_BS
	    else
		Buffer_Type = ERROR _BS
    !*/
    {
	object Integer result;

	if (Is_Alphabetic_Character (ch))
	{
	    result = ID_OR_KEYWORD_OR_CONDITION_BS;
	}
	else if (Is_White_Space_Character (ch))
	{
	    result = WHITE_SPACE_BS;
	}
	else if (ch == '#')
	{
	    result = COMMENT_BS;
	}
	else
	{
	    result = ERROR_BS;
	}

	return result;
    }

    local_function_body Integer Token_Kind (
	    preserves Integer bs,
	    preserves Text str
	)
    /*!
	requires
	    bs is in Buffer_State and
	    if bs = ID_OR_KEYWORD_OR_CONDITION_BS
	    then
		IS_IDENTIFIER (str) or
		IS_KEYWORD (str) or
		IS_CONDITION (str)
	ensures
	    if bs = EMPTY_BS or bs = ERROR_BS
	    then
		Token_Kind = ERROR
	    else if bs = WHITE_SPACE_BS
	    then
		Token_Kind = WHITE_SPACE
	    else if bs = COMMENT_BS
	    then
		Token_Kind = COMMENT
	    else
		if IS_KEYWORD (t)
		then
		    Token_Kind = KEYWORD
		else if IS_CONDITION (t)
		then
		    Token_Kind = CONDITION
		else
		    Token_Kind = IDENTIFIER
    !*/
    {
	object Integer result;

	case_select (bs)
	{
	    case EMPTY_BS:
	    case ERROR_BS:
	    {
		// buffer holding an error token
		result = ERROR;
	    }
	    break;

	    case ID_OR_KEYWORD_OR_CONDITION_BS:
	    {
		// buffer holding an identifier, keyword, or condition token:
		// determine which
		result = Id_Or_Keyword_Or_Condition (str);
	    }
	    break;

	    case WHITE_SPACE_BS:
	    {
		// buffer holding white space token
		result = WHITE_SPACE;
	    }
	    break;

	    case COMMENT_BS:
	    {
		// buffer holding comment token
		result = COMMENT;
	    }
	    break;
	}

	return result;
    }

public:

    standard_concrete_operations (BL_Tokenizing_Machine_Kernel_1);

    procedure_body Insert (
	    preserves Character ch
	)
    {
	// first add the character to the buffer
	object Character ch_copy;
	
	ch_copy = ch;
	
	self[buffer_rep].Add(self[buffer_rep].Length(), ch_copy);
	
	case_select(self[buffer_state])
	{
		case EMPTY_BS:
		{
			// since the buffer type is empty,
			// we should set it to the type of this character
			self[buffer_state] = Buffer_Type(ch);
		}
		break;
		
		case ID_OR_KEYWORD_OR_CONDITION_BS:
		{
			// if this character is not an identifer characher,
			// we have reached the end of the token
			if(not Is_Identifier_Character(ch))
			{
				self[token_ready] = true;
			}
		}
		break;
		
		case WHITE_SPACE_BS:
		{
			// if this character is not whitespace,
			// we have reached the end of the token
			if(not Is_White_Space_Character(ch))
                        {
                                self[token_ready] = true;
                        }
		}
		break;
		
		case COMMENT_BS:
		{
			// if this character is a newline,
			// we have reached the end of the token
			if(ch == '\n')
                        {
                                self[token_ready] = true;
                        }
		}
		break;

		case ERROR_BS:
		{
			// if this character is a starting character,
			// we have reached the end of the token
			if(Can_Start_Token(ch))
                        {
                                self[token_ready] = true;
                        }
		}
		break;
	}	
    }
    
    procedure_body Dispense (
	    produces Text& token_text,
	    produces Integer& token_kind
	)
    {
        object Character last;
	
	// pop off the last character
	self[buffer_rep].Remove(self[buffer_rep].Length() - 1, last);
	
	// set token_text
	token_text.Clear();
	token_text &= self[buffer_rep];
	
	// set token_kind
	token_kind = Token_Kind(self[buffer_state], token_text);
	
	// set the new buffer state
	self[buffer_state] = Buffer_Type(last);
	
	// put the characher back in the buffer
	self[buffer_rep].Add(0, last);	
	
	// done dispensing
	self[token_ready] = false;
    }

    procedure_body Flush_A_Token (
	    produces Text& token_text,
	    produces Integer& token_kind
	)
    {
	// set token_text
	token_text.Clear();
	token_text &= self[buffer_rep];
	
	// set token kind
	token_kind = Token_Kind(self[buffer_state], token_text);

	// set the buffer's state to empty
	self[buffer_state] = EMPTY_BS;
	
        // done dispensing
        self[token_ready] = false;
    }

    function_body Boolean Is_Ready_To_Dispense ()
    {
        return self[token_ready];
    }

    function_body Integer Size ()
    {
        return self[buffer_rep].Length();
    }

};

#endif // CT_BL_TOKENIZING_MACHINE_KERNEL_1
