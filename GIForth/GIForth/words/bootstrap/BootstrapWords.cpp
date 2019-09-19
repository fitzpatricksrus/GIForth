//
// Created by Dad on 9/18/19.
//

#include "BootstrapWords.h"
#include <array>
#include "utils/NativeOSFunctions.hpp"
#include "runtime/ForthThread.h"

PrimativeForthWordFunction BootstrapWords::NOP(&BootstrapWords::F_NOP);
void BootstrapWords::F_NOP(ForthThread &thread) {
}

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

}

// bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
PrimativeForthWordFunction BootstrapWords::JUMP_IF_FALSE(&BootstrapWords::F_JUMP_IF_FALSE);
void BootstrapWords::F_JUMP_IF_FALSE(ForthThread& thread) {
    int newNdx = thread.getNextCell().integer;  // consume next cell always
    if (!thread.popDataStack().boolean) {
        thread.setIndex(newNdx);
    }
}

PrimativeForthWordFunction BootstrapWords::EXECUTE(&BootstrapWords::F_EXECUTE);
void BootstrapWords::F_EXECUTE(ForthThread& thread) {
    // hey jf - will this actually work for both primitive and composite words?
    ForthWord* word = thread.popDataStack().word;
    word->execute(thread);
}

PrimativeForthWordFunction BootstrapWords::JUMP(&BootstrapWords::F_JUMP);
void BootstrapWords::F_JUMP(ForthThread& thread) {
    thread.setIndex(thread.getNextCell().integer);
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

// -- value ; pushes next cell in word onto data stack
PrimativeForthWordFunction BootstrapWords::CONSTANT(&BootstrapWords::F_CONSTANT);
void BootstrapWords::F_CONSTANT(ForthThread& thread) {
    thread.pushDataStack(thread.getNextCell());
}

// char --
PrimativeForthWordFunction BootstrapWords::PRINT_CHAR(&BootstrapWords::F_PRINT_CHAR);
void BootstrapWords::F_PRINT_CHAR(ForthThread& thread) {
    NativeOSFunctions::printChar(thread.popDataStack().character);
}
