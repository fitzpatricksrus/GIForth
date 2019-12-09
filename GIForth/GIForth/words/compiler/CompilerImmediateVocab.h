#ifndef GIFORTH_COMPILERIMMEDIATEVOCAB_H
#define GIFORTH_COMPILERIMMEDIATEVOCAB_H

#include <runtime/ForthVocab.h>

class CompilerImmediateVocab : public ForthVocab {
public:
	static ForthVocab& getInstance();

	static ForthWord& SEMI_COLON();
	static ForthWord& IF();
	static ForthWord& ELSE();
	static ForthWord& ENDIF();
	static ForthWord& WHILE();
	static ForthWord& DO();
	static ForthWord& ENDWHILE();
	static ForthWord& REPEAT();
	static ForthWord& UNTIL();
	static ForthWord& FOREVER();
};


#endif //GIFORTH_COMPILERIMMEDIATEVOCAB_H
