#include "runtime/utils/PrimitiveForthWordFunction.h"
#include "ForthVocab.h"
#include "utils/StringUtils.h"

ForthVocab::ForthVocab(ForthVocab* nextIn)
: next(nextIn), words()
{
}

const ForthWord *ForthVocab::findWord(const char *strAddr) {
	std::string str(strAddr);
	return findWord(str);
}

const ForthWord *ForthVocab::findWord(const std::string& str) {
	std::string n(str);
	StringUtils::toLower(n);
	return findWordWithLower(n);
}

void ForthVocab::add(ForthWord *word) {
	add(word->getNameInVocabulary(), word);
}

void ForthVocab::add(const std::string& name, ForthWord *word) {
	std::string lower(name);
	StringUtils::toLower(lower);
	(*this)[lower] = word;
}

const ForthWord*& ForthVocab::operator[](const std::string& ndx) {
	return words[ndx];
}

const ForthWord *ForthVocab::findWordWithLower(const std::string& str) {
	//NOTE: OMG!  word[] has a side affect! If the key isn't found,
	// the map INSERTS an entry for the key with a value of nullptr
	const ForthWord* result = words.count(str) > 0 ? words[str] : nullptr;
	if ((result == nullptr) && (next != nullptr)) {
		result = next->findWordWithLower(str);
	}
	return result;
}
