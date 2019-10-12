//
// Created by stuff on 10/12/2019.
//

#ifndef GIFORTH_COMPILERWORDS_H
#define GIFORTH_COMPILERWORDS_H

#include "BasicForthVocab.h"

class CompilerWords : public BasicForthVocab {
public:
	CompilerWords(ForthVocab* next);
	CompilerWords(const CompilerWords& other) = default;
	virtual ~CompilerWords() = default;

	static ForthWord& SEARCH_VOCAB;
};


#endif //GIFORTH_COMPILERWORDS_H
