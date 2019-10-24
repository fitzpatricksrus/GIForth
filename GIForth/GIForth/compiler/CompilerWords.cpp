//
// Created by stuff on 10/12/2019.
//

#include "utils/PrimitiveForthWordFunction.h"
#include "CompilerWords.h"
#include "ForthVocab.h"
#include "runtime/ForthThread.h"

CompilerWords::CompilerWords(ForthVocab *next)
: BasicForthVocab(next)
{
	add(&SEARCH_VOCAB);
}

// str* vocab* -- word true| false
static void findTheWord(ForthThread& thread) {
	ForthVocab* vocab = static_cast<ForthVocab*>(thread.popDataStack().pointer);
	char* str = static_cast<char*>(thread.popDataStack().pointer);
	ForthWord* result = vocab->findWord(str);
	if (result) {
		thread.pushDataStack(result);
		thread.pushDataStack(true);
	} else {
		thread.pushDataStack(false);
	}
}
static PrimitiveForthWordFunction F_SEARCH_VOCAB(&findTheWord, "COMPILER::SEARCH_VOCAB");
ForthWord& CompilerWords::SEARCH_VOCAB = F_SEARCH_VOCAB;

static void variableImpl(ForthThread& thread) {
	int ndx = thread.getIndex();
	ForthCell* cellPtr = &thread.getCellAt(ndx);
	ForthCell::PTR_TYPE ptr = static_cast<ForthCell::PTR_TYPE>(cellPtr);
	thread.pushDataStack(ptr);
	thread.offsetIndex(1);
}
static PrimitiveForthWordFunction F_VARIABLE_IMPL(&variableImpl, "COMPILER::VARIABLE_IMPL", { PrimitiveForthWordFunction::ParamType::INT });
ForthWord& CompilerWords::VARIABLE_IMPL = F_VARIABLE_IMPL;
