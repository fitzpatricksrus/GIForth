#ifndef GIFORTH_COMPILERIMMEDIATEVOCAB_H
#define GIFORTH_COMPILERIMMEDIATEVOCAB_H

#include <runtime/ForthVocab.h>

class CompilerImmediateVocab : public ForthVocab {
public:
	static ForthVocab& getInstance();

	static ForthWord& SEMI_COLON();
};


#endif //GIFORTH_COMPILERIMMEDIATEVOCAB_H
