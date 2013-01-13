//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Program_Pretty_Print_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_PROGRAM_PRETTY_PRINT_1
#define CT_PROGRAM_PRETTY_PRINT_1 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Program/Pretty_Print.h"
 
///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

concrete_template <
        concrete_instance class Statement,
        /*!
            implements
                abstract_instance Statement_Kernel <Statement>,
	    implements
	        abstract_instance Statement_Pretty_Print <Statement>
        !*/
        concrete_instance class Program_Base
        /*!
            implements
                abstract_instance Program_Kernel <Statement>
        !*/
    >
class Program_Pretty_Print_1 :
    implements
        abstract_instance Program_Pretty_Print <Statement>,
    extends
        concrete_instance Program_Base
{
private:

    local_procedure_body Print_Spaces (
	    alters Character_OStream& out,
            preserves Integer number_spaces
        )
    /*!
	requires
	    number_spaces >= 0 and
	    out.is_open = true
	ensures
	    out.is_open = true and
	    out.ext_name = #out.ext_name and
	    out.content = #out.content * MAKE_A_STRING (number_spaces, ' ')
    !*/
    {
	object Integer i;
	
	while( i < number_spaces )
	{
	    out << ' ';
	    i++;			
	}	
    }

    local_procedure_body Display_Instruction (
	    alters Character_OStream& out,
            preserves Text name,
	    preserves Statement& body,
	    preserves Integer indent
	)
    /*!
	requires
	    indent >= 0 and
	    out.is_open = true
	ensures
	    out.is_open = true and
	    out.ext_name = #out.ext_name and
	    out.content = #out.content * Display_Instruction (name, body, indent)
    !*/
    {
	Print_Spaces( out, indent );
	out << "INSTRUCTION " << name << " IS\n";
	body.Pretty_Print( out, indent+4 );
	Print_Spaces( out, indent );
	out << "END " << name << "\n";
    }
	
    local_procedure_body Display_Context (
	    alters Character_OStream& out,
            preserves Integer indent
        )
    /*!
	preserves self
	requires
	    indent >= 0 and
	    out.is_open = true
	ensures
	    out.is_open = true and
	    out.ext_name = #out.ext_name and
	    out.content = #out.content * DISPLAY_CONTEXT (self.context, indent)
    !*/
    {
	object Program_Pretty_Print_1 temp_program;
	object Text context_name, p_name;
	object Statement context_body, p_body;
	
	while ( self.Size_Of_Context() > 0 )
	{
	    self.Remove_Any_From_Context ( context_name, context_body );
	    Display_Instruction ( out, context_name, context_body, indent );
	    out << "\n";
	    temp_program.Add_To_Context ( context_name, context_body );
	}
	
	self.Swap_Name ( p_name );
	temp_program.Swap_Name ( p_name );
	
	self.Swap_Body ( p_body );
	temp_program.Swap_Body ( p_body );
	
	self &= temp_program;
    }

public:

    procedure_body Pretty_Print (
	    alters Character_OStream& out,
            preserves Integer indentation_factor
	)
    {
	object Text p_name;
	object Statement p_body;

	self.Swap_Name ( p_name );
	self.Swap_Body ( p_body );
	
	Print_Spaces ( out, indentation_factor );
	out << "PROGRAM " << p_name << " IS\n\n";
	self.Display_Context ( out, indentation_factor+4 );
	Print_Spaces ( out, indentation_factor );
	out << "BEGIN\n";
	p_body.Pretty_Print ( out, indentation_factor+4 );
	Print_Spaces ( out, indentation_factor );
	out << "END " << p_name << "\n";
	
	self.Swap_Name ( p_name );
	self.Swap_Body ( p_body );
    }

};

#endif // CT_PROGRAM_PRETTY_PRINT_1
