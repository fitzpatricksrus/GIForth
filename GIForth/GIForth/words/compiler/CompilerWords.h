#ifndef GIFORTH_COMPILERWORDS_H
#define GIFORTH_COMPILERWORDS_H

#include <runtime/ForthVocab.h>

class CompilerWords : public ForthVocab {
public:
	CompilerWords(ForthVocab* parent);
	virtual ~CompilerWords() = default;

	static ForthVocab* getCompilerVocabInstance();
	static ForthWord& COMPILE_WORD;
	static ForthWord& COLON;
};

#endif //GIFORTH_COMPILERWORDS_H
