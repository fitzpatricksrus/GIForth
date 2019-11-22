#ifndef GIFORTH_BOOTSTRAPWORDS_H
#define GIFORTH_BOOTSTRAPWORDS_H

#include "utils/PrimitiveForthWordFunction.h"
#include "words/compiler/BasicForthVocab.h"

class BootstrapWords : public BasicForthVocab {
public:
	BootstrapWords(ForthVocab* next);
	BootstrapWords(const BootstrapWords& other) = default;
	virtual ~BootstrapWords() = default;

    // -- stringAddr
    static PrimitiveForthWordFunction NEXT_TOKEN;

    // stringAddr -- [ wordAddr true | stringAddr false ]
    static ForthWord& FIND_WORD;

    // stringAddr --
    static PrimitiveForthWordFunction PRINT_STRING;

private:
    static void F_NEXT_TOKEN(ForthThread& thread);
    static void F_PRINT_STRING(ForthThread& thread);
};

#endif //GIFORTH_BOOTSTRAPWORDS_H