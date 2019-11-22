//
// Created by Dad on 9/18/19.
//

#include "BootstrapWords.h"
#include <array>
#include <utils/CompositeForthWordBuilder.h>
#include <words/PrimitiveForthWords.h>
#include <words/CoreForthWords.h>
#include <words/compiler/CompilerWords.h>
#include "utils/NativeOSFunctions.hpp"
#include "runtime/ForthThread.h"

BootstrapWords::BootstrapWords(ForthVocab* next)
: BasicForthVocab(next)
{
	add(&NEXT_TOKEN);
	add(&FIND_WORD);
//	add(&PARSE_NUMBER);
	add(&PRINT_STRING);
}

PrimitiveForthWordFunction BootstrapWords::NEXT_TOKEN(&BootstrapWords::F_NEXT_TOKEN, "BootstrapWords::NEXT_TOKEN");
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
		CompositeForthWordBuilder("CoreForthWords::CURRENT_VOCAB")
				.compileCell(&CompilerWords::CURRENT_VOCAB)
				.compileCell(&PrimitiveForthWords::CELL_AT)
				.compileCell(&CompilerWords::SEARCH_VOCAB)
				.build());
ForthWord& BootstrapWords::FIND_WORD = F_FIND_WORD;

// stringAddr --
PrimitiveForthWordFunction BootstrapWords::PRINT_STRING(&BootstrapWords::F_PRINT_STRING, "BootstrapWords::PRINT_STRING");
void BootstrapWords::F_PRINT_STRING(ForthThread& thread) {
    NativeOSFunctions::printString(static_cast<char*>(thread.popDataStack().pointer));
}

