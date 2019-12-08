#include <runtime/PrimitiveForthWords.h>
#include <words/CoreForthWords.h>
#include <words/VocabWords.h>
#include "OuterInterpVocab.h"
#include "BootstrapWords.h"

ForthVocab& OuterInterpVocab::getInstance() {
	static ForthVocab vocab(nullptr);
	static bool doInit = true;
	
	if (doInit) {
		doInit = false;
		vocab.add(&PrimitiveForthWords::NOP);
		vocab.add(&PrimitiveForthWords::JUMP);
		vocab.add(&PrimitiveForthWords::JUMP_IF_FALSE);
		vocab.add(&PrimitiveForthWords::RETURN);
		vocab.add(&PrimitiveForthWords::EXIT_THREAD);
		vocab.add(&PrimitiveForthWords::EXECUTE);
		vocab.add(&PrimitiveForthWords::PUSH_NEXT_CELL);
		vocab.add(&PrimitiveForthWords::CHAR_SIZE);
		vocab.add(&PrimitiveForthWords::INT_SIZE);
		vocab.add(&PrimitiveForthWords::PTR_SIZE);
		vocab.add(&PrimitiveForthWords::WORD_SIZE);
		vocab.add(&PrimitiveForthWords::ALLOC);
		vocab.add(&PrimitiveForthWords::FREE);
		vocab.add(&PrimitiveForthWords::REGISTER);
		vocab.add(&PrimitiveForthWords::CHAR_AT);
		vocab.add(&PrimitiveForthWords::CHAR_PUT);
		vocab.add(&PrimitiveForthWords::CHAR_INDEX);
		vocab.add(&PrimitiveForthWords::INT_AT);
		vocab.add(&PrimitiveForthWords::INT_PUT);
		vocab.add(&PrimitiveForthWords::INT_INDEX);
		vocab.add(&PrimitiveForthWords::CELL_AT);
		vocab.add(&PrimitiveForthWords::CELL_PUT);
		vocab.add(&PrimitiveForthWords::CELL_INDEX);
		vocab.add(&PrimitiveForthWords::TO_RETURN_STACK);
		vocab.add(&PrimitiveForthWords::FROM_RETURN_STACK);
		vocab.add(&PrimitiveForthWords::AT_RETURN_STACK);
		vocab.add(&PrimitiveForthWords::SWAP);
		vocab.add(&PrimitiveForthWords::PICK);
		vocab.add(&PrimitiveForthWords::OVER);
		vocab.add(&PrimitiveForthWords::ROLL);
		vocab.add(&PrimitiveForthWords::DROP);
		vocab.add(&PrimitiveForthWords::DUP);
		vocab.add(&PrimitiveForthWords::ADD);
		vocab.add(&PrimitiveForthWords::SUBTRACT);
		vocab.add(&PrimitiveForthWords::MULTIPLY);
		vocab.add(&PrimitiveForthWords::DIVIDE);
		vocab.add(&PrimitiveForthWords::MOD);
		vocab.add(&PrimitiveForthWords::LESS_THAN);
		vocab.add(&PrimitiveForthWords::GREATER_THAN);
		vocab.add(&PrimitiveForthWords::EQUAL);
		vocab.add(&PrimitiveForthWords::CONDITIONAL_AND);
		vocab.add(&PrimitiveForthWords::CONDITIONAL_OR);
		vocab.add(&PrimitiveForthWords::CONDITIONAL_NOT);
		vocab.add(&PrimitiveForthWords::ACCEPT_INPUT);
		vocab.add(&PrimitiveForthWords::PEEK_NEXT_INPUT_CHAR);
		vocab.add(&PrimitiveForthWords::GET_NEXT_INPUT_CHAR);
		vocab.add(&PrimitiveForthWords::PRINT_CHAR);
		vocab.add(&PrimitiveForthWords::FALSE);
		vocab.add(&PrimitiveForthWords::TRUE);
		vocab.add(&PrimitiveForthWords::ZERO);
		vocab.add(&PrimitiveForthWords::ONE);
		vocab.add(&PrimitiveForthWords::NEGATIVE_ONE);
		vocab.add(&PrimitiveForthWords::ADD_ONE);
		vocab.add(&PrimitiveForthWords::SUBTRACT_ONE);
		vocab.add(&PrimitiveForthWords::TRACE);

		vocab.add("strlen", &CoreForthWords::STRLEN);
		vocab.add("strcpy", &CoreForthWords::STRCPY);
		vocab.add("strreverse", &CoreForthWords::STRREVERSE);
		vocab.add("char2Int", &CoreForthWords::PARSE_DIGIT);
		vocab.add("str2Int", &CoreForthWords::PARSE_NUMBER);
		vocab.add("int2Str", &CoreForthWords::NUMBER_TO_CHARACERS);

		vocab.add("searchVocab", &VocabWords::SEARCH_VOCAB);
		vocab.add("sourceVocab", &VocabWords::SOURCE_VOCAB);
		vocab.add("destVocab", &VocabWords::DEST_VOCAB);
		vocab.add("addWordToVocab", &VocabWords::ADD_WORD_TO_VOCAB);

		vocab.add("nextToken", &BootstrapWords::NEXT_TOKEN);
		vocab.add("findWord", &BootstrapWords::FIND_WORD);
		vocab.add("printString", &BootstrapWords::PRINT_STRING);
		vocab.add("printNumber", &BootstrapWords::PRINT_NUMBER);
	}

	return vocab;
}