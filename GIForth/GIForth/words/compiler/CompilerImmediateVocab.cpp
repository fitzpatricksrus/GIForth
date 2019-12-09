//
// Created by stuff on 12/8/2019.
//

#include <runtime/utils/CompositeForthWordBuilder.h>
#include <runtime/CompositeForthWordWords.h>
#include <runtime/PrimitiveForthWords.h>
#include <utils/testing/debug.h>
#include "CompilerImmediateVocab.h"
#include "runtime/CompositeForthWord.h"

ForthVocab& CompilerImmediateVocab::getInstance() {
	static ForthVocab vocab(nullptr);
	static bool doInit = true;

	if (doInit) {
		vocab.add(&SEMI_COLON());
		vocab.add(&CompositeForthWordWords::COMPILE_IF());
		vocab.add(&CompositeForthWordWords::COMPILE_ELSE());
		vocab.add(&CompositeForthWordWords::COMPILE_ENDIF());
		vocab.add(&CompositeForthWordWords::COMPILE_WHILE());
		vocab.add(&CompositeForthWordWords::COMPILE_DO());
		vocab.add(&CompositeForthWordWords::COMPILE_ENDWHILE());
		vocab.add(&CompositeForthWordWords::COMPILE_REPEAT());
		vocab.add(&CompositeForthWordWords::COMPILE_UNTIL());
		vocab.add(&CompositeForthWordWords::COMPILE_FOREVER());
		doInit = false;
	}
	return vocab;
}

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


