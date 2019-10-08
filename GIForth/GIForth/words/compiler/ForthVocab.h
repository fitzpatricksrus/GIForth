//
// Created by stuff on 10/8/2019.
//

#ifndef GIFORTH_FORTHVOCAB_H
#define GIFORTH_FORTHVOCAB_H

#include "runtime/ForthThreadLocal.h"

class ForthWord;

class ForthVocab {
public:
	ForthVocab(ForthVocab* next);
	ForthVocab(const ForthVocab& other) = default;
	virtual ~ForthVocab() = default;
	ForthWord* findWord(const char* strAddr) const;

	static ForthVocab* getCurrentVocab();
	static void setCurrentVocab(ForthVocab* newVocab);

protected:
	virtual ForthWord* doFindWord(const char* strAddr) const = 0;

private:
	ForthVocab* next;
	static ForthThreadLocal<ForthVocab*> currentVocab;
};


#endif //GIFORTH_FORTHVOCAB_H
