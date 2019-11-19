//
// Created by stuff on 10/8/2019.
//

#include "utils/PrimitiveForthWordFunction.h"
#include "utils/CompositeForthWordBuilder.h"
#include "ForthVocab.h"

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
