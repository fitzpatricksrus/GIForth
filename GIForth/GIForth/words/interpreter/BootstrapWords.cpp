//
// Created by Dad on 9/18/19.
//

#include "BootstrapWords.h"
#include <array>
#include <runtime/utils/CompositeForthWordBuilder.h>
#include <runtime/PrimitiveForthWords.h>
#include <words/VocabWords.h>
#include "runtime/NativeOSFunctions.hpp"
#include "runtime/ForthThread.h"

BootstrapWords::BootstrapWords(ForthVocab* next)
: BasicForthVocab(next)
{
	add("nextToken", &NEXT_TOKEN);
	add("findWord", &FIND_WORD);
	add("printString", &PRINT_STRING);
	add("printNumber", &PRINT_NUMBER);
}

PrimitiveForthWordFunction BootstrapWords::NEXT_TOKEN(&BootstrapWords::F_NEXT_TOKEN, "BootstrapWords::NEXT_TOKEN", "nextToken");
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

static CompositeForthWord F_FIND_WORD(  // char* -- len
		CompositeForthWordBuilder("BootstrapWords::FIND_WORD")
				.compileCell(&VocabWords::CURRENT_VOCAB)
				.compileCell(&PrimitiveForthWords::CELL_AT)
				.compileCell(&VocabWords::SEARCH_VOCAB)
				.build());
ForthWord& BootstrapWords::FIND_WORD = F_FIND_WORD;

// stringAddr --
PrimitiveForthWordFunction BootstrapWords::PRINT_STRING(&BootstrapWords::F_PRINT_STRING, "BootstrapWords::PRINT_STRING", "printString");
void BootstrapWords::F_PRINT_STRING(ForthThread& thread) {
	NativeOSFunctions::printString(static_cast<char*>(thread.popDataStack().pointer));
}

// int --
static void F_PRINT_NUMBER(ForthThread& thread) {
	NativeOSFunctions::printString(std::to_string(thread.popDataStack().integer));
}
PrimitiveForthWordFunction BootstrapWords::PRINT_NUMBER(&F_PRINT_NUMBER, "BootstrapWords::PRINT_NUMBER", "printNumber");
