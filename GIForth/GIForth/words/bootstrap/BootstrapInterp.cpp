//
// Created by Dad on 9/18/19.
//
/*
: interp
0         nextToken                  // -- stringAddr
1         findWord                   // stringAddr -- [ wordAddr true | stringAddr false ]
2         if1                        // bool --
3         (7)
                                     // found the word.  Execute it
4             execute                // wordAddr --
5         else1
6         (19)
             // may be a number
7            parseNumber             // stringAddr -- [ value true | string addr false ]
8            if2                     //
9            (12)
                                     // it's a number and it's on the stack.  We're done
10            else2
11            (19)
12                printString         // stringAddr
13                (constant)
14                63
15                printChar        // '?'
16                (constant)
17                13
18                printChar        // '\n'
19            endif
19        endif
;
*/
#include "BootstrapInterp.h"
#include "BootstrapWords.h"
#include "runtime/ForthCell.h"

CompositeForthWord* BootstrapInterp::getInstance() {
    static CompositeForthWord INSTANCE;
    static bool firstTime = true;
    if (firstTime) {
        firstTime = false;
        INSTANCE << &BootstrapWords::NEXT_TOKEN;            //0
        INSTANCE << &BootstrapWords::FIND_WORD;             //1
        INSTANCE << &BootstrapWords::JUMP_IF_FALSE;         //2
        INSTANCE << static_cast<ForthCell::INT_TYPE>(7);    //3
        INSTANCE << &BootstrapWords::EXECUTE;               //4
        INSTANCE << &BootstrapWords::JUMP;                  //5
        INSTANCE << static_cast<ForthCell::INT_TYPE>(19);   //6
        INSTANCE << &BootstrapWords::PARSE_NUMBER;          //7
        INSTANCE << &BootstrapWords::JUMP_IF_FALSE;         //8
        INSTANCE << static_cast<ForthCell::INT_TYPE>(12);   //9
        INSTANCE << &BootstrapWords::JUMP;                  //10
        INSTANCE << static_cast<ForthCell::INT_TYPE>(19);   //11
        INSTANCE << &BootstrapWords::PRINT_STRING;          //12
        INSTANCE << &BootstrapWords::CONSTANT;              //13
        INSTANCE << static_cast<ForthCell::INT_TYPE>(63);  //14
        INSTANCE << &BootstrapWords::PRINT_CHAR;            //15
        INSTANCE << &BootstrapWords::CONSTANT;              //16
        INSTANCE << static_cast<ForthCell::INT_TYPE>(13);  //17
        INSTANCE << &BootstrapWords::PRINT_CHAR;            //18
    }
    return &INSTANCE;
}
