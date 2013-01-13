//  /*-------------------------------------------------------------------*\
//  |   Abstract Template : Statement_Parse
//  \*-------------------------------------------------------------------*/

#ifndef AT_STATEMENT_PARSE
#define AT_STATEMENT_PARSE 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Statement/Kernel.h"
/*!
    #include "AI/BL_Tokenizing_Machine/Kernel.h"
!*/

///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

abstract_template <
        concrete_instance class Statement_Base,
        /*!
            implements
                abstract_instance Statement_Kernel <
                        Statement_Base
                    >
        !*/
        concrete_instance class Tokenizing_Machine
        /*!
            implements
                abstract_instance BL_Tokenizing_Machine_Type
        !*/
    >
class Statement_Parse :
    extends
        abstract_instance Statement_Base
{
public:

    /*!
        math definition CONDITION_TO_TOKEN (
                i: integer
            ): string of character satisfies
	    if i = NEXT_IS_EMPTY
	    then CONDITION_TO_TOKEN (i) = "next-is-empty"
	    else if i = NEXT_IS_NOT_EMPTY
	    then CONDITION_TO_TOKEN (i) = "next-is-not-empty"
	    else if i = NEXT_IS_WALL
	    then CONDITION_TO_TOKEN (i) = "next-is-wall"
	    else if i = NEXT_IS_NOT_WALL
	    then CONDITION_TO_TOKEN (i) = "next-is-not-wall"
	    else if i = NEXT_IS_FRIEND
	    then CONDITION_TO_TOKEN (i) = "next-is-friend"
	    else if i = NEXT_IS_NOT_FRIEND
	    then CONDITION_TO_TOKEN (i) = "next-is-not-friend"
	    else if i = NEXT_IS_ENEMY
	    then CONDITION_TO_TOKEN (i) = "next-is-enemy"
	    else if i = NEXT_IS_NOT_ENEMY
	    then CONDITION_TO_TOKEN (i) = "next-is-not-enemy"
	    else if i = RANDOM
	    then CONDITION_TO_TOKEN (i) = "random"
	    else if i = TRUE
	    then CONDITION_TO_TOKEN (i) = "true"

        math definition BLOCK_TO_STRING_OF_TOKENS (
                block: string of STATEMENT
            ): string of string of character satisfies
	    if block = empty_string
	    then
		BLOCK_TO_STRING_OF_TOKENS (block) = empty_string
	    else
		there exists s: STATEMENT, rest: string of STATEMENT
		    (block = <s> * rest and
		     BLOCK_TO_STRING_OF_TOKENS (block) =
			 STATEMENT_TO_STRING_OF_TOKENS (s) *
			 BLOCK_TO_STRING_OF_TOKENS (rest))

        math definition STATEMENT_TO_STRING_OF_TOKENS (
                s: STATEMENT
            ): string of string of character satisfies
	    there exists label: STATEMENT_LABEL,
			 nested_stmts: string of STATEMENT
		(s = compose (label, nested_stmts) and
		 if label.kind = BLOCK
		 then
		     STATEMENT_TO_STRING_OF_TOKENS (s) =
			 BLOCK_TO_STRING_OF_TOKENS (nested_stmts)
		 else if label.kind = IF
		 then
		     STATEMENT_TO_STRING_OF_TOKENS (s) =
			 <"IF"> * <CONDITION_TO_TOKEN (label.test)> *
			 <"THEN"> *
			 STATEMENT_TO_STRING_OF_TOKENS (
						    first (nested_stmts)) *
			 <"END"> * <"IF">
		 else if label.kind = IF_ELSE
		 then
		     STATEMENT_TO_STRING_OF_TOKENS (s) =
			 <"IF"> * <CONDITION_TO_TOKEN (label.test)> *
			 <"THEN"> *
			 STATEMENT_TO_STRING_OF_TOKENS (
						    first (nested_stmts)) *
			 <"ELSE"> *
			 STATEMENT_TO_STRING_OF_TOKENS (
						    last (nested_stmts)) *
			 <"END"> * <"IF">
		 else if label.kind = WHILE
		 then
		     STATEMENT_TO_STRING_OF_TOKENS (s) =
			 <"WHILE"> * <CONDITION_TO_TOKEN (label.test)> *
			 <"DO"> *
			 STATEMENT_TO_STRING_OF_TOKENS (
						    first (nested_stmts)) *
			 <"END"> * <"WHILE">
		 else if label.kind = CALL
		 then
		     STATEMENT_TO_STRING_OF_TOKENS (s) =
						      <label.instruction>)
    !*/

    procedure Parse (
            alters Character_IStream& str,
            alters Tokenizing_Machine& m,
            alters Text& token_text,
            alters Integer& token_kind
        ) is_abstract;
    /*!
	produces self
	requires
	    str.is_open = true and
	    token_kind = WHICH_KIND (token_text) and
	    m.ready_to_dispense = false
	ensures
	    if there exists s: STATEMENT, x, y: string of character
		(root (s).kind /= BLOCK and
		 #token_text * #m.buffer * #str.content = x * y and
		 STATEMENT_TO_STRING_OF_TOKENS (s) =
		     REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (x)))
	    then
		str.is_open = true and
		str.ext_name = #str.ext_name and
		there exists z: string of character
		    (#token_text * #m.buffer * #str.content =
			 z * token_text * m.buffer * str.content and
		     STATEMENT_TO_STRING_OF_TOKENS (self) =
			 REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (z)) and
		     root (self).kind /= BLOCK and
		     token_kind = WHICH_KIND (token_text) and
		     m.ready_to_dispense = false)
    !*/

    procedure Parse_Block (
            alters Character_IStream& str,
            alters Tokenizing_Machine& m,
            alters Text& token_text,
            alters Integer& token_kind
        ) is_abstract;
    /*!
	produces self
	requires
	    str.is_open = true and
	    token_kind = WHICH_KIND (token_text) and
	    m.ready_to_dispense = false
	ensures
	    if there exists x, y: string of character,
			    s: string of STATEMENT 
		   (#token_text * #m.buffer * #str.content = x * y and
		    BLOCK_TO_STRING_OF_TOKENS (s) =
			REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (x)))
	    then
		str.is_open = true and
		str.ext_name = #str.ext_name and
		there exists z: string of character
		    (#token_text * #m.buffer * #str.content =
			 z * token_text * m.buffer * str.content and
		     BLOCK_TO_STRING_OF_TOKENS (children (self)) =
			 REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (z)) and
		     root (self).kind = BLOCK and
		     token_text is not in {"IF", "WHILE"} and
		     not IS_IDENTIFIER (token_text) and
		     not IS_WHITE_SPACE (token_text) and
		     not IS_COMMENT (token_text) and
		     token_kind = WHICH_KIND (token_text) and
		     m.ready_to_dispense = false)
    !*/
};

#endif // AT_STATEMENT_PARSE
