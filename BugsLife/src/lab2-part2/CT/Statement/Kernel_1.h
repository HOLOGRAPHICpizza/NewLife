//  /*-------------------------------------------------------------------*\
//  |   Concrete Template : Statement_Kernel_1
//  \*-------------------------------------------------------------------*/

#ifndef CT_STATEMENT_KERNEL_1
#define CT_STATEMENT_KERNEL_1 1

///------------------------------------------------------------------------
/// Global Context --------------------------------------------------------
///------------------------------------------------------------------------

#include "AT/Statement/Kernel.h"
#include "CT/Tree/Kernel_1a.h"

///------------------------------------------------------------------------
/// Interface -------------------------------------------------------------
///------------------------------------------------------------------------

concrete_template <
        concrete_instance class Nested_Statement_Type,
        /*!
            implements
                abstract_instance Statement_Kernel <
                        Nested_Statement_Type
                    >
        !*/
        concrete_instance class Tree_Node =
	    Record <
		    Integer,
		    Integer,
		    Text
		>,
        concrete_instance class Tree_Of_Tree_Node =
	    Tree_Kernel_1a <Tree_Node>,
        concrete_instance class Rep =
	    Representation <
		    Tree_Of_Tree_Node
		>
    >
class Statement_Kernel_1 :
    implements
        abstract_instance Statement_Kernel <Nested_Statement_Type>,
    encapsulates
        concrete_instance Rep
{
private:

    rep_field_name (Rep, 0, Tree_Of_Tree_Node, tree_rep);
    
    field_name (Tree_Node, 0, Integer, kind);
    field_name (Tree_Node, 1, Integer, test);
    field_name (Tree_Node, 2, Text, instruction);

    /*!
        math definition IS_LEGAL_LABEL (
                k: integer
                t: integer
                i: string of character
            ): boolean is
	    k is in Kind and
	    t is in Condition and
	    IS_IDENTIFIER (i) and
	    IS_STATEMENT_LABEL (k, t, i)

        math definition ALL_LABELS_ARE_LEGAL (
                t: tree of Tree_Node
            ): boolean satisfies
	    there exists label: Tree_Node,
			 subtrees: string of tree of Tree_Node
		(t = compose (label, subtrees) and
		 IS_LEGAL_LABEL (label.kind, label.test, label.instruction) and
		 for all x: tree of Tree_Node
		 where (x is in elements (subtrees))
		     (ALL_LABELS_ARE_LEGAL (x)))

	convention
	    ALL_LABELS_ARE_LEGAL (self.tree_rep) and
	    IS_LEGAL_STATEMENT (self.tree_rep)

	correspondence
	    self = self.tree_rep
    !*/

    local_procedure_body Initialize ()
    {
        // Students to fill this in
	self[tree_rep][current][kind] = BLOCK;
	self[tree_rep][current][test] = TRUE;
    }

public:

    standard_concrete_operations (Statement_Kernel_1);

    procedure_body Add_To_Block (
            preserves Integer pos,
            consumes Nested_Statement_Type& statement
        )
    {
        // Students to fill this in
	object Tree_Of_Tree_Node s;
	
        // make s a valid representation for an initial value of Statement
	s[current][kind] = BLOCK;
	s[current][test] = TRUE;
	
        // extract representation tree from statement and consume statement
	statement[tree_rep] &= s;
	
	// add the representation tree we extracted
	self[tree_rep].Add (pos, s);
    }

    procedure_body Remove_From_Block (
            preserves Integer pos,
            produces Nested_Statement_Type& statement
        )
    {
        // Students to fill this in
	self[tree_rep].Remove (pos, statement[tree_rep]);       
    }

    function_body Integer Length_Of_Block ()
    {
        // Students to fill this in
	return self[tree_rep].Number_Of_Children ();
    }

    procedure_body Compose_If (
            consumes Integer& cond,
            consumes Nested_Statement_Type& block
        )
    {
	object Tree_Of_Tree_Node new_tree_rep, t;

        // make t a valid representation for an initial value of Statement
	t[current][kind] = BLOCK;
	t[current][test] = TRUE;

        // extract representation tree from block and consume block
	block[tree_rep] &= t;

        // construct new representation tree
	new_tree_rep[current][kind] = IF;
	new_tree_rep[current][test] &= cond;
	new_tree_rep.Add (0, t);

        // produce self
	self[tree_rep] &= new_tree_rep;
    }

    procedure_body Decompose_If (
            produces Integer& cond,
            produces Nested_Statement_Type& block
        )
    {
	object Tree_Of_Tree_Node new_tree_rep;

        // make new_tree_rep valid representation for initial value of Statement
	new_tree_rep[current][kind] = BLOCK;
	new_tree_rep[current][test] = TRUE;

        // consume self
	self[tree_rep] &= new_tree_rep;

        // extract condition and body from representation of if
	new_tree_rep[current][test] &= cond;
	new_tree_rep.Remove (0, block[tree_rep]);
    }

    procedure_body Compose_If_Else (
            consumes Integer& cond,
            consumes Nested_Statement_Type& if_block,
            consumes Nested_Statement_Type& else_block
        )
    {
        // Students to fill this in
	object Tree_Of_Tree_Node new_tree_rep, if_t, else_t;

        // make if_t and else_t valid representations for an initial value of Statement
	if_t[current][kind] = BLOCK;
	if_t[current][test] = TRUE;

	else_t[current][kind] = BLOCK;
	else_t[current][kind] = TRUE;

        // extract representation tree from blocks and consume blocks
	if_block[tree_rep] &= if_t;
	else_block[tree_rep] &= else_t;

        // construct new representation tree
	new_tree_rep[current][kind] = IF_ELSE;
	new_tree_rep[current][test] &= cond;
	new_tree_rep.Add (0, if_t);
	new_tree_rep.Add (1, else_t);

        // produce self
	self[tree_rep] &= new_tree_rep;
    }

    procedure_body Decompose_If_Else (
            produces Integer& cond,
            produces Nested_Statement_Type& if_block,
            produces Nested_Statement_Type& else_block
        )
    {
        // Students to fill this in
	object Tree_Of_Tree_Node new_tree_rep;

        // make new_tree_rep valid representation for initial value of Statement
	new_tree_rep[current][kind] = BLOCK;
	new_tree_rep[current][test] = TRUE;

        // consume self
	self[tree_rep] &= new_tree_rep;

        // extract condition and body from representation of if
	new_tree_rep[current][test] &= cond;
	new_tree_rep.Remove (0, if_block[tree_rep]);
	new_tree_rep.Remove (0, else_block[tree_rep]);
    }

    procedure_body Compose_While (
            consumes Integer& cond,
            consumes Nested_Statement_Type& block
        )
    {
        // Students to fill this in
	object Tree_Of_Tree_Node new_tree_rep, t;

        // make t a valid representation for an initial value of Statement
	t[current][kind] = BLOCK;
	t[current][test] = TRUE;

        // extract representation tree from block and consume block
	block[tree_rep] &= t;

        // construct new representation tree
	new_tree_rep[current][kind] = WHILE;
	new_tree_rep[current][test] &= cond;
	new_tree_rep.Add (0, t);

        // produce self
	self[tree_rep] &= new_tree_rep;
    }

    procedure_body Decompose_While (
            produces Integer& cond,
            produces Nested_Statement_Type& block
        )
    {
        // Students to fill this in
	object Tree_Of_Tree_Node new_tree_rep;

        // make new_tree_rep valid representation for initial value of Statement
	new_tree_rep[current][kind] = BLOCK;
	new_tree_rep[current][test] = TRUE;

        // consume self
	self[tree_rep] &= new_tree_rep;

        // extract condition and body from representation of if
	new_tree_rep[current][test] &= cond;
	new_tree_rep.Remove (0, block[tree_rep]);
    }

    procedure_body Compose_Call (
            consumes Text& inst
        )
    {
        // Students to fill this in
	object Tree_Of_Tree_Node new_tree_rep;

        // construct new representation tree
	new_tree_rep[current][kind] = CALL;
	new_tree_rep[current][test] = TRUE;
	new_tree_rep[current][instruction] &= inst;

        // produce self
	self[tree_rep] &= new_tree_rep;
    }

    procedure_body Decompose_Call (
            produces Text& inst
        )
    {
        // Students to fill this in
	object Tree_Of_Tree_Node new_tree_rep;

        // make new_tree_rep valid representation for initial value of Statement
	new_tree_rep[current][kind] = BLOCK;
	new_tree_rep[current][test] = TRUE;

        // consume self
	self[tree_rep] &= new_tree_rep;

        // extract condition and body from representation of if
	new_tree_rep[current][instruction] &= inst;
    }

    function_body Integer Kind ()
    {
        // Students to fill this in
	return self[tree_rep][current][kind];
    }

};

#endif // CT_STATEMENT_KERNEL_1
