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

    // stringAddr -- [ value true | string addr false ]
    static PrimativeForthWordFunction PARSE_NUMBER;

    // stringAddr --
    static PrimativeForthWordFunction PRINT_STRING;

private:
    static void F_NEXT_TOKEN(ForthThread& thread);
    static void F_FIND_WORD(ForthThread& thread);
    static void F_PARSE_NUMBER(ForthThread& thread);
    static void F_PRINT_STRING(ForthThread& thread);
};

#endif //GIFORTH_BOOTSTRAPWORDS_H
