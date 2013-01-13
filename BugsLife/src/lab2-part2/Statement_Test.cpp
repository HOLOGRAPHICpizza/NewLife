//  /*--------------------------------------------------------------------*\
//  |   Main Program: Simple tester for Statement
//  |*--------------------------------------------------------------------*|
//  |   Date:    17 October 1999    
//  |   Author:  Paolo Bucci
//  |   
//  |   Brief User's Manual:
//  |   Allows user to test a Statement implementation,
//  |   interactively or in batch mode.
//  |   
//  \*--------------------------------------------------------------------*/


///---------------------------------------------------------------------
/// Global Context -----------------------------------------------------
///---------------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "CT/Statement/Kernel_1.h"
#include "CT/Statement/Kernel_C.h"
#include "CT/Statement/Pretty_Print_1.h"
#include "CT/Tree/Kernel_1a_C.h"
#include "CT/Array/Kernel_1_C.h"

///---------------------------------------------------------------------
/// Local Context ------------------------------------------------------
///---------------------------------------------------------------------

concrete_instance
class Tree_Node :
    instantiates
        Record < 
                Integer,
                Integer,
                Text
            >
{};

//----------------------------------------------------------------------

concrete_instance
class Tree_Of_Tree_Node :
    instantiates
        Tree_Kernel_1a_C <
                Tree_Node
            >
{};

//----------------------------------------------------------------------

concrete_instance
class Statement_Base :
    instantiates
        Statement_Kernel_1 <
                Statement_Base,
                Tree_Node,
                Tree_Of_Tree_Node
            >
{};

//----------------------------------------------------------------------

concrete_instance
class Statement_Checking :
    instantiates
        Statement_Kernel_C <
                Statement_Checking,
                Statement_Base
            >
{};

//----------------------------------------------------------------------

concrete_instance
class Statement :
    instantiates
        Statement_Pretty_Print_1 <
                Statement_Checking
            >
{};

//----------------------------------------------------------------------

concrete_instance
class Array_Of_Statement :
    instantiates
        Array_Kernel_1_C <
                Statement
            >
{};

///---------------------------------------------------------------------
/// Interface ----------------------------------------------------------
///---------------------------------------------------------------------

// Program control objects

object Boolean interactive;
object Text command_line;
object Character command_code;
object Character_IStream ins;
object Character_OStream outs;

// Test objects

object Array_Of_Statement statements;

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operations (omitted for brevity)

//----------------------------------------------------------------------
//----------------------------------------------------------------------

// Global operation bodies

procedure_body Determine_Interactive_Mode ()
{
    outs << "Run in interactive mode (y/n)? ";
    ins >> command_line;
    command_code = command_line[0];
    interactive = (command_code == 'y');
}

//------------------------------------------------------------------------

