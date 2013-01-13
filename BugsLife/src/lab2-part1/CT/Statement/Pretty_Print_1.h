// LAB 2 - Michael Craft and Joshua Angelucci
//
//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Statement_Pretty_Print_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_STATEMENT_PRETTY_PRINT_1
#define CT_STATEMENT_PRETTY_PRINT_1 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Statement/Pretty_Print.h"
/*!
    #include "AT/Statement/Kernel.h"
!*/
   
///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

concrete_template <
        concrete_instance class Statement_Base
        /*!
            implements
                abstract_instance Statement_Kernel <Statement_Base>
        !*/
    >
class Statement_Pretty_Print_1 :
    implements
        abstract_instance Statement_Pretty_Print <Statement_Base>,
    extends
        concrete_instance Statement_Base
{
private:

    local_procedure_body Pretty_Print_Condition (
            alters Character_OStream& out,
            preserves Integer condition
        )
    /*!
        preserves self
        requires
            out.is_open = true and
            condition is in Condition
        ensures
            out.is_open = true and
            out.ext_name = #out.ext_name and
            out.content = #out.content * DISPLAY_CONDITION (condition)
    !*/
    {
	case_select (condition)
	{
	    case NEXT_IS_EMPTY:
	    {
	        out << "next-is-empty";
	    }
	    break;
	    
	    case NEXT_IS_NOT_EMPTY:
	    {
	        out << "next-is-not-empty";
	    }
	    break;
	    
	    case NEXT_IS_WALL:
	    {
	        out << "next-is-wall";
	    }
	    break;
	    
	    case NEXT_IS_NOT_WALL:
	    {
	        out << "next-is-not-wall";
	    }
	    break;
	    
	    case NEXT_IS_FRIEND:
	    {
	        out << "next-is-friend";
	    }
	    break;
	    
	    case NEXT_IS_NOT_FRIEND:
	    {
	        out << "next-is-not-friend";
	    }
	    break;
	    
	    case NEXT_IS_ENEMY:
	    {
	        out << "next-is-enemy";
	    }
	    break;
	    
	    case NEXT_IS_NOT_ENEMY:
	    {
	        out << "next-is-not-enemy";
	    }
	    break;
	    
	    case RANDOM:
	    {
	        out << "random";
	    }
	    break;
	    
	    case TRUE:
	    {
	        out << "true";
	    }
	    break;
	}
    }
    
    local_procedure_body Print_Spaces (
            alters Character_OStream& out,
            preserves Integer number_spaces
        )
    /*!
        preserves self
        requires
            number_spaces >= 0 and
            out.is_open = true
        ensures
            out.is_open = true and
            out.ext_name = #out.ext_name and
            out.content = #out.content *
                            MAKE_A_STRING (number_spaces, ' ')
    !*/
    {
	object Integer i;
	while(i < number_spaces)
	{
	    out << ' ';
	    i++;
	}   
    }

public:

    procedure_body Pretty_Print (
            alters Character_OStream& out,
            preserves Integer indentation_factor
        )
    {
        case_select (self.Kind())
	{
	   case BLOCK:
	   {
	       object catalyst Integer i;

	       // loop through the nested statements
	       while ( i < self.Length_Of_Block () )
	       {
		   object catalyst Statement_Pretty_Print_1 nested;
		   
		   // remove the nested statement at position i
		   self.Remove_From_Block ( i, nested );
		   
		   nested.Pretty_Print ( out, indentation_factor );

		   // add it back to the position it was removed from
		   self.Add_To_Block ( i, nested );  
		   
		   i++;
	       }
	   }
	   break;
	   
	   case IF:
	   {
	       object catalyst Integer cond;
	       // double check what object type to use
	       object catalyst Statement_Pretty_Print_1 block;

	       self.Decompose_If ( cond, block );

	       // output begins
	       Print_Spaces ( out, indentation_factor );
	       out << "IF ";

	       Pretty_Print_Condition ( out, cond );
	       out << " THEN\n";

	       // recursive call on the if block
	       block.Pretty_Print ( out, indentation_factor+4 );

	       Print_Spaces ( out, indentation_factor );
	       out << "END IF\n";

	       self.Compose_If ( cond, block );
	   }
	   break;

	   case IF_ELSE:
	   {
	       object catalyst Integer cond;	   
	       // double check what object type to use
	       object catalyst Statement_Pretty_Print_1 if_block, else_block;

	       self.Decompose_If_Else ( cond, if_block , else_block);

	       // output begins
	       Print_Spaces ( out, indentation_factor );
	       out << "IF ";

	       Pretty_Print_Condition ( out, cond );
	       out << " THEN\n";

	       // recursive call on the if block
	       if_block.Pretty_Print ( out, indentation_factor+4 );

	       Print_Spaces ( out, indentation_factor );
	       out << "ELSE\n";

	       // recursive call on the else block
	       else_block.Pretty_Print ( out, indentation_factor+4 );

	       Print_Spaces ( out, indentation_factor );
	       out << "END IF\n";

	       self.Compose_If ( cond, if_block );
	   }
	   break;

	   case WHILE:
	   {
	       object catalyst Integer cond;
	       // double check what object type to use
	       object catalyst Statement_Pretty_Print_1 block;

	       self.Decompose_While ( cond, block );

	       // output begins
	       Print_Spaces ( out, indentation_factor );
	       out << "WHILE ";

	       Pretty_Print_Condition ( out, cond );
	       out << " DO\n";

	       // recursive call on the if block
	       block.Pretty_Print ( out, indentation_factor+4 );

	       Print_Spaces ( out, indentation_factor );
	       out << "END WHILE\n";

	       self.Compose_While ( cond, block );
	   }
	   break;
	   
	   case CALL:
	   {
	       object catalyst Text inst;
	       
	       self.Decompose_Call ( inst );
	       
	       // output begins
	       Print_Spaces ( out, indentation_factor );
	       out << inst << "\n";

	       self.Compose_Call ( inst );
	   }
	   break;
	}
    }

};

#endif // CT_STATEMENT_PRETTY_PRINT_1
