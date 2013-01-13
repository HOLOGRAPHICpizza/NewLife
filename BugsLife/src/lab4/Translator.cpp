//  /*--------------------------------------------------------*\
//  |   Main Program: BL Compiler
//  |*--------------------------------------------------------*|
//  |   Date:    July 20, 1999
//  |   Author:  Paolo Bucci
//  |
//  |   Brief User's Manual:
//  |   
//  |       Compiler < input > output
//  |   
//  |
//  \*--------------------------------------------------------*/


///-------------------------------------------------------------
/// Global Context ---------------------------------------------
///-------------------------------------------------------------

#include "RESOLVE_Foundation.h"

#include "CI/Statement/Kernel_1a_C.h"
#include "CT/Statement/Parse_1.h"
#include "CT/Program/Kernel_1_C.h"
#include "CT/Program/Parse_1.h"
#include "CT/Sequence/Kernel_1a_C.h"
#include "CT/Program/Generate_Code_1.h"

///--------------------------------------------------------------
/// Local Context -----------------------------------------------
///--------------------------------------------------------------

concrete_instance
class Statement :
    instantiates
        Statement_Parse_1 <
                Statement_Kernel_1a_C
            >
{};

//---------------------------------------------------------------

concrete_instance
class Program_Base :
    instantiates
        Program_Kernel_1_C <
                Statement
            >
{};

//---------------------------------------------------------------

concrete_instance
class Program_With_Parse :
    instantiates
        Program_Parse_1 <
                Statement,
                Program_Base
            >
{};

//---------------------------------------------------------------

concrete_instance
class Compiled_Program :
    instantiates
        Sequence_Kernel_1a_C <
                Integer
            >
{};

//---------------------------------------------------------------

concrete_instance
class Program :
    instantiates
        Program_Generate_Code_1 <
                Statement,
                Program_With_Parse,
                Compiled_Program
            >
{};

///--------------------------------------------------------------
/// Interface ---------------------------------------------------
///--------------------------------------------------------------

program_body main ()
{
    object Character_IStream ins;
    object Character_OStream outs;
    object Program p;
    object Compiled_Program cp;
    object Integer pos;

    // Open input and output streams
    
    ins.Open_External ("");
    outs.Open_External ("");

    p.Parse (ins);
    p.Generate_Code (cp);

    outs << cp.Length () << '\n';
    while (pos < cp.Length ())
    {
        outs << cp[pos] << '\n';
        pos++;
    }

    // Close streams

    ins.Close_External ();
    outs.Close_External ();
}
