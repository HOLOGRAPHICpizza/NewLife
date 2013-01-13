//  /*--------------------------------------------------------*\
//  |   Main Program: Test Driver for Closed Lab 6
//  |*--------------------------------------------------------*|
//  |   Date:    
//  |   Author:  
//  |
//  |   Brief User's Manual:
//  |   Allows the user to exercise Next_Primitive_Instruction
//  |   in either an interactive menu-driven mode or in a batch
//  |   file mode (using input redirection).
//  |
//  \*--------------------------------------------------------*/


///-------------------------------------------------------------
/// Global Context ---------------------------------------------
///-------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "CT/Array/Kernel_1.h"
#include "CI/Random/Uniform_Generator_1.h"
    
///-------------------------------------------------------------
/// Local Context ----------------------------------------------
///-------------------------------------------------------------

enumeration What_A_Bug_Can_See_In_Front_Of_It
{
    EMPTY,
    WALL, 
    FRIEND,
    ENEMY
};
    
///------------------------------------------------------------------------

enumeration Instruction_Code
{
    MOVE,
    TURNLEFT,
    TURNRIGHT,
    INFECT,
    SKIP,
    HALT,
    JUMP,
    JUMP_IF_NOT_NEXT_IS_EMPTY,
    JUMP_IF_NOT_NEXT_IS_NOT_EMPTY,
    JUMP_IF_NOT_NEXT_IS_WALL,
    JUMP_IF_NOT_NEXT_IS_NOT_WALL,
    JUMP_IF_NOT_NEXT_IS_FRIEND,
    JUMP_IF_NOT_NEXT_IS_NOT_FRIEND,
    JUMP_IF_NOT_NEXT_IS_ENEMY,
    JUMP_IF_NOT_NEXT_IS_NOT_ENEMY,
    JUMP_IF_NOT_RANDOM,
    JUMP_IF_NOT_TRUE
};

///------------------------------------------------------------------------

concrete_instance
class Compiled_Program :
    instantiates
	Array_Kernel_1 <Integer>
{};

///-------------------------------------------------------------
/// Global objects ---------------------------------------------
///-------------------------------------------------------------

object Random_Uniform_Generator_1 test_gen;
object Boolean interactive;
object Text command_line;
object Character command_code;
object Character_IStream ins;
object Character_OStream outs;

///-------------------------------------------------------------
/// Global operations ------------------------------------------
///-------------------------------------------------------------

global_function Boolean Evaluate_Jump_Condition (
	preserves Integer what_bug_sees,
	preserves Integer jump_instr
    );
/*!
    requires
	[what_bug_sees is in What_A_Bug_Can_See_In_Front_Of_It and
	 jump_instr is one of the conditional jump
	 instructions in Instruction_Code]
    ensures
	[Assume jump_instr = JUMP_IF_NOT_condition.
	 Evaluate_Jump_Condition returns true if and only if
	 condition is true given what_bug_sees.]
!*/

//--------------------------------------------------------------

global_function Boolean Is_Primitive_Instruction_Code (
	preserves Integer instr
    );
/*!
    ensures
	Is_Primitive_Instruction_Code = 
	    (instr = MOVE) or (instr = TURNLEFT) or
	    (instr = TURNRIGHT) or (instr = INFECT) or
	    (instr = SKIP) or (instr = HALT)
!*/

//--------------------------------------------------------------

global_procedure Next_Primitive_Instruction (
	preserves Compiled_Program& prog,
	preserves Integer what_bug_sees,
	alters Integer& pc,
	produces Integer& primitive_instruction
    );
/*!
    requires
	[prog is a valid BugsWorld virtual machine program and
	 what_bug_sees is in What_A_Bug_Can_See_In_Front_Of_It and
	 0 <= pc <= prog.ub]
    ensures
	[Returns in primitive_instruction the next primitive
	 instruction (MOVE, TURNLEFT, TURNRIGHT, INFECT, SKIP,
	 or HALT) that should be executed in program prog given
	 what_bug_sees and starting execution at location #pc
	 in prog. pc is the location in prog immediately after
	 the location in prog of primitive_instruction.]
!*/

//--------------------------------------------------------------

global_procedure Do_Load_Program (
        produces Compiled_Program& cp,
	produces Integer& pc
    );
