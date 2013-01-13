//  /*--------------------------------------------------------*\
//  |   Main Program: BL Parser
//  |*--------------------------------------------------------*|
//  |   Date:    November 3, 1999
//  |   Author:  Paolo Bucci
//  |   
//  |   Modified on 30 January 2007 by Paolo Bucci
//  |   Converted to new RESOLVE/C++ discipline.
//  |
//  |   Brief User's Manual:
//  |   
//  |       Parser < input > output
//  |   
//  |
//  \*--------------------------------------------------------*/


///-------------------------------------------------------------
/// Global Context ---------------------------------------------
///-------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "CI/Statement/Kernel_1a_C.h"
#include "CT/Statement/Pretty_Print_1.h"
#include "CT/Statement/Parse_1.h"
#include "CT/Program/Kernel_1_C.h"
#include "CT/Program/Pretty_Print_1.h"
#include "CT/Program/Parse_1.h"

///---------------------------------------------------------------------
/// Local Context ------------------------------------------------------
///---------------------------------------------------------------------

concrete_instance
class Statement_Base :
    instantiates
	Statement_Pretty_Print_1 <
                Statement_Kernel_1a_C
            >
{};

//----------------------------------------------------------------------

concrete_instance
class Statement :
    instantiates
	Statement_Parse_1 <
                Statement_Base
            >
{};

//----------------------------------------------------------------------

concrete_instance
class Program_Base :
    instantiates
	Program_Kernel_1_C <
                Statement
            >
{};

//----------------------------------------------------------------------

concrete_instance
class Program_With_Pretty_Print :
    instantiates
	Program_Pretty_Print_1 <
                Statement,
                Program_Base
            >
{};

//----------------------------------------------------------------------

concrete_instance
class Program :
    instantiates
	Program_Parse_1 <
                Statement,
                Program_With_Pretty_Print
            >
{};

///----------------------------------------------------------------------
/// Interface -----------------------------------------------------------
///----------------------------------------------------------------------

program_body main ()
{
    object Character_IStream ins;
    object Character_OStream outs;
    object Program p;
    object Integer pos;

    // Open input and output streams
    
    ins.Open_External ("");
    outs.Open_External ("");

    p.Parse (ins);
    p.Pretty_Print (outs, 0);

    // Close streams

    ins.Close_External ();
    outs.Close_External ();
}
