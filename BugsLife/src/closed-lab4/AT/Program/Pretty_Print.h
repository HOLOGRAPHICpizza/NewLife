//  /*-------------------------------------------------------------------*\
//  |   Abstract Template : Program_Pretty_Print
//  \*-------------------------------------------------------------------*/

#ifndef AT_PROGRAM_PRETTY_PRINT
#define AT_PROGRAM_PRETTY_PRINT 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Program/Kernel.h"
/*!
    #include "AT/Statement/Pretty_Print.h"
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
class Program_Pretty_Print :
    extends
        abstract_instance Program_Kernel <Statement>
{
public:    

    /*!
        math definition DISPLAY_INSTRUCTION (
            n: IDENTIFIER
            b: STATEMENT
            i: integer
        ): string of character is
        MAKE_A_STRING (i, ' ') * "INSTRUCTION " * n * " IS\n" *
        PRETTY_DISPLAY (b, i+4) *
        MAKE_A_STRING (i, ' ') * "END " * n * "\n"

        math definition DISPLAY_CONTEXT (
            c: CONTEXT
            i: integer
        ): string of character satisfies
        if c = empty_set
        then
            DISPLAY_CONTEXT (c, i) = empty_string
        else
            there exists name: IDENTIFIER, body: STATEMENT
                ((name, body) is in c and
                 DISPLAY_CONTEXT (c, i) =
                     DISPLAY_INSTRUCTION (name, body, i) * "\n" *
                     DISPLAY_CONTEXT (c - {(name, body)}, i))

        math definition PRETTY_DISPLAY (
            p: PROGRAM
            i: integer
        ): string of character is
        MAKE_A_STRING (i, ' ') * "PROGRAM " * p.name * " IS\n\n" *
        DISPLAY_CONTEXT (p.context, i+4) *
        MAKE_A_STRING (i, ' ') * "BEGIN\n" *
        PRETTY_DISPLAY (p.body, i+4) *
        MAKE_A_STRING (i, ' ') * "END " * p.name * "\n"
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
            out.content =
                #out.content * PRETTY_DISPLAY (self, indentation_factor)
    !*/

};

#endif // AT_PROGRAM_PRETTY_PRINT