/*!
    ensures
	[cp is a BL compiled program read from a user specified file] and
	pc = 0
!*/

///-------------------------------------------------------------

global_procedure Do_Next_Primitive_Instruction (
        produces Compiled_Program& cp,
	alters Integer& pc 
    );

///-------------------------------------------------------------

global_function Text Right_Align_Integer (
        preserves Integer i,
	preserves Integer w
    );

///-------------------------------------------------------------

global_procedure Do_Disassemble_Program (
        preserves Compiled_Program& cp,
	preserves Integer pc 
    );

//--------------------------------------------------------------

global_procedure Determine_Interactive_Mode ();

//--------------------------------------------------------------

global_procedure Get_Command ();

//--------------------------------------------------------------
/// Global operation bodies ------------------------------------
///-------------------------------------------------------------

function_body Boolean Evaluate_Jump_Condition (
	preserves Integer what_bug_sees,
	preserves Integer jump_instr
    )
{
    object Boolean answer;
    
    assert ((what_bug_sees == EMPTY) or
            (what_bug_sees == WALL) or
            (what_bug_sees == FRIEND) or
            (what_bug_sees == ENEMY),
            "[what_bug_sees is in What_A_Bug_Can_See_In_Front_Of_It]");

    case_select (jump_instr)
    {
        case JUMP_IF_NOT_NEXT_IS_EMPTY:
	{
	    answer = (what_bug_sees == EMPTY);
	}
	break;

        case JUMP_IF_NOT_NEXT_IS_NOT_EMPTY:
	{
	    answer = (what_bug_sees != EMPTY);
	}
	break;

        case JUMP_IF_NOT_NEXT_IS_WALL:
	{
	    answer = (what_bug_sees == WALL);
	}
	break;

        case JUMP_IF_NOT_NEXT_IS_NOT_WALL:
	{
	    answer = (what_bug_sees != WALL);
	}
	break;

        case JUMP_IF_NOT_NEXT_IS_FRIEND:
	{
	    answer = (what_bug_sees == FRIEND);
	}
	break;

        case JUMP_IF_NOT_NEXT_IS_NOT_FRIEND:
	{
	    answer = (what_bug_sees != FRIEND);
	}
	break;

        case JUMP_IF_NOT_NEXT_IS_ENEMY:
	{
	    answer = (what_bug_sees == ENEMY);
	}
	break;

        case JUMP_IF_NOT_NEXT_IS_NOT_ENEMY:
	{
	    answer = (what_bug_sees != ENEMY);
	}
	break;

        case JUMP_IF_NOT_RANDOM:
	{
	    test_gen.Generate_Next ();
	    answer = (test_gen.Uniform_Integer (0, 1) == 0);
	}
	break;

        case JUMP_IF_NOT_TRUE:
	{
	    answer = true;
	}
	break;

        default:
        {
            assert (false,
"[jump_instr is one of the conditional jump instructions in Instruction_Code]");
        }
        break;
    }

    return answer;
}

//--------------------------------------------------------------

function_body Boolean Is_Primitive_Instruction_Code (
	preserves Integer instr
    )
{
    return (instr == MOVE) or (instr == TURNLEFT) or
	   (instr == TURNRIGHT) or (instr == INFECT) or
	   (instr == SKIP) or (instr == HALT);
}

///-------------------------------------------------------------

procedure_body Next_Primitive_Instruction (
	preserves Compiled_Program& prog,
	preserves Integer what_bug_sees,
	alters Integer& pc,
	produces Integer& primitive_instruction
    )
{
    // Students to fill this in
    
    while (not Is_Primitive_Instruction_Code (prog[pc]))
    {
	// Unconditional Jump 
	if (prog[pc] == JUMP)
	{
	    // Jump
	    pc = prog[pc+1];
	}
	// Jump Condition is true
	else if (Evaluate_Jump_Condition (what_bug_sees, prog[pc]))
	{
	    // Don't Jump
	    pc += 2;
	}
	// Jump Condition is false
	else
	{
	    // Jump
	    pc = prog[pc+1];
	}
    }
    primitive_instruction = prog[pc];
    pc++;
}

///-------------------------------------------------------------

