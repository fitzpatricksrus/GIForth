//
// Created by stuff on 10/8/2019.
//

#include "BasicForthVocab.h"
#include "runtime/ForthWord.h"

BasicForthVocab::BasicForthVocab(ForthVocab *next)
: ForthVocab(next), words()
{
}

const ForthWord* BasicForthVocab::doFindWord(const char *strAddr) {
	std::string str(strAddr);
	auto r = words[str];
	return words[str];
}

void BasicForthVocab::add(ForthWord *word) {
	(*this)[word->getNameInVocabulary()] = word;
}

const ForthWord*& BasicForthVocab::operator[](const std::string& ndx) {
	return words[ndx];
}