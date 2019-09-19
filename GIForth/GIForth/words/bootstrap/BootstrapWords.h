//
// Created by Dad on 9/18/19.
//

#ifndef GIFORTH_BOOTSTRAPWORDS_H
#define GIFORTH_BOOTSTRAPWORDS_H

#include <utils/PrimativeForthWordFunction.h>

class BootstrapWords {
public:
    // -- stringAddr
    static PrimativeForthWordFunction NEXT_TOKEN;

    // stringAddr -- [ wordAddr true | stringAddr false ]
    static PrimativeForthWordFunction FIND_WORD;

    // bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
    static PrimativeForthWordFunction JUMP_IF_FALSE;

    // wordAddr --
    static PrimativeForthWordFunction EXECUTE;

    // --
    static PrimativeForthWordFunction JUMP;

    // stringAddr -- [ value true | string addr false ]
    static PrimativeForthWordFunction PARSE_NUMBER;

    // stringAddr --
    static PrimativeForthWordFunction PRINT_STRING;

    // -- value ; pushes next cell in word onto data stack
    static PrimativeForthWordFunction CONSTANT;

    // char --
    static PrimativeForthWordFunction PRINT_CHAR;

private:
    static void F_NEXT_TOKEN(ForthThread& thread);
    static void F_FIND_WORD(ForthThread& thread);
    static void F_JUMP_IF_FALSE(ForthThread& thread);
    static void F_EXECUTE(ForthThread& thread);
    static void F_JUMP(ForthThread& thread);
    static void F_PARSE_NUMBER(ForthThread& thread);
    static void F_PRINT_STRING(ForthThread& thread);
    static void F_CONSTANT(ForthThread& thread);
    static void F_PRINT_CHAR(ForthThread& thread);
};

#endif //GIFORTH_BOOTSTRAPWORDS_H
