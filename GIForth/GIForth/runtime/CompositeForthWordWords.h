#ifndef GIFORTH_COMPOSITEFORTHWORDWORDS_H
#define GIFORTH_COMPOSITEFORTHWORDWORDS_H

#include <runtime/ForthVocab.h>
#include <runtime/utils/PrimitiveForthWordFunction.h>

class CompositeForthWordWords : public ForthVocab {
public:
	explicit CompositeForthWordWords(ForthVocab* next);
	CompositeForthWordWords(const CompositeForthWordWords& other) = default;
	~CompositeForthWordWords() override = default;

	// str --
	static PrimitiveForthWordFunction COMPILE_BEGIN;

	// value/word --
	static PrimitiveForthWordFunction COMPILE_TOS;

	static PrimitiveForthWordFunction FORWARD_MARK;
	static PrimitiveForthWordFunction FORWARD_RESOLVE;

	static PrimitiveForthWordFunction BACKWARD_MARK;
	static PrimitiveForthWordFunction BACKWARD_RESOLVE;

	// -- word
	static PrimitiveForthWordFunction COMPILE_END;

	// word --
	static PrimitiveForthWordFunction FREE_WORD;

	// ndx word --
	static PrimitiveForthWordFunction THREAD_AT;
};

#endif //GIFORTH_COMPOSITEFORTHWORDWORDS_H
