//
// Created by Dad on 9/18/19.
//

#include "BootstrapWords.h"
#include <array>
#include <runtime/utils/CompositeForthWordBuilder.h>
#include <words/VocabWords.h>
#include "runtime/NativeOSFunctions.hpp"
#include "runtime/ForthThread.h"

BootstrapWords::BootstrapWords(ForthVocab* next)
: ForthVocab(next)
{
	add(&NEXT_TOKEN());
	add(&FIND_WORD());
	add(&PRINT_STRING());
	add(&PRINT_NUMBER());
}

ForthWord& BootstrapWords::NEXT_TOKEN() {
	static PrimitiveForthWordFunction word(&BootstrapWords::F_NEXT_TOKEN, "BootstrapWords::nextToken", "nextToken");
	return word;
}
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

ForthWord& BootstrapWords::FIND_WORD() {
	static CompositeForthWord word(  // char* -- len
			CompositeForthWordBuilder("BootstrapWords::findWord")
					.compileCell(&VocabWords::SOURCE_VOCAB())
					.compileCell(&VocabWords::SEARCH_VOCAB())
					.build());
	return word;
}

// stringAddr --
ForthWord& BootstrapWords::PRINT_STRING() {
	static PrimitiveForthWordFunction word(&BootstrapWords::F_PRINT_STRING, "BootstrapWords::printString", "printString");
	return word;
}
void BootstrapWords::F_PRINT_STRING(ForthThread& thread) {
	NativeOSFunctions::printString(static_cast<char*>(thread.popDataStack().pointer));
}

// int --
static void F_PRINT_NUMBER(ForthThread& thread) {
	NativeOSFunctions::printString(std::to_string(thread.popDataStack().integer));
}
ForthWord& BootstrapWords::PRINT_NUMBER() {
	static PrimitiveForthWordFunction word(&F_PRINT_NUMBER, "BootstrapWords::printNumber", "printNumber");
	return word;
}
