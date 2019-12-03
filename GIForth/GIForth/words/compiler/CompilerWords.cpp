#include <words/PrimitiveForthWords.h>
#include <utils/CompositeForthWordBuilder.h>
#include "CompilerWords.h"
#include "runtime/ForthThread.h"
#include "utils/testing/debug.h"

using ParamType = PrimitiveForthWordFunction::ParamType;

CompilerWords::CompilerWords(ForthVocab *next)
		: BasicForthVocab(next)
{
	add(&COMPILE_BEGIN);
	add(&COMPILE_TOS);
	add(&COMPILE_END);
	add(&FREE_WORD);
}

static CompositeForthWordBuilder* builder() {
	return static_cast<CompositeForthWordBuilder*>(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer);
}

static void F_COMPILE_BEGIN(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer == nullptr);
	std::string name(static_cast<char*>(thread.popDataStack().pointer));
	PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE] = new CompositeForthWordBuilder(name);
}
PrimitiveForthWordFunction CompilerWords::COMPILE_BEGIN(&F_COMPILE_BEGIN,
	"CompilerWords::COMPILE_BEGIN", "COMPILE_BEGIN", { ParamType::PTR });

static void F_COMPILE_TOS(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer != nullptr);
	builder()->compileCell(thread.popDataStack());
}
PrimitiveForthWordFunction CompilerWords::COMPILE_TOS(&F_COMPILE_TOS,
	"CompilerWords::COMPILE_TOS", "COMPILE_TOS");

static void F_COMPILE_END(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer != nullptr);
	thread.pushDataStack(static_cast<ForthCell::PTR_TYPE>(new CompositeForthWord(builder()->build())));
	PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE] = static_cast<ForthCell::PTR_TYPE>(nullptr);
}
PrimitiveForthWordFunction CompilerWords::COMPILE_END(&F_COMPILE_END,
	"CompilerWords::COMPILE_END", "COMPILE_END");

static void F_FREE_WORD(ForthThread &thread) {
	CompositeForthWord* word = static_cast<CompositeForthWord*>(thread.popDataStack().pointer);
	checkTrue(word != nullptr);
	delete word;
}
PrimitiveForthWordFunction CompilerWords::FREE_WORD(&F_FREE_WORD,
	"CompilerWords::FREE_WORD", "FREE_WORD");

