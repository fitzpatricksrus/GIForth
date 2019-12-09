//
// Created by stuff on 12/8/2019.
//

#include "runtime/NativeOSFunctions.hpp"
#include "runtime/CompositeForthWord.h"
#include "runtime/ForthThread.h"
#include <runtime/PrimitiveForthWords.h>
#include "CompilerDeferredVocab.h"

ForthVocab& CompilerDeferredVocab::getInstance() {
	static ForthVocab vocab(nullptr);
	static bool doInit = true;

	if (doInit) {
		doInit = false;
		vocab.add(&PrimitiveForthWords::JUMP());
		vocab.add(&PrimitiveForthWords::JUMP_IF_FALSE());
		vocab.add(&PrimitiveForthWords::RETURN());
		vocab.add(&PrimitiveForthWords::RECURSE());
		vocab.add(&PrimitiveForthWords::PUSH_NEXT_CELL());
		vocab.add(&PrimitiveForthWords::TO_RETURN_STACK());
		vocab.add(&PrimitiveForthWords::FROM_RETURN_STACK());
	}
	return vocab;
}
