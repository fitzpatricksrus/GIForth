//
// Created by stuff on 10/8/2019.
//

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

ForthVocab *ForthVocab::getCurrentVocab() {
	return *currentVocab;
}

void ForthVocab::setCurrentVocab(ForthVocab *newVocab) {
	*currentVocab = newVocab;
}

ForthThreadLocal<ForthVocab*> ForthVocab::currentVocab(nullptr);
