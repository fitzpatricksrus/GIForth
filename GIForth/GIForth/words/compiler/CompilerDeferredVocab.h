#ifndef GIFORTH_COMPILERDEFERREDVOCAB_H
#define GIFORTH_COMPILERDEFERREDVOCAB_H

#include <runtime/ForthVocab.h>

class CompilerDeferredVocab : public ForthVocab {
public:
	static ForthVocab& getInstance();
};


#endif //GIFORTH_COMPILERDEFERREDVOCAB_H
