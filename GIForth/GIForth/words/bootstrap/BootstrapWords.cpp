//
// Created by Dad on 9/18/19.
//

#include "BootstrapWords.h"
#include <array>
#include "utils/NativeOSFunctions.hpp"
#include "runtime/ForthThread.h"

PrimativeForthWordFunction BootstrapWords::NEXT_TOKEN(&BootstrapWords::F_NEXT_TOKEN);
void BootstrapWords::F_NEXT_TOKEN(ForthThread& thread) {
    static constexpr int MAX_TOKEN_SIZE = 80;
    static std::array<char, MAX_TOKEN_SIZE> token;

    int ndx = 0;
    char c;

    // skip leading whitespace
    do {
        c = NativeOSFunctions::nextChar();
    } while (c <= ' ');

    //suck up non-whitespace
    do {
        token[ndx++] = c;
        c = NativeOSFunctions::nextChar();
    } while ((c > ' ') && (ndx < MAX_TOKEN_SIZE - 2));
    // -2 above for last char of a too long token and null terminator
    if (ndx == MAX_TOKEN_SIZE) {
        // if max length reached, add last character to token
        token[ndx++] = c;
    }

    // terminate string with null character
    token[ndx] = '\0';

    thread.pushDataStack(static_cast<ForthCell::PTR_TYPE>(token.data()));
}

PrimativeForthWordFunction BootstrapWords::FIND_WORD(&BootstrapWords::F_FIND_WORD);
void BootstrapWords::F_FIND_WORD(ForthThread& thread) {
	thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(false));
}

// stringAddr -- [ value true | stringAddr false ]
PrimativeForthWordFunction BootstrapWords::PARSE_NUMBER(&BootstrapWords::F_PARSE_NUMBER);
void BootstrapWords::F_PARSE_NUMBER(ForthThread& thread) {
    ForthCell::INT_TYPE resultValue = 0;
    char* data = static_cast<char*>(thread.popDataStack().pointer);
    int dataNdx = 0;
    while (data[dataNdx]) {
        char c = data[dataNdx++];
        if ((c < '0' || c >'9')) {
            // oops, non-numeric char
            thread.pushDataStack(static_cast<ForthCell::PTR_TYPE>(data));
            thread.pushDataStack(false);
            return;
        } else {
            resultValue = resultValue * 10 + c - '0';
        }
    }
    thread.pushDataStack(resultValue);
    thread.pushDataStack(true);
}

// stringAddr --
PrimativeForthWordFunction BootstrapWords::PRINT_STRING(&BootstrapWords::F_PRINT_STRING);
void BootstrapWords::F_PRINT_STRING(ForthThread& thread) {
    NativeOSFunctions::printString(static_cast<char*>(thread.popDataStack().pointer));
}