procedure_body Get_Command ()
{
    if (interactive)
    {
        // Show menu of commands:
        // Concept-specific operations
        
        outs << "\n\nCommand: s [Swap]\n"
             << "         p [Pretty_Print]\n"
             << "         a [Add_To_Block]\n"
             << "         r [Remove_From_Block]\n"
             << "         l [Length_Of_Block]\n"
             << "         i [Compose_If]\n"
             << "         I [Decompose_If]\n"
             << "         e [Compose_If_Else]\n"
             << "         E [Decompose_If_Else]\n"
             << "         w [Compose_While]\n"
             << "         W [Decompose_While]\n"
             << "         c [Compose_Call]\n"
             << "         C [Decompose_Call]\n"
             << "         k [Kind]\n"

        // Tester control operations
        
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

//------------------------------------------------------------------------

function_body Integer Get_Condition ()
{
    object Integer cond;

    if (interactive)
    {
        outs << "  ... operator value, enter\n";
        outs << "          a ... for NEXT_IS_EMPTY\n";
        outs << "          b ... for NEXT_IS_NOT_EMPTY\n";
        outs << "          c ... for NEXT_IS_WALL\n";
        outs << "          d ... for NEXT_IS_NOT_WALL\n";
        outs << "          e ... for NEXT_IS_FRIEND\n";
        outs << "          f ... for NEXT_IS_NOT_FRIEND\n";
        outs << "          g ... for NEXT_IS_ENEMY\n";
        outs << "          h ... for NEXT_IS_NOT_ENEMY\n";
        outs << "          i ... for RANDOM\n";
        outs << "          j ... for TRUE\n";
        outs << "      ? ";
    }

    ins >> command_line;
    if (command_line.Length () > 0)
    {
        command_code = command_line[0];
        case_select (command_code)
        {
            case 'a':
            {
                cond = NEXT_IS_EMPTY;
            }
            break;
            case 'b':
            {
                cond = NEXT_IS_NOT_EMPTY;
            }
            break;
            case 'c':
            {
                cond = NEXT_IS_WALL;
            }
            break;
            case 'd':
            {
                cond = NEXT_IS_NOT_WALL;
            }
            break;
            case 'e':
            {
                cond = NEXT_IS_FRIEND;
            }
            break;
            case 'f':
            {
                cond = NEXT_IS_NOT_FRIEND;
            }
            break;
            case 'g':
            {
                cond = NEXT_IS_ENEMY;
            }
            break;
            case 'h':
            {
                cond = NEXT_IS_NOT_ENEMY;
            }
            break;
            case 'i':
            {
                cond = RANDOM;
            }
            break;
            case 'j':
            {
                cond = TRUE;
            }
            break;
            default:
            {
                cond = -1;
            }
            break;
        }
    }
    else
    {
        cond = -1;
    }

    return cond;
}

//------------------------------------------------------------------------

procedure_body Print_Condition (preserves Integer cond)
{
    case_select (cond)
    {
        case NEXT_IS_EMPTY:
        {
            outs << "NEXT_IS_EMPTY";
        }
        break;

        case NEXT_IS_NOT_EMPTY:
        {
            outs << "NEXT_IS_NOT_EMPTY";
        }
        break;

        case NEXT_IS_WALL:
        {
            outs << "NEXT_IS_WALL";
        }
        break;

        case NEXT_IS_NOT_WALL:
        {
            outs << "NEXT_IS_NOT_WALL";
        }
        break;

        case NEXT_IS_FRIEND:
        {
            outs << "NEXT_IS_FRIEND";
        }
        break;

        case NEXT_IS_NOT_FRIEND:
        {
            outs << "NEXT_IS_NOT_FRIEND";
        }
        break;

        case NEXT_IS_ENEMY:
        {
            outs << "NEXT_IS_ENEMY";
        }
        break;

        case NEXT_IS_NOT_ENEMY:
        {
            outs << "NEXT_IS_NOT_ENEMY";
        }
        break;

        case RANDOM:
        {
            outs << "RANDOM";
        }
        break;

        case TRUE:
        {
            outs << "TRUE";
        }
        break;

        default:
        {
            outs << "*** Invalid condition ***";
        }
        break;
    }    
}

//------------------------------------------------------------------------

procedure_body Do_Swap ()
{
    object Integer id1, id2;
    object Statement temp;  // to avoid repeated argument

    if (interactive)
    {
        outs << "Swap which object? ";
    }
    ins >> id1;
    if (interactive)
    {
        outs << "  ... with which object? ";
    }
    ins >> id2;
    outs << "\n--------------------------------------------"
         << "\n                   |";
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << " &= statements" << id2 << ";          |";
    temp &= statements[id1];
    temp &= statements[id2];
    temp &= statements[id1];
    outs << "\n--------------------------------------------"
         << "\n                   |";
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Pretty_Print ()
{
    object Integer id, indentation_factor;

    if (interactive)
    {
        outs << "Pretty_Print which object? ";
    }
    ins >> id;

    if (interactive)
    {
        outs << "  ... indentation factor (>= 0)? ";
    }
    ins >> indentation_factor;
    
    outs << "\n--------------------------------------------"
         << "\nstatements" << id << " = \n";
    statements[id].Pretty_Print (outs, indentation_factor);
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Add_To_Block ()
{
    object Integer id1, id2;
    object Integer pos;

    if (interactive)
    {
        outs << "Add to which object? ";
    }
    ins >> id1;
    if (interactive)
    {
        outs << "  ... position? ";
    }
    ins >> pos;
    
    if (interactive)
    {
        outs << "  ... object? ";
    }
    ins >> id2;

    outs << "\n--------------------------------------------"
         << "\n                   |  position = " << pos;
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << ".Add_To_Block (position, statements"
         << id2 << ");  |";
    statements[id1].Add_To_Block (pos, statements[id2]);
    outs << "\n--------------------------------------------"
         << "\n                   |  position = " << pos;
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Remove_From_Block ()
{
    object Integer id1, id2;
    object Integer pos;

    if (interactive)
    {
        outs << "Remove from which object? ";
    }
    ins >> id1;

    if (interactive)
    {
        outs << "  ... position? ";
    }
    ins >> pos;
    
    if (interactive)
    {
        outs << "  ... object? ";
    }
    ins >> id2;
    outs << "\n--------------------------------------------"
         << "\n                   |  position = ? ";
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << ".Remove_From_Block (position, statements"
         << id2 << ");  |";
    statements[id1].Remove_From_Block (pos, statements[id2]);
    outs << "\n--------------------------------------------"
         << "\n                   |  position = " << pos;
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Length_Of_Block ()
{
    object Integer id, k;

    if (interactive)
    {
        outs << "Length of block for which object? ";
    }
    ins >> id;
    outs << "\n--------------------------------------------"
         << "\n                   |  length = ?";
    outs << "\n--------------------------------------------"
         << "\nlength = statements" << id << ".Length_Of_Block ();    |";
    k = statements[id].Length_Of_Block ();
    outs << "\n--------------------------------------------"
         << "\n                   |  length = " << k;
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Compose_If ()
{
    object Integer id1, id2;
    object Integer cond;

    if (interactive)
    {
        outs << "Compose into which object? ";
    }
    ins >> id1;

    cond = Get_Condition ();
    
    if (interactive)
    {
        outs << "  ... body object? ";
    }
    ins >> id2;

    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ";
    Print_Condition (cond);
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << ".Compose_If (cond, statements" << id2
         << ");  |";
    statements[id1].Compose_If (cond, statements[id2]);
    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ";
    Print_Condition (cond);
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Decompose_If ()
{
    object Integer id1, id2;
    object Integer cond;

    if (interactive)
    {
        outs << "Decompose from which object? ";
    }
    ins >> id1;

    if (interactive)
    {
        outs << "  ... body object? ";
    }
    ins >> id2;
    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ? ";
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << ".Decompose_If (condition, statements"
         << id2 << ");  |";
    statements[id1].Decompose_If (cond, statements[id2]);
    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ";
    Print_Condition (cond);
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Compose_If_Else ()
{
    object Integer id1, id2, id3;
    object Integer cond;

    if (interactive)
    {
        outs << "Compose into which object? ";
    }
    ins >> id1;

    cond = Get_Condition ();
    
    if (interactive)
    {
        outs << "  ... if body object? ";
    }
    ins >> id2;
    if (interactive)
    {
        outs << "  ... else body object? ";
    }
    ins >> id3;

    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ";
    Print_Condition (cond);
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << ".Compose_If_Else (cond, statements"
         << id2 << ", statements" << id3 << ");  |";
    statements[id1].Compose_If_Else (cond, statements[id2], statements[id3]);
    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ";
    Print_Condition (cond);
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Decompose_If_Else ()
{
    object Integer id1, id2, id3;
    object Integer cond;

    if (interactive)
    {
        outs << "Decompose from which object? ";
    }
    ins >> id1;

    if (interactive)
    {
        outs << "  ... if body object? ";
    }
    ins >> id2;
    if (interactive)
    {
        outs << "  ... else body object? ";
    }
    ins >> id3;
    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ? ";
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << ".Decompose_If_Else (condition, statements"
         << id2 << ", statements" << id3 << ");  |";
    statements[id1].Decompose_If_Else (cond, statements[id2], statements[id3]);
    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ";
    Print_Condition (cond);
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Compose_While ()
{
    object Integer id1, id2;
    object Integer cond;

    if (interactive)
    {
        outs << "Compose into which object? ";
    }
    ins >> id1;

    cond = Get_Condition ();
    
    if (interactive)
    {
        outs << "  ... body object? ";
    }
    ins >> id2;

    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ";
    Print_Condition (cond);
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << ".Compose_While (cond, statements" << id2
         << ");  |";
    statements[id1].Compose_While (cond, statements[id2]);
    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ";
    Print_Condition (cond);
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Decompose_While ()
{
    object Integer id1, id2;
    object Integer cond;

    if (interactive)
    {
        outs << "Decompose from which object? ";
    }
    ins >> id1;

    if (interactive)
    {
        outs << "  ... body object? ";
    }
    ins >> id2;
    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ? ";
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << ".Decompose_While (condition, statements"
         << id2 << ");  |";
    statements[id1].Decompose_While (cond, statements[id2]);
    outs << "\n--------------------------------------------"
         << "\n                   |  condition = ";
    Print_Condition (cond);
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Compose_Call ()
{
    object Integer id1;
    object Text inst;

    if (interactive)
    {
        outs << "Compose into which object? ";
    }
    ins >> id1;
    if (interactive)
    {
        outs << "  ... instruction? ";
    }
    ins >> inst;
    
    outs << "\n--------------------------------------------"
         << "\n                   |  instruction = " << inst;
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << ".Compose_Call (" << inst << ");  |";
    statements[id1].Compose_Call (inst);
    outs << "\n--------------------------------------------"
         << "\n                   |  instruction = " << inst;
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Decompose_Call ()
{
    object Integer id1;
    object Text inst;

    if (interactive)
    {
        outs << "Decompose from which object? ";
    }
    ins >> id1;

    outs << "\n--------------------------------------------"
         << "\n                   |  instruction = ? ";
    outs << "\n--------------------------------------------"
         << "\nstatements" << id1 << ".Decompose_Call ("
         << inst << ");  |";
    statements[id1].Decompose_Call (inst);
    outs << "\n--------------------------------------------"
         << "\n                   |  instruction = " << inst;
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------

procedure_body Do_Kind ()
{
    object Integer id, k;

    if (interactive)
    {
        outs << "Kind for which object? ";
    }
    ins >> id;
    outs << "\n--------------------------------------------"
         << "\n                   |  kind = ?";
    outs << "\n--------------------------------------------"
         << "\nkind = statements" << id << ".Kind ();    |";
    k = statements[id].Kind ();
    outs << "\n--------------------------------------------"
         << "\n                   |  kind = ";
    case_select (k)
    {
        case BLOCK:
        {
            outs << "BLOCK";
        }
        break;
        case IF:
        {
            outs << "IF";
        }
        break;
        case IF_ELSE:
        {
            outs << "IF_ELSE";
        }
        break;
        case WHILE:
        {
            outs << "WHILE";
        }
        break;
        case CALL:
        {
            outs << "CALL";
        }
        break;
    }
    outs << "\n--------------------------------------------";
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

program_body main ()
{
    object Boolean finished;
    
    // Open input and output streams
    
    ins.Open_External ("");
    outs.Open_External ("");

    // Set number of test objects (= 10)

    statements.Set_Bounds (0, 9);

    // Ask user about interactive mode
    
    Determine_Interactive_Mode ();

    // Execute interactive testing loop until finished
    
    while (not finished)
    {
        // Ask user for next command
        
        Get_Command ();

        // Perform next command
        
        case_select (command_code)
        {
            // Concept-specific operations
            
            case 's':
            {
                Do_Swap ();
                break;
            }
            case 'p':
            {
                Do_Pretty_Print ();
                break;
            }
            case 'a':
            {
                Do_Add_To_Block ();
                break;
            }
            case 'r':
            {
                Do_Remove_From_Block ();
                break;
            }
            case 'l':
            {
                Do_Length_Of_Block ();
                break;
            }
            case 'i':
            {
                Do_Compose_If ();
                break;
            }
            case 'I':
            {
                Do_Decompose_If ();
                break;
            }
            case 'e':
            {
                Do_Compose_If_Else ();
                break;
            }
            case 'E':
            {
                Do_Decompose_If_Else ();
                break;
            }
            case 'w':
            {
                Do_Compose_While ();
                break;
            }
            case 'W':
            {
                Do_Decompose_While ();
                break;
            }
            case 'c':
            {
                Do_Compose_Call ();
                break;
            }
            case 'C':
            {
                Do_Decompose_Call ();
                break;
            }
            case 'k':
            {
                Do_Kind ();
                break;
            }

            // Tester control operations
                
            case 'q':
            {
                finished = true;
                break;
            }

            default:
            {
                outs << "\n" << command_line;
                break;
            }
        }
    }

    // Close input and output streams
    
    ins.Close_External ();
    outs.Close_External ();
}
