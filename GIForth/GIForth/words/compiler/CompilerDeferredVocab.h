#ifndef GIFORTH_COMPILERDEFERREDVOCAB_H
#define GIFORTH_COMPILERDEFERREDVOCAB_H

#include <runtime/ForthVocab.h>
#include "runtime/utils/PrimitiveForthWordFunction.h"
#include "runtime/ForthCell.h"

class CompilerDeferredVocab : public ForthVocab {
public:
	static ForthVocab& getInstance();
};


#endif //GIFORTH_COMPILERDEFERREDVOCAB_H
