#include <runtime/PrimitiveForthWords.h>
#include <runtime/utils/CompositeForthWordBuilder.h>
#include "CompositeForthWordWords.h"
#include "runtime/ForthThread.h"
#include "utils/testing/debug.h"

using ParamType = PrimitiveForthWordFunction::ParamType;

CompositeForthWordWords::CompositeForthWordWords(ForthVocab *next)
		: ForthVocab(next)
{
	add(&COMPILE_BEGIN);
	add(&COMPILE_TOS);
	add(&COMPILE_END);
	add(&FREE_WORD);
	add(&FORWARD_MARK);
	add(&FORWARD_RESOLVE);
	add(&FORWARD_MARK_RESOLVE);
	add(&BACKWARD_MARK);
	add(&BACKWARD_RESOLVE);
	add(&THREAD_AT);
}

static inline CompositeForthWordBuilder* builder() {
	return static_cast<CompositeForthWordBuilder*>(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer);
}

static void F_COMPILE_BEGIN(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer == nullptr);
	std::string name(static_cast<char*>(thread.popDataStack().pointer));
	PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE] = new CompositeForthWordBuilder(name);
}
PrimitiveForthWordFunction CompositeForthWordWords::COMPILE_BEGIN(&F_COMPILE_BEGIN,
																  "CompilerWords::COMPILE_BEGIN", "compileBegin", { ParamType::PTR });

static void F_COMPILE_TOS(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer != nullptr);
	builder()->compileCell(thread.popDataStack());
}
PrimitiveForthWordFunction CompositeForthWordWords::COMPILE_TOS(&F_COMPILE_TOS,
																"CompilerWords::COMPILE_TOS", "compileTOS");

static void F_FORWARD_MARK(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer != nullptr);
	builder()->forwardMark();
}
PrimitiveForthWordFunction CompositeForthWordWords::FORWARD_MARK(&F_FORWARD_MARK,
																 "CompilerWords::FORWARD_MARK", ">mark");

static void F_FORWARD_RESOLVE(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer != nullptr);
	builder()->forwardResolve();
}
PrimitiveForthWordFunction CompositeForthWordWords::FORWARD_RESOLVE(&F_FORWARD_RESOLVE,
																	"CompilerWords::FORWARD_RESOLVE", ">resolve");

static void F_FORWARD_MARK_RESOLVE(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer != nullptr);
	builder()->forwardMarkResolve();
}
PrimitiveForthWordFunction CompositeForthWordWords::FORWARD_MARK_RESOLVE(&F_FORWARD_MARK_RESOLVE,
																	"CompilerWords::FORWARD_MARK_RESOLVE", ">markResolve");

static void F_BACKWARD_MARK(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer != nullptr);
	builder()->backwardMark();
}
PrimitiveForthWordFunction CompositeForthWordWords::BACKWARD_MARK(&F_BACKWARD_MARK,
																  "CompilerWords::BACKWARD_MARK", "<mark");

static void F_BACKWARD_RESOLVE(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer != nullptr);
	builder()->backwardResolve();
}
PrimitiveForthWordFunction CompositeForthWordWords::BACKWARD_RESOLVE(&F_BACKWARD_RESOLVE,
																	 "CompilerWords::BACKWARD_RESOLVE", "<resolve");

static void F_COMPILE_END(ForthThread &thread) {
	checkTrue(PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE].pointer != nullptr);
	thread.pushDataStack(static_cast<ForthCell::PTR_TYPE>(new CompositeForthWord(builder()->build())));
	PrimitiveForthWords::registers[PrimitiveForthWords::COMPILE_STATE] = static_cast<ForthCell::PTR_TYPE>(nullptr);
}
PrimitiveForthWordFunction CompositeForthWordWords::COMPILE_END(&F_COMPILE_END,
	"CompilerWords::COMPILE_END", "compileEnd");

static void F_FREE_WORD(ForthThread &thread) {
	CompositeForthWord* word = static_cast<CompositeForthWord*>(thread.popDataStack().pointer);
	checkTrue(word != nullptr);
	delete word;
}
PrimitiveForthWordFunction CompositeForthWordWords::FREE_WORD(&F_FREE_WORD,
	"CompilerWords::FREE_WORD", "FREE_WORD");

// ndx word --
static void F_THREAD_AT(ForthThread &thread) {
	CompositeForthWord* word = static_cast<CompositeForthWord*>(thread.popDataStack().pointer);
	int ndx = thread.popDataStack().integer;
	thread.pushDataStack((*word)[ndx]);
}
PrimitiveForthWordFunction CompositeForthWordWords::THREAD_AT(&F_THREAD_AT,
															  "CompilerWords::THREAD_AT", "thread@");
