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
	static ForthWord& COMPILE_BEGIN();

	// value/word --
	static ForthWord& COMPILE_TOS();

	static ForthWord& FORWARD_MARK();
	static ForthWord& FORWARD_RESOLVE();

	static ForthWord& FORWARD_MARK_RESOLVE();

	static ForthWord& BACKWARD_MARK();
	static ForthWord& BACKWARD_RESOLVE();

	static ForthWord& COMPILE_IF();
	static ForthWord& COMPILE_ELSE();
	static ForthWord& COMPILE_ENDIF();
	static ForthWord& COMPILE_WHILE();
	static ForthWord& COMPILE_DO();
	static ForthWord& COMPILE_ENDWHILE();
	static ForthWord& COMPILE_REPEAT();
	static ForthWord& COMPILE_FOREVER();
	static ForthWord& COMPILE_UNTIL();

	// -- word
	static ForthWord& COMPILE_END();

	// word --
	static ForthWord& FREE_WORD();

	// ndx word --
	static ForthWord& THREAD_AT();
};

#endif //GIFORTH_COMPOSITEFORTHWORDWORDS_H
