//
// Created by Dad on 11/24/19.
//

#ifndef GIFORTH_COMPILERWORDS_H
#define GIFORTH_COMPILERWORDS_H

#include <runtime/BasicForthVocab.h>
#include <utils/PrimitiveForthWordFunction.h>

class CompilerWords : public BasicForthVocab {
public:
	explicit CompilerWords(ForthVocab* next);
	CompilerWords(const CompilerWords& other) = default;
	~CompilerWords() override = default;

	// str --
	static PrimitiveForthWordFunction COMPILE_BEGIN;

	// word --
	static PrimitiveForthWordFunction COMPILE_TOS;

	// -- word
	static PrimitiveForthWordFunction COMPILE_END;

	// word --
	static PrimitiveForthWordFunction FREE_WORD;
};

#endif //GIFORTH_COMPILERWORDS_H
