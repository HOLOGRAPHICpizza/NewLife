//  /*-------------------------------------------------------------------*\
//  |   Abstract Template : Program_Parse
//  \*-------------------------------------------------------------------*/

#ifndef AT_PROGRAM_PARSE
#define AT_PROGRAM_PARSE 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Program/Kernel.h"
/*!
    #include "AT/Statement/Parse.h"
!*/

///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

abstract_template <
        concrete_instance class Statement
        /*!
            implements
                abstract_instance Statement_Kernel <Statement>
        !*/
    >
class Program_Parse :
    extends
        abstract_instance Program_Kernel <Statement>
{
public:

    /*!
        math definition INSTRUCTION_TO_STRING_OF_TOKENS (
                name: IDENTIFIER
                body: STATEMENT
            ): string of string of character is
            <"INSTRUCTION"> * <name> * <"IS"> *
            STATEMENT_TO_STRING_OF_TOKENS (body) *
            <"END"> * <name>

        math definition CONTEXT_TO_STRING_OF_TOKENS (
                c: CONTEXT
            ): string of string of character satisfies
            if c = empty_set
            then
                CONTEXT_TO_STRING_OF_TOKENS (c) = empty_string
            else
                there exists name: IDENTIFIER, body: STATEMENT
                    (CONTEXT_TO_STRING_OF_TOKENS (c) =
                         INSTRUCTION_TO_STRING_OF_TOKENS (name, body) *
                         CONTEXT_TO_STRING_OF_TOKENS (c - {(name, body)}))

        math definition PROGRAM_TO_STRING_OF_TOKENS (
                p: PROGRAM
            ): string of string of character is
            <"PROGRAM"> * <p.name> * <"IS"> *
            CONTEXT_TO_STRING_OF_TOKENS (p.context) *
            <"BEGIN"> * STATEMENT_TO_STRING_OF_TOKENS (p.body) *
            <"END"> * <p.name>

        math definition IS_AN_INPUT_REP (
                s: string of character
                p: PROGRAM
            ): boolean is
            PROGRAM_TO_STRING_OF_TOKENS (p) =
                REMOVE_SEPARATORS (TOKENIZE_PROGRAM_TEXT (s))
    !*/

    procedure Parse (
            alters Character_IStream& str
        ) is_abstract;
    /*!
        produces self
        requires
            str.is_open = true
        ensures
            if there exists p: PROGRAM, s, t: string of character
                   (#str.content = s * t and
                    IS_AN_INPUT_REP (s, p))
            then
                str.is_open = true and
                str.ext_name = #str.ext_name and
                there exists u: string of character
                    (#str.content = u * str.content and
                     IS_AN_INPUT_REP (u, self))
    !*/

};

#endif // AT_PROGRAM_PARSE
