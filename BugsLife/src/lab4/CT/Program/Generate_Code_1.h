// LAB 4 - Michael Craft & Joshua Angelucci
//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Program_Generate_Code_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_PROGRAM_GENERATE_CODE_1
#define CT_PROGRAM_GENERATE_CODE_1 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Program/Generate_Code.h"
#include "CT/Sequence/Kernel_1a.h"
   
///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

concrete_template <
        concrete_instance class Statement,
        /*!
            implements
                abstract_instance Statement_Kernel <Statement>
        !*/
        concrete_instance class Program_Base,
        /*!
            implements
                abstract_instance Program_Kernel <Statement>
        !*/
        concrete_instance class Compiled_Program =
            Sequence_Kernel_1a <Integer>
        /*!
            implements
	        abstract_instance Sequence_Kernel <Integer>
        !*/
    >
class Program_Generate_Code_1 :
    implements
        abstract_instance Program_Generate_Code <
                Statement,
                Compiled_Program
            >,
    extends
        concrete_instance Program_Base
{
private:

    local_procedure_body Generate_Code_Block_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind = BLOCK
	ensures
	    if IS_CONSISTENT_WITH_CONTEXT (stmnt, p.context)  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_BLOCK (
			   |#cp|, children (stmnt), p.context)
    !*/
    {
	object Integer i;
	object Statement b_stmnt;
	
	// iterate through the block's nested statements
	while (i < stmnt.Length_Of_Block ())
	{
	    stmnt.Remove_From_Block (i, b_stmnt);
	    Generate_Code_Statement (p, cp, b_stmnt);
	    stmnt.Add_To_Block (i, b_stmnt);
	    i++;
	}
    }

    local_procedure_body Generate_Code_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind /= BLOCK
	ensures
	    if IS_CONSISTENT_WITH_CONTEXT (stmnt, p.context)  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_STATEMENT (
			   |#cp|, stmnt, p.context)
    !*/
    {
	// cannot be kind BLOCK
	case_select (stmnt.Kind ())
	{
	    case IF:
            {
		Generate_Code_If_Statement (p, cp, stmnt);
	    }
	    break;
            case IF_ELSE:
	    {
                Generate_Code_If_Else_Statement (p, cp, stmnt);
	    }
	    break;
            case WHILE:
	    {
		Generate_Code_While_Statement (p, cp, stmnt);
	    }
	    break;
            case CALL:
	    {
		Generate_Code_Call_Statement (p, cp, stmnt);
	    }
	    break;
	}
    }

    local_procedure_body Generate_Code_If_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind = IF
	ensures
	    if IS_CONSISTENT_WITH_CONTEXT (stmnt, p.context)  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_IF (
			   |#cp|, root (stmnt).test,
			   first (children (stmnt)), p.context)
    !*/
    {
	object Integer cond, jump, dummy;
	object Statement body;

	stmnt.Decompose_If (cond, body);

	Generate_Code_Test_Condition (cp, cond);

	jump = cp.Length ();
	cp.Add (jump, dummy);

	Generate_Code_Block_Statement (p, cp, body);

	cp[jump] = cp.Length ();

	stmnt.Compose_If (cond, body);
    }

    local_procedure_body Generate_Code_If_Else_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind = IF_ELSE
	ensures
	    if IS_CONSISTENT_WITH_CONTEXT (stmnt, p.context)  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_IF_ELSE (
			   |#cp|, root (stmnt).test,
			   first (children (stmnt)),
			   last (children (stmnt)), p.context)
    !*/
    {
        object Integer cond, jump1, jump2, dummy;
        object Statement if_body, else_body;

        stmnt.Decompose_If_Else(cond, if_body, else_body);

        // test condition code
        Generate_Code_Test_Condition(cp, cond);

        // placeholder for jump number to be replaced after generating body
        jump1 = cp.Length();
	cp.Add(jump1, dummy);

        // if body
        Generate_Code_Block_Statement(p, cp, if_body);

        // JUMP instruction
	dummy = JUMP;
        cp.Add(cp.Length(), dummy);

        // placeholder for second jump number
        jump2 = cp.Length();
        cp.Add(jump2, dummy);

        // first jump number
        cp[jump1] = cp.Length();

        // else body
        Generate_Code_Block_Statement(p, cp, else_body);

	// second jump number
	cp[jump2] = cp.Length();

	stmnt.Compose_If_Else(cond, if_body, else_body);
    }

    local_procedure_body Generate_Code_While_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind = WHILE
	ensures
	    if IS_CONSISTENT_WITH_CONTEXT (stmnt, p.context)  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_WHILE (
			   |#cp|, root (stmnt).test,
			   first (children (stmnt)), p.context)
    !*/
    {
        object Integer cond, jump, start, dummy;
        object Statement body;

        stmnt.Decompose_While(cond, body);
        
        // record start position
        start = cp.Length();

        // test condition code
        Generate_Code_Test_Condition(cp, cond);

        // placeholder for jump number
        jump = cp.Length();
	cp.Add(jump, dummy);

        // body
        Generate_Code_Block_Statement(p, cp, body);

        // JUMP instruction
	dummy = JUMP;
        cp.Add(cp.Length(), dummy);
	
	// start number
	cp.Add(cp.Length(), start);
	
	// jump number
	cp[jump] = cp.Length();

        stmnt.Compose_While(cond, body);
    }

    local_procedure_body Generate_Code_Call_Statement (
	    preserves Program_Generate_Code_1& p,
	    alters Compiled_Program& cp,
	    preserves Statement& stmnt
	)
    /*!
	requires
	    root (stmnt).kind = CALL
	ensures
	    if (IS_PRIMITIVE_INSTRUCTION (root (stmnt).instruction) or
		IS_DEFINED_IN (root (stmnt).instruction, p.context))  and
		not HAS_A_CALLING_CYCLE (p.context)
	    then
		cp = #cp * GENERATE_CODE_FOR_CALL (
			   |#cp|, root (stmnt).instruction,
			   p.context)
    !*/
    {
        object Text inst;

        stmnt.Decompose_Call (inst);

        if(Is_Primitive_Instruction(inst))
        {
            // simply insert the instruction code
            Generate_Code_Primitive_Statement(cp, inst);
        }
        else
        {
            object Text inst_copy;
            object Statement body;

            // does the instruction actually exist?
	    // this will catch recursion because the inst has been already removed
            assert(p.Is_In_Context(inst),
                "Expected a defined instruction without a calling cycle.");

            // insert the instruction's block

	    // this is where the inst will be removed
	    // so that the above assert will not allow recursion 
            p.Remove_From_Context(inst, inst_copy, body);

            Generate_Code_Block_Statement(p, cp, body);

            p.Add_To_Context(inst_copy, body);
        }
        
        stmnt.Compose_Call(inst);
    }

    local_procedure_body Generate_Code_Primitive_Statement (
	    alters Compiled_Program& cp,
	    preserves Text inst
	)
    /*!
	requires
	    IS_PRIMITIVE_INSTRUCTION (inst)
	ensures
	    cp = #cp * GENERATE_INSTRUCTION_CODE (inst)
    !*/
    {
        object Integer code;

        if(inst == "move")
        {
            code = MOVE;
        }
        else if(inst == "turnleft")
        {
            code = TURNLEFT;
        }
        else if(inst == "turnright")
        {
            code = TURNRIGHT;
        }
        else if(inst == "infect")
        {
            code = INFECT;
        }
        else if(inst == "skip")
        {
            code = SKIP;
        }

        cp.Add(cp.Length(), code);
    }

    local_procedure_body Generate_Code_Test_Condition (
	    alters Compiled_Program& cp,
	    preserves Integer condition
	)
    /*!
	requires
	    IS_CONDITION (condition)
	ensures
	    cp = #cp * <GENERATE_TEST_CODE (condition)>
    !*/
    {
        object Integer code;

        case_select (condition)
        {
            case NEXT_IS_EMPTY:
            {
                code = JUMP_IF_NOT_NEXT_IS_EMPTY;
            }
            break;
            case NEXT_IS_NOT_EMPTY:
            {
                code = JUMP_IF_NOT_NEXT_IS_NOT_EMPTY;
            }
            break;
            case NEXT_IS_WALL:
            {
                code = JUMP_IF_NOT_NEXT_IS_WALL;
            }
            break;
            case NEXT_IS_NOT_WALL:
            {
                code = JUMP_IF_NOT_NEXT_IS_NOT_WALL;
            }
	    break;
            case NEXT_IS_FRIEND:
            {
                code = JUMP_IF_NOT_NEXT_IS_FRIEND;
            }
            break;
            case NEXT_IS_NOT_FRIEND:
            {
                code = JUMP_IF_NOT_NEXT_IS_NOT_FRIEND;
            }
            break;
            case NEXT_IS_ENEMY:
            {
                code = JUMP_IF_NOT_NEXT_IS_ENEMY;
            }
            break;
            case NEXT_IS_NOT_ENEMY:
            {
                code = JUMP_IF_NOT_NEXT_IS_NOT_ENEMY;
            }
            break;
            case RANDOM:
            {
                code = JUMP_IF_NOT_RANDOM;
            }
            break;
            case TRUE:
            {
                code = JUMP_IF_NOT_TRUE;
            }
            break;
        }

        cp.Add (cp.Length (), code);
    }

    local_function_body Boolean Is_Primitive_Instruction (
	    preserves Text inst
	)
    /*!
	ensures
	    Is_Primitive_Instruction = IS_PRIMITIVE_INSTRUCTION (inst)
    !*/
    {
        return (inst == "move" or
            inst == "turnleft" or
            inst == "turnright" or
            inst == "infect" or
            inst == "skip");
    }

public:
    
    procedure_body Generate_Code (
	    produces Compiled_Program& cp
	)
    {
        object Statement body;
	object Integer halt;
	
	// body
	self.Swap_Body(body);
        Generate_Code_Block_Statement(self, cp, body);
	self.Swap_Body(body);
        
        // halt
	halt = HALT;

	// since cp.Add consumes the second arguement a dummy variable was created
        cp.Add(cp.Length(), halt);
    }

};

#endif // CT_PROGRAM_GENERATE_CODE_1
