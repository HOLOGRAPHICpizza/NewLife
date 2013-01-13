//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Program_Kernel_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_PROGRAM_KERNEL_1
#define CT_PROGRAM_KERNEL_1 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Program/Kernel.h"
#include "CI/Statement/Kernel_1a.h"
#include "CT/Partial_Map/Kernel_1.h"

///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

concrete_template <
        concrete_instance class Statement =
            Statement_Kernel_1a,
        concrete_instance class Context =
            Partial_Map_Kernel_1 <
                    Text,
                    Statement
                >,
        concrete_instance class Rep =
            Representation <
                    Text,
                    Context,
                    Statement
                >
    >
class Program_Kernel_1 :
    implements
        abstract_instance Program_Kernel <Statement>,
    encapsulates
        concrete_instance Rep
{
private:

    rep_field_name (Rep, 0, Text, name_rep);
    rep_field_name (Rep, 1, Context, context_rep);
    rep_field_name (Rep, 2, Statement, body_rep);

    /*!
	convention
            IS_IDENTIFIER (self.name_rep) and
	    root (self.body_rep).kind = BLOCK and
	    for all name: IDENTIFIER, body: STATEMENT
	    where ((name, body) is in self.context_rep)
		(IS_LEGAL_USER_DEFINED_IDENTIFIER (name) and
		 root (body).kind = BLOCK)

	correspondence
	    self = (self.name_rep, self.context_rep, self.body_rep)
    !*/

public:

    standard_concrete_operations (Program_Kernel_1);

    procedure Swap_Name (
            alters Text& n
        )
    {
	self[name_rep] &= n;
    }

    procedure Swap_Body (
            alters Statement& statement
        )
    {
	self[body_rep] &= statement;
    }

    procedure Add_To_Context (
            consumes Text& n,
            consumes Statement& statement
        )
    {
	self[context_rep].Define ( n, statement );
    }

    procedure Remove_From_Context (
            preserves Text n,
            produces Text& n_copy,
            produces Statement& statement
        )
    {   
	self[context_rep].Undefine ( n, n_copy, statement );
    }           

    procedure Remove_Any_From_Context (
            produces Text& n,
            produces Statement& statement
        )
    {
	self[context_rep].Undefine_Any ( n, statement );
    }

    function Boolean Is_In_Context (
            preserves Text n
        )
    {   
	return self[context_rep].Is_Defined ( n );
    }

    function Integer Size_Of_Context ()
    {
	return self[context_rep].Size ();
    }

};

#endif // CT_PROGRAM_KERNEL_1
