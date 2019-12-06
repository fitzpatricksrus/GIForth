#ifndef GIFORTH_COMPILERWORDS_H
#define GIFORTH_COMPILERWORDS_H

#include <runtime/BasicForthVocab.h>

class CompilerWords : public BasicForthVocab {
public:
	CompilerWords(ForthVocab* parent);
	virtual ~CompilerWords() = default;

	static ForthVocab* getCompilerVocabInstance();
	static ForthWord& COMPILE_WORD;
	static ForthWord& COLON;
};

#endif //GIFORTH_COMPILERWORDS_H
