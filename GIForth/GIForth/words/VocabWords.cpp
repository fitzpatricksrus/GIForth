//
// Created by stuff on 10/12/2019.
//

#include <runtime/utils/CompositeForthWordBuilder.h>
#include <runtime/PrimitiveForthWords.h>
#include "runtime/utils/PrimitiveForthWordFunction.h"
#include "VocabWords.h"
#include "runtime/ForthVocab.h"
#include "runtime/ForthThread.h"

VocabWords::VocabWords(ForthVocab *next)
: ForthVocab(next)
{
	add(&VocabWords::SEARCH_VOCAB());
	add(&VocabWords::SOURCE_VOCAB());
	add(&VocabWords::DEST_VOCAB());
	add(&VocabWords::ADD_WORD_TO_VOCAB());
}

// str* vocab* -- word true| str* false
static void findTheWord(ForthThread& thread) {
	ForthVocab* vocab = static_cast<ForthVocab*>(thread.popDataStack().pointer);
	char* str = static_cast<char*>(thread.popDataStack().pointer);
	const ForthWord* result = vocab->findWord(str);
	if (result) {
		thread.pushDataStack(const_cast<ForthWord*>(result));
		thread.pushDataStack(true);
	} else {
		thread.pushDataStack(static_cast<ForthCell::PTR_TYPE>(str));
		thread.pushDataStack(false);
	}
}
ForthWord& VocabWords::SEARCH_VOCAB() {
	static PrimitiveForthWordFunction word(&findTheWord, "VocabWords::searchVocab");
	return word;
}

// word vocab --
static void addWordToVocab(ForthThread& thread) {
	ForthVocab* vocab = static_cast<ForthVocab*>(thread.popDataStack().pointer);
	ForthWord* word = static_cast<ForthWord*>(thread.popDataStack().pointer);
	vocab->add(word);
}
ForthWord& VocabWords::ADD_WORD_TO_VOCAB() {
	static PrimitiveForthWordFunction word(&addWordToVocab, "VocabWords::addWordToVocab");
	return word;
}

ForthWord& VocabWords::SOURCE_VOCAB() {
	static CompositeForthWord word(
			CompositeForthWordBuilder("VocabWords::sourceVocab")
					.compileConstant(&PrimitiveForthWords::registers[PrimitiveForthWords::SOURCE_VOCAB_STATE])
					.compileWord(&PrimitiveForthWords::CELL_AT())
					.build());
	return word;
}

ForthWord& VocabWords::DEST_VOCAB() {
	static CompositeForthWord word(
			CompositeForthWordBuilder("VocabWords::destVocab")
					.compileConstant(&PrimitiveForthWords::registers[PrimitiveForthWords::DEST_VOCAB_STATE])
					.compileWord(&PrimitiveForthWords::CELL_AT())
					.build());
	return word;
}

