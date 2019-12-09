#ifndef GIFORTH_OUTERINTERPVOCAB_H
#define GIFORTH_OUTERINTERPVOCAB_H

#include <runtime/ForthVocab.h>

class OuterInterpVocab : public ForthVocab {
public:
	static ForthVocab& getInstance();
};

#endif //GIFORTH_OUTERINTERPVOCAB_H