procedure_body Do_Load_Program (
        produces Compiled_Program& cp,
	produces Integer& pc
    )
{
    object Integer index, length;
    object Text filename;
    object Character_IStream pfile;

    if (interactive)
    {
	outs << "\n\nEnter Program Filename: ";
    }
    ins >> filename;

    // read compiled program

    pfile.Open_External (filename);
    
    if (interactive)
    {
	outs << "Loading " << filename << "...";
    }

    pfile >> length;
    cp.Set_Bounds (0, length-1);
    while (index < length)
    {
	pfile >> cp[index];
	index++;
    }

    if (interactive)
    {
	outs << "done!\n";
    }
    
    pfile.Close_External ();

    pc = 0;
}

///-------------------------------------------------------------

procedure_body Do_Next_Primitive_Instruction (
        produces Compiled_Program& cp,
	alters Integer& pc 
    )
{
    object Integer what_bug_sees, primitive_instruction;
    object Text str;

    if (interactive)
    {
	outs << "\n\nEnter Program Counter (Enter => pc = " << pc << "): ";
    }
    ins >> str;
    if (Can_Convert_To_Integer (str))
    {
	pc = To_Integer (str);
    }
    if (interactive)
    {
	outs << "Enter What Bug Sees (EMPTY=0, WALL=1, FRIEND=2, ENEMY=3): ";
    }
    ins >> what_bug_sees;

    // Report results of this test case

    outs << "-------------------------------------------------\n"
	 << "                      |  pc            = "  << pc << '\n'
	 << "                      |  what_bug_sees = ";
    case_select (what_bug_sees)
    {
        case EMPTY:
	{
	    outs << "EMPTY";
	}
	break;

        case WALL:
	{
	    outs << "WALL";
	}
	break;

        case FRIEND:
	{
	    outs << "FRIEND";
	}
	break;

        case ENEMY:
	{
	    outs << "ENEMY";
	}
	break;

        default:
	{
	    outs << "Invalid what_bug_sees value";
	}
	break;
    }
    outs << "\n-------------------------------------------------\n";
    Next_Primitive_Instruction (cp, what_bug_sees, pc, primitive_instruction);
    outs << "Next_Primitive_Instruction (cp, what_bug_sees, pc, primitive_instruction);|\n"
	 << "-------------------------------------------------\n"
	 << "                      |  pc                    = "  << pc << '\n'
	 << "                      |  primitive_instruction = ";
    case_select (primitive_instruction)
    {
        case MOVE:
	{
	    outs << "MOVE";
	}
	break;

        case TURNLEFT:
	{
	    outs << "TURNLEFT";
	}
	break;

        case TURNRIGHT:
	{
	    outs << "TURNRIGHT";
	}
	break;

        case INFECT:
	{
	    outs << "INFECT";
	}
	break;

        case HALT:
	{
	    outs << "HALT";
	}
	break;

        case SKIP:
	{
	    outs << "SKIP";
	}
	break;

        default:
	{
	    outs << "Invalid primitive_instruction value";
	}
	break;
    }
    outs << "\n-------------------------------------------------\n";
}

///-------------------------------------------------------------


procedure_body To_Text_With_Padding (
        preserves Integer i,
	preserves Integer w,
	produces Text& t
    )
{
    object Text tmp;

    tmp = To_Text (i);
    while (tmp.Length () < w)
    {
	tmp.Add (0, ' ');
    }
    t &= tmp;
}

///-------------------------------------------------------------

