#ifndef GIFORTH_COMPILERWORDS_H
#define GIFORTH_COMPILERWORDS_H

#include <runtime/BasicForthVocab.h>

class CompilerWords : public BasicForthVocab {
public:

	static ForthWord& COLON;
	static ForthWord& SEMICOLON;
};

#endif //GIFORTH_COMPILERWORDS_H
