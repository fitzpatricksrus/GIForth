#ifndef GIFORTH_COMPOSITEFORTHWORDWORDS_H
#define GIFORTH_COMPOSITEFORTHWORDWORDS_H

#include <runtime/BasicForthVocab.h>
#include <runtime/utils/PrimitiveForthWordFunction.h>

class CompositeForthWordWords : public BasicForthVocab {
public:
	explicit CompositeForthWordWords(ForthVocab* next);
	CompositeForthWordWords(const CompositeForthWordWords& other) = default;
	~CompositeForthWordWords() override = default;

	// str --
	static PrimitiveForthWordFunction COMPILE_BEGIN;

	// --
	static PrimitiveForthWordFunction COMPILE_TOS;

	// -- word
	static PrimitiveForthWordFunction COMPILE_END;

	// word --
	static PrimitiveForthWordFunction FREE_WORD;
};

#endif //GIFORTH_COMPOSITEFORTHWORDWORDS_H
