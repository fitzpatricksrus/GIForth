//
// Created by stuff on 10/8/2019.
//

#include "utils/PrimitiveForthWordFunction.h"
#include "words/bootstrap/CompositeForthWordBuilder.h"
#include "ForthVocab.h"
#include "runtime/ForthThread.h"

ForthVocab::ForthVocab(ForthVocab* nextIn)
: next(nextIn)
{
}

ForthWord *ForthVocab::findWord(const char *strAddr) const {
	ForthWord* result = doFindWord(strAddr);
	if ((result == nullptr) && (next != nullptr)) {
		result = next->findWord(strAddr);
	}
	return result;
}

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

static PrimitiveForthWordFunction F_FIND_WORD_IN_VOCAB(&findTheWord, "COMPILER::FIND_WORD_IN_VOCAB");
ForthWord& FIND_WORD_IN_VOCAB = F_FIND_WORD_IN_VOCAB;	// str* vocab* -- word true| false
