#include <runtime/PrimitiveForthWords.h>
#include <words/CoreForthWords.h>
#include <words/VocabWords.h>
#include <runtime/CompositeForthWordWords.h>
#include "OuterInterpVocab.h"
#include "BootstrapWords.h"

ForthVocab& OuterInterpVocab::getInstance() {
	static ForthVocab vocab(nullptr);
	static bool doInit = true;
	
	if (doInit) {
		doInit = false;
		vocab.add(&PrimitiveForthWords::NOP());
		vocab.add(&PrimitiveForthWords::AT_RETURN_STACK());
		vocab.add(&PrimitiveForthWords::EXIT_THREAD());
		vocab.add(&PrimitiveForthWords::EXECUTE());
		vocab.add(&PrimitiveForthWords::CHAR_SIZE());
		vocab.add(&PrimitiveForthWords::INT_SIZE());
		vocab.add(&PrimitiveForthWords::PTR_SIZE());
		vocab.add(&PrimitiveForthWords::WORD_SIZE());
		vocab.add(&PrimitiveForthWords::ALLOC());
		vocab.add(&PrimitiveForthWords::FREE());
		vocab.add(&PrimitiveForthWords::REGISTER());
		vocab.add(&PrimitiveForthWords::CHAR_AT());
		vocab.add(&PrimitiveForthWords::CHAR_PUT());
		vocab.add(&PrimitiveForthWords::CHAR_INDEX());
		vocab.add(&PrimitiveForthWords::INT_AT());
		vocab.add(&PrimitiveForthWords::INT_PUT());
		vocab.add(&PrimitiveForthWords::INT_INDEX());
		vocab.add(&PrimitiveForthWords::CELL_AT());
		vocab.add(&PrimitiveForthWords::CELL_PUT());
		vocab.add(&PrimitiveForthWords::CELL_INDEX());
		vocab.add(&PrimitiveForthWords::SWAP());
		vocab.add(&PrimitiveForthWords::PICK());
		vocab.add(&PrimitiveForthWords::OVER());
		vocab.add(&PrimitiveForthWords::ROLL());
		vocab.add(&PrimitiveForthWords::DROP());
		vocab.add(&PrimitiveForthWords::DUP());
		vocab.add(&PrimitiveForthWords::ADD());
		vocab.add(&PrimitiveForthWords::SUBTRACT());
		vocab.add(&PrimitiveForthWords::MULTIPLY());
		vocab.add(&PrimitiveForthWords::DIVIDE());
		vocab.add(&PrimitiveForthWords::MOD());
		vocab.add(&PrimitiveForthWords::LESS_THAN());
		vocab.add(&PrimitiveForthWords::GREATER_THAN());
		vocab.add(&PrimitiveForthWords::EQUAL());
		vocab.add(&PrimitiveForthWords::CONDITIONAL_AND());
		vocab.add(&PrimitiveForthWords::CONDITIONAL_OR());
		vocab.add(&PrimitiveForthWords::CONDITIONAL_NOT());
		vocab.add(&PrimitiveForthWords::ACCEPT_INPUT());
		vocab.add(&PrimitiveForthWords::PEEK_NEXT_INPUT_CHAR());
		vocab.add(&PrimitiveForthWords::GET_NEXT_INPUT_CHAR());
		vocab.add(&PrimitiveForthWords::PRINT_CHAR());
		vocab.add(&PrimitiveForthWords::FALSE());
		vocab.add(&PrimitiveForthWords::TRUE());
		vocab.add(&PrimitiveForthWords::ZERO());
		vocab.add(&PrimitiveForthWords::ONE());
		vocab.add(&PrimitiveForthWords::NEGATIVE_ONE());
		vocab.add(&PrimitiveForthWords::ADD_ONE());
		vocab.add(&PrimitiveForthWords::SUBTRACT_ONE());
		vocab.add(&PrimitiveForthWords::TRACE());

		vocab.add(&CoreForthWords::STRLEN());
		vocab.add(&CoreForthWords::STRCPY());
		vocab.add(&CoreForthWords::STRREVERSE());
		vocab.add(&CoreForthWords::PARSE_DIGIT());
		vocab.add(&CoreForthWords::PARSE_NUMBER());
		vocab.add(&CoreForthWords::NUMBER_TO_CHARACERS());

		vocab.add(&VocabWords::SEARCH_VOCAB());
		vocab.add(&VocabWords::SOURCE_VOCAB());
		vocab.add(&VocabWords::DEST_VOCAB());
		vocab.add(&VocabWords::ADD_WORD_TO_VOCAB());

		vocab.add(&BootstrapWords::NEXT_TOKEN());
		vocab.add(&BootstrapWords::FIND_WORD());
		vocab.add(&BootstrapWords::PRINT_STRING());
		vocab.add(&BootstrapWords::PRINT_NUMBER());

		vocab.add(&CompositeForthWordWords::COMPILE_BEGIN());
		vocab.add(&CompositeForthWordWords::COMPILE_TOS());
		vocab.add(&CompositeForthWordWords::COMPILE_END());
		vocab.add(&CompositeForthWordWords::FREE_WORD());
		vocab.add(&CompositeForthWordWords::FORWARD_MARK());
		vocab.add(&CompositeForthWordWords::FORWARD_RESOLVE());
		vocab.add(&CompositeForthWordWords::FORWARD_MARK_RESOLVE());
		vocab.add(&CompositeForthWordWords::BACKWARD_MARK());
		vocab.add(&CompositeForthWordWords::BACKWARD_RESOLVE());
		vocab.add(&CompositeForthWordWords::THREAD_AT());
	}

	return vocab;
}