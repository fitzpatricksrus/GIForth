//
// Created by stuff on 10/8/2019.
//

#ifndef GIFORTH_BASICFORTHVOCAB_H
#define GIFORTH_BASICFORTHVOCAB_H

#include "ForthVocab.h"

class BasicForthVocab : public ForthVocab {
public:
	BasicForthVocab(ForthVocab* next);
	BasicForthVocab(const BasicForthVocab& other) = default;
	virtual ~BasicForthVocab() = default;

protected:
	virtual ForthWord* doFindWord(const char* strAddr);

private:
	std::map<std::string, ForthWord*> words;
};

#endif //GIFORTH_BASICFORTHVOCAB_H
