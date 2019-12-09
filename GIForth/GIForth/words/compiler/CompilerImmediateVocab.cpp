//
// Created by stuff on 12/8/2019.
//

#include <runtime/utils/CompositeForthWordBuilder.h>
#include <runtime/CompositeForthWordWords.h>
#include <runtime/PrimitiveForthWords.h>
#include "CompilerImmediateVocab.h"
#include "runtime/CompositeForthWord.h"

/*
: ;
	compileEnd
 	true
 	false
 	return
 	;

*/
ForthWord& CompilerImmediateVocab::SEMI_COLON() {
	static CompositeForthWord sc(CompositeForthWordBuilder("CompilerWords::;")
			.compileWord(&CompositeForthWordWords::COMPILE_END())
			.compileWord(&PrimitiveForthWords::TRUE())                    //result of compile
			.compileWord(&PrimitiveForthWords::FALSE())                   //cause compile to exit
			.build());
	return sc;
}

ForthVocab& CompilerImmediateVocab::getInstance() {
	static ForthVocab vocab(nullptr);
	static bool doInit = true;

	if (doInit) {
		vocab.add(&SEMI_COLON());
		doInit = false;
	}
	return vocab;
}

