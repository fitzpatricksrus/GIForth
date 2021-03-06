#ifndef GIFORTH_BOOTSTRAPWORDS_H
#define GIFORTH_BOOTSTRAPWORDS_H

#include "runtime/utils/PrimitiveForthWordFunction.h"
#include "runtime/ForthVocab.h"

class BootstrapWords : public ForthVocab {
public:
	explicit BootstrapWords(ForthVocab* next);
	BootstrapWords(const BootstrapWords& other) = default;
	~BootstrapWords() override = default;

    // -- stringAddr
    static ForthWord& NEXT_TOKEN();

    // stringAddr -- [ wordAddr true | stringAddr false ]
    static ForthWord& FIND_WORD();

	// stringAddr --
	static ForthWord& PRINT_STRING();

	// int --
	static ForthWord& PRINT_NUMBER();

private:
    static void F_NEXT_TOKEN(ForthThread& thread);
    static void F_PRINT_STRING(ForthThread& thread);
};

#endif //GIFORTH_BOOTSTRAPWORDS_H
