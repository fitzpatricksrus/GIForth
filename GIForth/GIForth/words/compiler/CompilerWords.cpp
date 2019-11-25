//
// Created by Dad on 11/24/19.
//

#include "CompilerWords.h"
#include "runtime/ForthThread.h"

using ParamType = PrimitiveForthWordFunction::ParamType;

static void F_COMPILE_BEGIN(ForthThread &thread) {
}
PrimitiveForthWordFunction CompilerWords::COMPILE_BEGIN(&F_COMPILE_BEGIN,
	"CompilerWords::COMPILE_BEGIN", "COMPILE_BEGIN", { ParamType::PTR });

static void F_COMPILE_TOS(ForthThread &thread) {
}
PrimitiveForthWordFunction CompilerWords::COMPILE_TOS(&F_COMPILE_TOS,
	"CompilerWords::COMPILE_TOS", "COMPILE_TOS");

static void F_COMPILE_END(ForthThread &thread) {
}
PrimitiveForthWordFunction CompilerWords::COMPILE_END(&F_COMPILE_END,
	"CompilerWords::COMPILE_END", "COMPILE_END");

static void F_FREE_WORD(ForthThread &thread) {
}
PrimitiveForthWordFunction CompilerWords::FREE_WORD(&F_FREE_WORD,
	"CompilerWords::FREE_WORD", "FREE_WORD");

