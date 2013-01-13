//  /*-------------------------------------------------------------------*\
//  |   Abstract Template : Statement_Kernel
//  \*-------------------------------------------------------------------*/

#ifndef AT_STATEMENT_KERNEL
#define AT_STATEMENT_KERNEL 1

///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

enumeration Kind
{
    BLOCK,
    IF,
    IF_ELSE,
    WHILE,
    CALL
};

///------------------------------------------------------------------------

enumeration Condition
{
    NEXT_IS_EMPTY,
    NEXT_IS_NOT_EMPTY,
    NEXT_IS_WALL,
    NEXT_IS_NOT_WALL,
    NEXT_IS_FRIEND,
    NEXT_IS_NOT_FRIEND,
    NEXT_IS_ENEMY,
    NEXT_IS_NOT_ENEMY,
    RANDOM,
    TRUE
};

///------------------------------------------------------------------------

abstract_template <
        concrete_instance class Nested_Statement_Type
        /*!
            implements
                abstract_instance Statement_Kernel <
                        Nested_Statement_Type
                    >
        !*/
    >
class Statement_Kernel
{
public:

    /*!
        math definition IS_IDENTIFIER (
                i: string of character
            ): boolean is
	    i = empty_string or
	    (there exists c: character, s: string of character
		 (i = <c> * s and
		  c is in {'a'..'z', 'A'..'Z'} and
		  for all x: character where (x is in elements (s))
		      (x is in {'a'..'z', 'A'..'Z', '0'..'9', '-'})) and
	     i is not in {"PROGRAM", "IS", "INSTRUCTION", "WHILE", "DO",
			  "IF", "THEN", "ELSE", "BEGIN", "END",
			  "next-is-empty", "next-is-not-empty",
			  "next-is-wall", "next-is-not-wall",
			  "next-is-friend", "next-is-not-friend",
			  "next-is-enemy", "next-is-not-enemy",
			  "random", "true"})

        math subtype IDENTIFIER is string of character
            exemplar i
            constraint
                IS_IDENTIFIER (i)

        math definition IS_CONDITION (
                c: integer
            ): boolean is
	    c is in Condition

        math definition IS_STATEMENT_LABEL (
                kind: integer
                test: integer
                instruction: string of character
            ): boolean is
	    (kind = BLOCK and
	     test = TRUE and
	     instruction = empty_string) or
	    ((kind = IF or kind = IF_ELSE or kind = WHILE) and
	     instruction = empty_string) or
	    (kind = CALL and
	     test = TRUE and
	     instruction /= empty_string)

        math subtype STATEMENT_LABEL is (
                kind: Kind
                test: Condition
                instruction: IDENTIFIER
            )
            exemplar n
            constraint
                IS_STATEMENT_LABEL (n.kind, n.test, n.instruction)

        math subtype STATEMENT is tree of STATEMENT_LABEL
            exemplar s
            constraint
                IS_LEGAL_STATEMENT (s)

        math definition IS_LEGAL_STATEMENT (
                t: tree of STATEMENT_LABEL
            ): boolean satisfies
	    there exists label: STATEMENT_LABEL,
			 nested_stmts: string of tree of STATEMENT_LABEL
		(t = compose (label, nested_stmts) and
		 for all x: tree of STATEMENT_LABEL
		 where (x is in elements (nested_stmts))
		     (IS_LEGAL_STATEMENT (x)) and
		 if label.kind = BLOCK
		 then
		     for all x: tree of STATEMENT_LABEL
		     where (x is in elements (nested_stmts))
			 (root (x).kind /= BLOCK)
		 else if label.kind = IF or label.kind = WHILE
		 then
		     |nested_stmts| = 1 and
		     first (nested_stmts).kind = BLOCK
		 else if label.kind = IF_ELSE
		 then
		     |nested_stmts| = 2 and
		     first (nested_stmts).kind = BLOCK and
		     last (nested_stmts).kind = BLOCK
		 else if label.kind = CALL
		 then
		     |nested_stmts| = 0)

        math definition IS_INITIAL_STATEMENT (
                s: STATEMENT
            ): boolean is
            root (s).kind = BLOCK and
            children (s) = empty_string
    !*/

