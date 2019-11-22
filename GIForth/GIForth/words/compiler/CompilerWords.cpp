//
// Created by stuff on 10/12/2019.
//

#include <utils/CompositeForthWordBuilder.h>
#include <words/PrimitiveForthWords.h>
#include "utils/PrimitiveForthWordFunction.h"
#include "CompilerWords.h"
#include "ForthVocab.h"
#include "runtime/ForthThread.h"

CompilerWords::CompilerWords(ForthVocab *next)
: BasicForthVocab(next)
{
	add("searchVocab", &SEARCH_VOCAB);
	add("currentVocab", &CURRENT_VOCAB);
}

// str* vocab* -- word true| str* false
static void findTheWord(ForthThread& thread) {
	ForthVocab* vocab = static_cast<ForthVocab*>(thread.popDataStack().pointer);
	char* str = static_cast<char*>(thread.popDataStack().pointer);
	const ForthWord* result = vocab->findWord(str);
	if (result) {
		thread.pushDataStack(const_cast<ForthWord*>(result));
		thread.pushDataStack(true);
	} else {
		thread.pushDataStack(static_cast<ForthCell::PTR_TYPE>(str));
		thread.pushDataStack(false);
	}
}
static PrimitiveForthWordFunction F_SEARCH_VOCAB(&findTheWord, "COMPILER::SEARCH_VOCAB");
ForthWord& CompilerWords::SEARCH_VOCAB = F_SEARCH_VOCAB;

static CompositeForthWord F_CURRENT_VOCAB(  // char* -- len
		CompositeForthWordBuilder("CoreForthWords::CURRENT_VOCAB")
				.compileConstant(&PrimitiveForthWords::registers + PrimitiveForthWords::COMPILER_STATE)
				.build());
ForthWord& CompilerWords::CURRENT_VOCAB = F_CURRENT_VOCAB;
