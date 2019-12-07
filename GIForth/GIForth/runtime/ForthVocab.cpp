//
// Created by stuff on 10/8/2019.
//

#include "runtime/utils/PrimitiveForthWordFunction.h"
#include "runtime/utils/CompositeForthWordBuilder.h"
#include "ForthVocab.h"

ForthVocab::ForthVocab(ForthVocab* nextIn)
: next(nextIn), words()
{
}

const ForthWord *ForthVocab::findWord(const char *strAddr) {
	std::string str(strAddr);
	return findWord(str);
}

const ForthWord *ForthVocab::findWord(const std::string& str) {
	//NOTE: OMG!  word[] has a side affect! If the key isn't found,
	// the map INSERTS an entry for the key with a value of nullptr
	const ForthWord* result = words.count(str) > 0 ? words[str] : nullptr;
	if ((result == nullptr) && (next != nullptr)) {
		result = next->findWord(str);
	}
	return result;
}

void ForthVocab::add(ForthWord *word) {
	add(word->getNameInVocabulary(), word);
}

void ForthVocab::add(const std::string& name, ForthWord *word) {
	(*this)[name] = word;
}

const ForthWord*& ForthVocab::operator[](const std::string& ndx) {
	return words[ndx];
}
