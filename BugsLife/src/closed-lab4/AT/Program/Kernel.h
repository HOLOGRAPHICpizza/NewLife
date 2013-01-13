//  /*-------------------------------------------------------------------*\
//  |   Abstract Template : Program_Kernel
//  \*-------------------------------------------------------------------*/

#ifndef AT_PROGRAM_KERNEL
#define AT_PROGRAM_KERNEL 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

/*!
    #include "AI/Statement/Kernel.h"
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
class Program_Kernel
{
public:

    /*!
        math definition IS_PRIMITIVE_INSTRUCTION (
                name: IDENTIFIER
            ): boolean is
            name is in {"move", "turnleft", "turnright", "infect", "skip"}

        math definition IS_LEGAL_USER_DEFINED_IDENTIFIER (
                name: IDENTIFIER
            ): boolean is
            name /= empty_string and
            not IS_PRIMITIVE_INSTRUCTION (name)

        math subtype CONTEXT is finite set of (
                name: IDENTIFIER
                body: STATEMENT
            )
            exemplar c
            constraint
                for all name1, name2: IDENTIFIER, body1, body2: STATEMENT
                where ((name1, body1) is in c and (name2, body2) is in c)
                    (if name1= name2 then body1 = body2) and
                for all name: IDENTIFIER, body: STATEMENT
                where ((name, body) is in c)
                    (IS_LEGAL_USER_DEFINED_IDENTIFIER (name) and
                     root (body).kind = BLOCK)

        math definition IS_DEFINED_IN (
                c: CONTEXT
                name: IDENTIFIER
            ): boolean is
            there exists body: STATEMENT
                ((name, body) is in c)

        math subtype PROGRAM is (
                name: IDENTIFIER
                context: CONTEXT
                body: STATEMENT
            )
            exemplar p
            constraint
                root (p.body).kind = BLOCK

        math definition IS_INITIAL_PROGRAM (
                p: PROGRAM
            ): boolean is
            p.name = empty_string and
            p.context = empty_set and
            IS_INITIAL_STATEMENT (p.body)
    !*/

    standard_abstract_operations (Program_Kernel);
    /*!
        Program_Kernel is modeled by PROGRAM
        initialization
            ensures IS_INITIAL_PROGRAM (self)
    !*/

    procedure Swap_Name (
            alters Text& n
        ) is_abstract;
    /*!
        requires
            IS_IDENTIFIER (n)
        ensures
            self.name = #n and
            n = #self.name and
            self.context = #self.context and
            self.body = #self.body
    !*/

    procedure Swap_Body (
            alters Statement& statement
        ) is_abstract;
    /*!
        requires
            root (statement).kind = BLOCK
        ensures
            self.name = #self.name and
            self.context = #self.context and
            self.body = #statement and
            statement = #self.body
    !*/

    procedure Add_To_Context (
            consumes Text& n,
            consumes Statement& statement
        ) is_abstract;
    /*!
        requires
            IS_LEGAL_USER_DEFINED_IDENTIFIER (n) and
            not IS_DEFINED_IN (self.context, n) and
            root (statement).kind = BLOCK
        ensures
            self.name = #self.name and
            self.context = #self.context union {(#n, #statement)} and
            self.body = #self.body
    !*/

    procedure Remove_From_Context (
            preserves Text n,
            produces Text& n_copy,
            produces Statement& statement
        ) is_abstract;
    /*!
        requires
            IS_DEFINED_IN (self.context, n)
        ensures
            n_copy = n and
            self.name = #self.name and
            self.context = #self.context - {(n_copy, statement)} and
            self.body = #self.body
    !*/

    procedure Remove_Any_From_Context (
            produces Text& n,
            produces Statement& statement
        ) is_abstract;
    /*!
        requires
            self.context /= empty_set
        ensures
            self.name = #self.name and
            self.context = #self.context - {(n, statement)} and
            self.body = #self.body
    !*/

    function Boolean Is_In_Context (
            preserves Text n
        ) is_abstract;
    /*!
        ensures
            Is_In_Context = IS_DEFINED_IN (self.context, n)
    !*/

    function Integer Size_Of_Context () is_abstract;
    /*!
        ensures
            Size_Of_Context = |self.context|
    !*/

};

#endif // AT_PROGRAM_KERNEL
