//
// Created by stuff on 10/8/2019.
//

#include "BasicForthVocab.h"
#include "runtime/ForthWord.h"

BasicForthVocab::BasicForthVocab(ForthVocab *next)
: ForthVocab(next), words()
{
}

ForthWord *BasicForthVocab::doFindWord(const char *strAddr) {
	std::string str(strAddr);
	return words[str];
}

void BasicForthVocab::add(ForthWord *word) {
	(*this)[word->getNameInVocabulary()] = word;
}

ForthWord*& BasicForthVocab::operator[](const std::string& ndx) {
	return words[ndx];
}
