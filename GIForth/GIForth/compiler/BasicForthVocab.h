#ifndef GIFORTH_BASICFORTHVOCAB_H
#define GIFORTH_BASICFORTHVOCAB_H

#include "ForthVocab.h"
#include <string>
#include <map>

class BasicForthVocab : public ForthVocab {
public:
	BasicForthVocab(ForthVocab* next);
	BasicForthVocab(const BasicForthVocab& other) = default;
	~BasicForthVocab() override = default;

	void add(ForthWord* word);
	ForthWord*& operator[](const std::string& name);

protected:
	virtual ForthWord* doFindWord(const char* strAddr);

private:
	std::map<std::string, ForthWord*> words;
};

#endif //GIFORTH_BASICFORTHVOCAB_H
