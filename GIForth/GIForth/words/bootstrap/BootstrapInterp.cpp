//
// Created by Dad on 9/18/19.
//
/*
: interp
0       do
0         nextToken                  // -- stringAddr
1         findWord                   // stringAddr -- [ wordAddr true | stringAddr false ]
2         (jump_if_false)            // bool --
3         (7)
                                     // found the word.  Execute it
4             execute                // wordAddr --
5         (jump)
6         (19)
             // may be a number
7            parseNumber             // stringAddr -- [ value true | string addr false ]
8            (jump_if_false)
9            (12)
                                     // it's a number and it's on the stack.  We're done
10            (jump)
11            (19)
12                printString         // stringAddr
13                (push_next_cell)
14                63
15                printChar        // '?'
16                (push_next_cell)
17                13
18                printChar        // '\n'
              endif
          endif
19      (push_next_cell)
20      (false)
21      (jump_if_false)
22      (0)

;
*/
#include <words/CoreForthWords.h>
#include "words/PrimitiveForthWords.h"
#include "BootstrapInterp.h"
#include "BootstrapWords.h"
#include "runtime/ForthCell.h"
#include "CompositeForthWordBuilder.h"

CompositeForthWord* BootstrapInterp::getInstance() {
    static CompositeForthWord INSTANCE(
		    CompositeForthWordBuilder("BootstrapInterp::INSTANCE")
				    .compileRepeat()
				    .compileCell(&BootstrapWords::NEXT_TOKEN)
				    .compileCell(&BootstrapWords::FIND_WORD)
				    .compileIf()
				    .compileCell(&PrimitiveForthWords::EXECUTE)
				    .compileElse()
//                    .append(&BootstrapWords::PARSE_NUMBER)
				    .compileCell(&CoreForthWords::PARSE_NUMBER)
				    .compileCell(&PrimitiveForthWords::CONDITIONAL_NOT)
				    .compileIf()
				    .compileCell(&BootstrapWords::PRINT_STRING)
				    .compileCell(static_cast<ForthCell::INT_TYPE>(63))
				    .compileCell(&PrimitiveForthWords::PRINT_CHAR)
				    .compileCell(static_cast<ForthCell::INT_TYPE>(13))
				    .compileCell(&PrimitiveForthWords::PRINT_CHAR)
                    .compileEndIf()
                .compileEndIf()
            .compileForever()
            .build()
            );
/*    static CompositeForthWord INSTANCE("BootstrapInterp::INSTANCE");
    static bool firstTime = true;
    if (firstTime) {
        firstTime = false;

        INSTANCE.appendCell(&BootstrapWords::NEXT_TOKEN);            //0
        INSTANCE.appendCell(&BootstrapWords::FIND_WORD);             //1
		INSTANCE.appendCell(&PrimitiveForthWords::JUMP_IF_FALSE);         //2
        INSTANCE.appendCell(static_cast<ForthCell::INT_TYPE>(7));    //3
		INSTANCE.appendCell(&PrimitiveForthWords::EXECUTE);               //4
		INSTANCE.appendCell(&PrimitiveForthWords::JUMP);                  //5
        INSTANCE.appendCell(static_cast<ForthCell::INT_TYPE>(0));    //6
        INSTANCE.appendCell(&BootstrapWords::PARSE_NUMBER);          //7
        INSTANCE.appendCell(&PrimitiveForthWords::CONDITIONAL_NOT);       //8
		INSTANCE.appendCell(&PrimitiveForthWords::JUMP_IF_FALSE);         //9
        INSTANCE.appendCell(static_cast<ForthCell::INT_TYPE>(0));    //10
        INSTANCE.appendCell(&BootstrapWords::PRINT_STRING);          //11
		INSTANCE.appendCell(&PrimitiveForthWords::PUSH_NEXT_CELL);        //12
		INSTANCE.appendCell(static_cast<ForthCell::INT_TYPE>(63));   //13
		INSTANCE.appendCell(&PrimitiveForthWords::PRINT_CHAR);            //14
		INSTANCE.appendCell(&PrimitiveForthWords::PUSH_NEXT_CELL);        //15
		INSTANCE.appendCell(static_cast<ForthCell::INT_TYPE>(13));   //16
		INSTANCE.appendCell(&PrimitiveForthWords::PRINT_CHAR);            //17
        INSTANCE.appendCell(&PrimitiveForthWords::JUMP);                  //18
        INSTANCE.appendCell(static_cast<ForthCell::INT_TYPE>(0));    //19
    } */
    return &INSTANCE;
}
