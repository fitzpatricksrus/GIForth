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
	add("searchVocab", &SEARCH_VOCAB);
	add("sourceVocab", &SOURCE_VOCAB);
	add("destVocab", &DEST_VOCAB);
	add("addWordToVocab", &ADD_WORD_TO_VOCAB);
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
static PrimitiveForthWordFunction F_SEARCH_VOCAB(&findTheWord, "VocabWords::SEARCH_VOCAB");
ForthWord& VocabWords::SEARCH_VOCAB = F_SEARCH_VOCAB;

// word vocab --
static void addWordToVocab(ForthThread& thread) {
	ForthVocab* vocab = static_cast<ForthVocab*>(thread.popDataStack().pointer);
	ForthWord* word = static_cast<ForthWord*>(thread.popDataStack().pointer);
	vocab->add(word);
}
static PrimitiveForthWordFunction F_ADD_WORD_TO_VOCAB(&addWordToVocab, "VocabWords::ADD_WORD_TO_VOCAB");
ForthWord& VocabWords::ADD_WORD_TO_VOCAB = F_ADD_WORD_TO_VOCAB;

static CompositeForthWord F_SOURCE_VOCAB(
		CompositeForthWordBuilder("VocabWords::SOURCE_VOCAB")
				.compileConstant(&PrimitiveForthWords::registers[PrimitiveForthWords::SOURCE_VOCAB_STATE])
				.compileWord(&PrimitiveForthWords::CELL_AT)
				.build());
ForthWord& VocabWords::SOURCE_VOCAB = F_SOURCE_VOCAB;

static CompositeForthWord F_DEST_VOCAB(
		CompositeForthWordBuilder("VocabWords::DEST_VOCAB")
				.compileConstant(&PrimitiveForthWords::registers[PrimitiveForthWords::DEST_VOCAB_STATE])
				.compileWord(&PrimitiveForthWords::CELL_AT)
				.build());
ForthWord& VocabWords::DEST_VOCAB = F_DEST_VOCAB;

