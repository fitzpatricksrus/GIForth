//
// Created by stuff on 10/8/2019.
//

#include "BasicForthVocab.h"

BasicForthVocab::BasicForthVocab(ForthVocab *next)
: ForthVocab(next), words()
{
}

ForthWord *BasicForthVocab::doFindWord(const char *strAddr) {
	std::string str(strAddr);
	return words[str];
}