procedure_body Do_Disassemble_Program (
        preserves Compiled_Program& cp,
	preserves Integer pc 
    )
{
    object Integer pos, width = 5;
    object Text t;

    outs << "\n\n";
    while (pos <= cp.Upper_Bound ())
    {
	if (pos == pc)
	{
	    To_Text_With_Padding (pos, width - 1, t);
	    outs << "*" << t << "\t";
	}
	else
	{
	    To_Text_With_Padding (pos, width, t);
	    outs << t << "\t";
	}
	case_select (cp[pos])
	{
	    case MOVE:
	    {
		outs << "MOVE";
	    }
	    break;

	    case TURNLEFT:
	    {
		outs << "TURNLEFT";
	    }
	    break;

	    case TURNRIGHT:
	    {
		outs << "TURNRIGHT";
	    }
	    break;

	    case INFECT:
	    {
		outs << "INFECT";
	    }
	    break;

	    case HALT:
	    {
		outs << "HALT";
	    }
	    break;

	    case SKIP:
	    {
		outs << "SKIP";
	    }
	    break;

	    case JUMP:
	    {
		outs << "JUMP\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;

	    case JUMP_IF_NOT_NEXT_IS_EMPTY:
	    {
		outs << "JUMP_IF_NOT_NEXT_IS_EMPTY\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;

	    case JUMP_IF_NOT_NEXT_IS_NOT_EMPTY:
	    {
		outs << "JUMP_IF_NOT_NEXT_IS_NOT_EMPTY\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;

	    case JUMP_IF_NOT_NEXT_IS_WALL:
	    {
		outs << "JUMP_IF_NOT_NEXT_IS_WALL\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;

	    case JUMP_IF_NOT_NEXT_IS_NOT_WALL:
	    {
		outs << "JUMP_IF_NOT_NEXT_IS_NOT_WALL\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;

	    case JUMP_IF_NOT_NEXT_IS_FRIEND:
	    {
		outs << "JUMP_IF_NOT_NEXT_IS_FRIEND\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;

	    case JUMP_IF_NOT_NEXT_IS_NOT_FRIEND:
	    {
		outs << "JUMP_IF_NOT_NEXT_IS_NOT_FRIEND\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;

	    case JUMP_IF_NOT_NEXT_IS_ENEMY:
	    {
		outs << "JUMP_IF_NOT_NEXT_IS_ENEMY\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;

	    case JUMP_IF_NOT_NEXT_IS_NOT_ENEMY:
	    {
		outs << "JUMP_IF_NOT_NEXT_IS_NOT_ENEMY\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;

	    case JUMP_IF_NOT_RANDOM:
	    {
		outs << "JUMP_IF_NOT_RANDOM\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;

	    case JUMP_IF_NOT_TRUE:
	    {
		outs << "JUMP_IF_NOT_TRUE\n";
		pos++;
		To_Text_With_Padding (pos, width, t);
		outs << t << "\t" << cp[pos];
	    }
	    break;
	}
	outs << "\n";
        pos++;
    }
}

//--------------------------------------------------------------

procedure_body Determine_Interactive_Mode (  )
{
    object Text user_response;
    
    outs << "Run in interactive mode (y/n)? ";
    ins >> user_response;
    outs << "\n";
    interactive = (user_response[0] == 'y');

}

//--------------------------------------------------------------

procedure_body Get_Command ( )
{
    if (interactive)
    {
	// Show menu of commands:
	outs << "\n\nCommand: l [Load compiled program]\n"
	     << "         s [Execute a step]\n"
	     << "         d [Disassemble program]\n"
	     << "         q [Quit]: ";
    }

    // Get next command line and code
	     
    ins >> command_line;
    if (command_line.Length () > 0)
    {
	command_code = command_line[0];
    }
    else
    {
	command_code.Clear ();
    }
}

///-------------------------------------------------------------
/// Interface --------------------------------------------------
///-------------------------------------------------------------

program_body main ()
{
    object Boolean finished;
    object Integer pc;
    object Compiled_Program program;

    // Seed random number generator
    
    test_gen.Set_Value (1234);
 
    // Open input and output streams
    
    ins.Open_External ("");
    outs.Open_External ("");

    // Ask user about interactive mode

    Determine_Interactive_Mode ( );

    // Execute interactive testing loop until finished

    while (not finished)
    {
        // Ask user for next command

	Get_Command ();

	case_select (command_code)
	{
	    case 'l':
	    {
		Do_Load_Program (program, pc);
	    }
	    break;

	    case 's':
	    {
		Do_Next_Primitive_Instruction (program, pc);
	    }
	    break;
	    
	    case 'd':
	    {
		Do_Disassemble_Program (program, pc);
	    }
	    break;

	    case 'q':
	    {
		outs << "\n*** Quitting test program\n";
                finished = true;
	    }
	    break;

	    default:
	    {
		outs << "\n" << command_line;
	    }
	    break;
	}
    }

    // Close streams

    ins.Close_External ();
    outs.Close_External ();
}
