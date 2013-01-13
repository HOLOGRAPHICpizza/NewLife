//  /*-------------------------------------------------------------------*\
//  |   Abstract Template : Statement_Pretty_Print
//  \*-------------------------------------------------------------------*/

#ifndef AT_STATEMENT_PRETTY_PRINT
#define AT_STATEMENT_PRETTY_PRINT 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Statement/Kernel.h"

///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

abstract_template <
        concrete_instance class Statement_Base
        /*!
            implements
                abstract_instance Statement_Kernel <
                        Statement_Base
                    >
        !*/
    >
class Statement_Pretty_Print :
    extends
        abstract_instance Statement_Base
{
public:    

    /*!
        math definition MAKE_A_STRING (
                i: integer
                ch: character
            ): string of character satisfies
	   if i <= 0
	   then
	      MAKE_A_STRING (i, ch) = empty_string
	   else
	      MAKE_A_STRING (i, ch) = <ch> * MAKE_A_STRING (i-1, ch)

        math definition DISPLAY_CONDITION (
                i: integer
            ): string of character satisfies
	    if i = NEXT_IS_EMPTY
	    then DISPLAY_CONDITION (i) = "next-is-empty"
	    else if i = NEXT_IS_NOT_EMPTY
	    then DISPLAY_CONDITION (i) = "next-is-not-empty"
	    else if i = NEXT_IS_WALL
	    then DISPLAY_CONDITION (i) = "next-is-wall"
	    else if i = NEXT_IS_NOT_WALL
	    then DISPLAY_CONDITION (i) = "next-is-not-wall"
	    else if i = NEXT_IS_FRIEND
	    then DISPLAY_CONDITION (i) = "next-is-friend"
	    else if i = NEXT_IS_NOT_FRIEND
	    then DISPLAY_CONDITION (i) = "next-is-not-friend"
	    else if i = NEXT_IS_ENEMY
	    then DISPLAY_CONDITION (i) = "next-is-enemy"
	    else if i = NEXT_IS_NOT_ENEMY
	    then DISPLAY_CONDITION (i) = "next-is-not-enemy"
	    else if i = RANDOM
	    then DISPLAY_CONDITION (i) = "random"
	    else if i = TRUE
	    then DISPLAY_CONDITION (i) = "true"

        math definition DISPLAY_BLOCK (
                s: string of STATEMENT
                i: integer
            ): string of character satisfies
	    if s = empty_string
	    then DISPLAY_BLOCK (s, i) = empty_string
	    else
	        there exists stmt: STATEMENT,
			     rest: string of STATEMENT
		   (s = <stmt> * rest and
		    DISPLAY_BLOCK (s, i) =
		        PRETTY_DISPLAY (stmt, i) * DISPLAY_BLOCK (rest, i))
 
        math definition PRETTY_DISPLAY (
                s: STATEMENT
                i: integer
            ): string of character satisfies
	    there exists label: STATEMENT_LABEL,
			 nested_stmts: string of STATEMENT
		 (s = compose (label, nested_stmts) and
		  if label.kind = BLOCK
		  then
		      PRETTY_DISPLAY (s, i) = DISPLAY_BLOCK (nested_stmts, i)
		  else if label.kind = IF
		  then
		      PRETTY_DISPLAY (s, i) =
		       MAKE_A_STRING (i, ' ') * "IF " *
		       DISPLAY_CONDITION (label.test) * " THEN\n" *
		       PRETTY_DISPLAY (first (nested_stmts), i+4) *
		       MAKE_A_STRING (i, ' ') * "END IF\n"
		  else if label.kind = IF_ELSE
		  then
		      PRETTY_DISPLAY (s, i) =
		       MAKE_A_STRING (i, ' ') * "IF " *
		       DISPLAY_CONDITION (label.test) * " THEN\n" *
		       PRETTY_DISPLAY (first (nested_stmts), i+4) *
		       MAKE_A_STRING (i, ' ') * "ELSE\n" *
		       PRETTY_DISPLAY (last (nested_stmts), i+4) *
		       MAKE_A_STRING (i, ' ') * "END IF\n"
		  else if label.kind = WHILE
		  then
		      PRETTY_DISPLAY (s, i) =
		       MAKE_A_STRING (i, ' ') * "WHILE " *
		       DISPLAY_CONDITION (label.test) * " DO\n" *
		       PRETTY_DISPLAY (first (nested_stmts), i+4) *
		       MAKE_A_STRING (i, ' ') * "END WHILE\n"
		  else if label.kind = CALL
		  then
		      PRETTY_DISPLAY (s, i) =
		       MAKE_A_STRING (i, ' ') * label.instruction * "\n")
    !*/

    procedure Pretty_Print (
	    alters Character_OStream& out,
            preserves Integer indentation_factor
        ) is_abstract;
    /*!
	preserves self
	requires
	    out.is_open = true
	 ensures
	     out.is_open = true and
	     out.ext_name = #out.ext_name and
	     out.content = #out.content *
                           PRETTY_DISPLAY (self, indentation_factor)
    !*/
};

#endif // AT_STATEMENT_PRETTY_PRINT
