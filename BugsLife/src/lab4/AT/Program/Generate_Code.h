//  /*-------------------------------------------------------------------*\
//  |   Abstract Template : Program_Generate_Code
//  \*-------------------------------------------------------------------*/

#ifndef AT_PROGRAM_GENERATE_CODE
#define AT_PROGRAM_GENERATE_CODE 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Program/Kernel.h"
/*!
    #include "AT/Sequence/Kernel.h"
!*/

///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

enumeration Instruction_Codes
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

abstract_template <
        concrete_instance class Statement,
        /*!
            implements
                abstract_instance Statement_Kernel <Statement>
        !*/
        concrete_instance class Compiled_Program
        /*!
            implements
                abstract_instance Sequence_Kernel <Integer>
        !*/
    >
class Program_Generate_Code :
    extends
        abstract_instance Program_Kernel <Statement>
{
public:
    
    /*!
        math definition CALLS_INSTRUCTION (
                s: STATEMENT
                n: IDENTIFIER
            ): boolean satisfies
            there exists x: STATEMENT_LABEL
                (x = root (s) and
                 if x.kind = CALL
                 then
                     CALLS_INSTRUCTION (s, n) =
                         (n = x.instruction)
                 else
                     CALLS_INSTRUCTION (s, n) =
                         there exists y: STATEMENT
                         where (y is in elements (children (s)))
                             (CALLS_INSTRUCTION (y, n)))

        math subtype NEW_INSTRUCTION is (
                name: IDENTIFIER
                body: STATEMENT
            )

        math definition HAS_A_CALLING_CYCLE (
                c: CONTEXT
            ): boolean is
            there exists v: NEW_INSTRUCTION, s: string of NEW_INSTRUCTION
                (for all i, j: NEW_INSTRUCTION
                         where (<i> * <j> is substring of <v> * s * <v>)
                     ({i, j} is subset of c  and
                      CALLS_INSTRUCTION (i.body, j.name)))

        math definition IS_CONSISTENT_WITH_CONTEXT (
                s: STATEMENT
                c: CONTEXT
            ): boolean satisfies
            there exists x: STATEMENT_LABEL
                (x = root (s) and
                 if x.kind = CALL
                 then
                     IS_CONSISTENT_WITH_CONTEXT (s, c) =
                         IS_PRIMITIVE_INSTRUCTION (x.instruction) or
                         IS_DEFINED_IN (c, x.instruction)
                 else
                     IS_CONSISTENT_WITH_CONTEXT (s, c) =
                         for all y: STATEMENT
                         where (y is in elements (children (s)))
                             (IS_CONSISTENT_WITH_CONTEXT (y, c)))

        math definition IS_CONSISTENT (
                p: PROGRAM
            ): boolean satisfies
            IS_CONSISTENT_WITH_CONTEXT (p.body, p.context)  and
            for all ni: NEW_INSTRUCTION
                    where (ni is in p.context)
                (IS_CONSISTENT_WITH_CONTEXT (ni.body, p.context))  and
            not HAS_A_CALLING_CYCLE (p.context)

        math definition GENERATE_CODE (
                p: PROGRAM
            ): string of integer satisfies
            if IS_CONSISTENT (p)
            then
                GENERATE_CODE (p) =
                    GENERATE_CODE_FOR_BLOCK (
                        0, children (p.body), p.context) * <HALT>
            else
                GENERATE_CODE (p) = empty_string

        math definition GENERATE_CODE_FOR_BLOCK (
                start: integer
                body: string of STATEMENT
                context: CONTEXT
            ): string of integer satisfies
            if body = empty_string
            then
                GENERATE_CODE_FOR_BLOCK (
                    start, body, context) = empty_string
            else
                there exists s: STATEMENT, rest: string of STATEMENT
                    (body = <s> * rest and
                     GENERATE_CODE_FOR_BLOCK (start, body, context) =
                         GENERATE_CODE_FOR_STATEMENT (start, s, context) *
                         GENERATE_CODE_FOR_BLOCK (
                             start + |GENERATE_CODE_FOR_STATEMENT (
                                          start, s, context)|,
                             rest, context))

        math definition GENERATE_CODE_FOR_STATEMENT (
                start: integer
                stmt: STATEMENT
                context: CONTEXT
            ): string of integer satisfies
            there exists x: STATEMENT_LABEL
                (x = root (stmt) and
                 if x.kind = BLOCK
                 then
                     GENERATE_CODE_FOR_STATEMENT (start, stmt, context) =
                         GENERATE_CODE_FOR_BLOCK (
                             start, children (stmt), context)
                 else if x.kind = IF
                 then
                     GENERATE_CODE_FOR_STATEMENT (start, stmt, context) =
                         GENERATE_CODE_FOR_IF (
                             start, x.test,
                             first (children (stmt)),
                             context)
                 else if x.kind = IF_ELSE
                 then
                     GENERATE_CODE_FOR_STATEMENT (start, stmt, context) =
                         GENERATE_CODE_FOR_IF_ELSE (
                             start, x.test,
                             first (children (stmt)),
                             last (children (stmt)), context)
                 else if x.kind = WHILE
                 then
                     GENERATE_CODE_FOR_STATEMENT (start, stmt, context) =
                         GENERATE_CODE_FOR_WHILE (
                             start, x.test,
                             first (children (stmt)),
                             context)
                 else if x.kind = CALL
                 then
                     GENERATE_CODE_FOR_STATEMENT (start, stmt, context) =
                         GENERATE_CODE_FOR_CALL (
                             start, x.instruction, context))

        math definition GENERATE_CODE_FOR_IF (
                start: integer
                test: integer
                body: STATEMENT
                context: CONTEXT
            ): string of integer satisfies
            there exists str: string of integer
                (str = GENERATE_CODE_FOR_BLOCK (
                           start + 2, children (body), context) and
                 GENERATE_CODE_FOR_IF (start, test, body, context) =
                     <GENERATE_TEST_CODE (test)> * <start + |str| + 2> *
                     str)

        math definition GENERATE_CODE_FOR_IF_ELSE (
                start: integer
                test: integer
                if_body: STATEMENT
                else_body: STATEMENT
                context: CONTEXT
            ): string of integer satisfies
            there exists str1, str2: string of integer
                (str1 = GENERATE_CODE_FOR_BLOCK (
                            start + 2, children (if_body), context) and
                 str2 = GENERATE_CODE_FOR_BLOCK (
                            start + |str1| + 4,
                            children (else_body), context) and
                 GENERATE_CODE_FOR_IF_ELSE (
                         start, test, if_body, else_body, context) =
                     <GENERATE_TEST_CODE (test)> * <start + |str1| + 4> *
                     str1 * <JUMP> * <start + |str1| + |str2| + 4> * str2)

        math definition GENERATE_CODE_FOR_WHILE (
                start: integer
                test: integer
                body: STATEMENT
                context: CONTEXT
            ): string of integer satisfies
            there exists str: string of integer
                (str = GENERATE_CODE_FOR_BLOCK (
                           start + 2, children (body), context) and
                 GENERATE_CODE_FOR_WHILE (start, test, body, context) =
                     <GENERATE_TEST_CODE (test)> * <start + |str| + 4> *
                     str * <JUMP> * <start>)

        math definition GENERATE_CODE_FOR_CALL (
                start: integer
                inst: IDENTIFIER
                context: CONTEXT
            ): string of integer satisfies
            if IS_PRIMITIVE_INSTRUCTION (inst)
            then
                GENERATE_CODE_FOR_CALL (start, inst, context) =
                    <GENERATE_INSTRUCTION_CODE (inst)>
            else
                there exists body: STATEMENT
                    ((inst, body) is in context and
                     GENERATE_CODE_FOR_CALL (start, inst, context) =
                         GENERATE_CODE_FOR_BLOCK (
                               start, children (body), context))

        math definition GENERATE_INSTRUCTION_CODE (
                inst: IDENTIFIER
            ): integer satisfies
            if inst = "move"
            then
                GENERATE_INSTRUCTION_CODE (inst) = MOVE
            else if inst = "turnleft"
            then
                GENERATE_INSTRUCTION_CODE (inst) = TURNLEFT
            else if inst = "turnright"
            then
                GENERATE_INSTRUCTION_CODE (inst) = TURNRIGHT
            else if inst = "infect"
            then
                GENERATE_INSTRUCTION_CODE (inst) = INFECT
            else if inst = "skip"
            then
                GENERATE_INSTRUCTION_CODE (inst) = SKIP

        math definition GENERATE_TEST_CODE (
                test: integer
            ): integer satisfies
            if test = NEXT_IS_EMPTY
            then
                GENERATE_TEST_CODE (test) = JUMP_IF_NOT_NEXT_IS_EMPTY
            else if test = NEXT_IS_NOT_EMPTY
            then
                GENERATE_TEST_CODE (test) = JUMP_IF_NOT_NEXT_IS_NOT_EMPTY
            else if test = NEXT_IS_WALL
            then
                GENERATE_TEST_CODE (test) = JUMP_IF_NOT_NEXT_IS_WALL
            else if test = NEXT_IS_NOT_WALL
            then
                GENERATE_TEST_CODE (test) = JUMP_IF_NOT_NEXT_IS_NOT_WALL
            else if test = NEXT_IS_FRIEND
            then
                GENERATE_TEST_CODE (test) = JUMP_IF_NOT_NEXT_IS_FRIEND
            else if test = NEXT_IS_NOT_FRIEND
            then
                GENERATE_TEST_CODE (test) = JUMP_IF_NOT_NEXT_IS_NOT_FRIEND
            else if test = NEXT_IS_ENEMY
            then
                GENERATE_TEST_CODE (test) = JUMP_IF_NOT_NEXT_IS_ENEMY
            else if test = NEXT_IS_NOT_ENEMY
            then
                GENERATE_TEST_CODE (test) = JUMP_IF_NOT_NEXT_IS_NOT_ENEMY
            else if test = RANDOM
            then
                GENERATE_TEST_CODE (test) = JUMP_IF_NOT_RANDOM
            else if test = TRUE
            then
                GENERATE_TEST_CODE (test) = JUMP_IF_NOT_TRUE
    !*/

    procedure Generate_Code (
            produces Compiled_Program& cp
        ) is_abstract;
    /*!
        preserves self
        ensures
            if IS_CONSISTENT (self)
            then
                cp = GENERATE_CODE (self)
    !*/

};

#endif // AT_PROGRAM_GENERATE_CODE