    standard_abstract_operations (Statement_Kernel);
    /*!
        Statement_Kernel is modeled by STATEMENT
        initialization
            ensures IS_INITIAL_STATEMENT (self)
    !*/

    procedure Add_To_Block (
	    preserves Integer pos,
	    consumes Nested_Statement_Type& statement
        ) is_abstract;
    /*!
	requires
	    root (self).kind = BLOCK and
	    root (statement).kind /= BLOCK and
	    0 <= pos and pos <= |children (self)|
	ensures
	    there exists x, y: string of STATEMENT
		(|x| = pos and
		 children (#self) = x * y and
		 self = compose (root (#self), x * <#statement> * y))
    !*/

    procedure Remove_From_Block (
	    preserves Integer pos,
	    produces Nested_Statement_Type& statement
        ) is_abstract;
    /*!
	requires
	    root (self).kind = BLOCK and
	    0 <= pos and pos < |children (self)|
	ensures
	    there exists x, y: string of STATEMENT
		(|x| = pos and
		 children (#self) = x * <statement> * y and
		 self = compose (root (#self), x * y))
    !*/

    function Integer Length_Of_Block () is_abstract;
    /*!
	requires
	    root (self).kind = BLOCK
	ensures
	    Length_Of_Block = |children (self)|
    !*/

    procedure Compose_If (
	    consumes Integer& cond,
	    consumes Nested_Statement_Type& block
        ) is_abstract;
    /*!
	produces self
	requires
	    IS_CONDITION (cond) and
	    root (block).kind = BLOCK
	ensures
	    self = compose ((IF, #cond, empty_string), <#block>)
    !*/

    procedure Decompose_If (
	    produces Integer& cond,
	    produces Nested_Statement_Type& block
        ) is_abstract;
    /*!
	consumes self
	requires
	    root (self).kind = IF
	ensures
	    #self = compose ((IF, cond, empty_string), <block>)
    !*/

    procedure Compose_If_Else (
	    consumes Integer& cond,
	    consumes Nested_Statement_Type& if_block,
	    consumes Nested_Statement_Type& else_block
        ) is_abstract;
    /*!
	produces self
	requires
	    IS_CONDITION (cond) and
	    root (if_block).kind = BLOCK and
	    root (else_block).kind = BLOCK
	ensures
	    self = compose ((IF_ELSE, #cond, empty_string),
			    <#if_block> * <#else_block>)
    !*/

    procedure Decompose_If_Else (
	    produces Integer& cond,
	    produces Nested_Statement_Type& if_block,
	    produces Nested_Statement_Type& else_block
        ) is_abstract;
    /*!
	consumes self
	requires
	    root (self).kind = IF_ELSE
	ensures
	    #self = compose ((IF_ELSE, cond, empty_string),
			     <if_block> * <else_block>)
    !*/

    procedure Compose_While (
	    consumes Integer& cond,
	    consumes Nested_Statement_Type& block
        ) is_abstract;
    /*!
	produces self
	requires
	    IS_CONDITION (cond) and
	    root (block).kind = BLOCK
	ensures
	    self = compose ((WHILE, #cond, empty_string), <#block>)
    !*/

    procedure Decompose_While (
	    produces Integer& cond,
	    produces Nested_Statement_Type& block
        ) is_abstract;
    /*!
	consumes self
	requires
	    root (self).kind = WHILE
	ensures
	    #self = compose ((WHILE, cond, empty_string), <block>)
    !*/

    procedure Compose_Call (
	    consumes Text& inst
        ) is_abstract;
    /*!
	produces self
	requires
	    IS_IDENTIFIER (inst) and inst /= empty_string
	ensures
	    root (self) = (CALL, TRUE, #inst) and
	    children (self) = empty_string
    !*/

    procedure Decompose_Call (
	    produces Text& inst
        ) is_abstract;
    /*!
	consumes self
	requires
	    root (self).kind = CALL
	ensures
	    #self = compose ((CALL, TRUE, inst), empty_string)
    !*/

    function Integer Kind () is_abstract;
    /*!
	ensures
	    Kind = root (self).kind
    !*/

};

#endif // AT_STATEMENT_KERNEL
