#include "CompilerWords.h"
#include "CompilerImmediateVocab.h"
#include "CompilerDeferredVocab.h"

#include <runtime/ForthWord.h>
#include <runtime/CompositeForthWord.h>
#include <runtime/utils/CompositeForthWordBuilder.h>
#include <runtime/CompositeForthWordWords.h>
#include <runtime/PrimitiveForthWords.h>
#include <words/interpreter/BootstrapWords.h>
#include <words/VocabWords.h>
#include <words/CoreForthWords.h>

CompilerWords::CompilerWords(ForthVocab* parent)
: ForthVocab(parent)
{
	add(&COMPILE_WORD());
	add(":", &COLON());
}

/*
: :
	compile if
		CurrentVocab
		addToVocab
	endif
 	;

: compileWord	( -- word true | false)
 	// get word name
 	nextToken
 	// start compiling
 	compileBegin
	do
 		nextToken str2Int if
			(PUSH_NEXT_CELL) (PUSH_NEXT_CELL) compileTOS
			compileTOS
			true
		else
			findWord if
				compileTOS
				true
			else
				CompilerWords searchVocab if
					execute
				else
					compileEnd freeWord
					printString '?' printChar 13 printChar
					false
					false
				endif
			endif
		endif
	until
 	;
*/
ForthWord& CompilerWords::COMPILE_WORD() {
	static CompositeForthWord word(
		CompositeForthWordBuilder("CompilerWords::compileWord")
			.compileWord(&BootstrapWords::NEXT_TOKEN())							// -- char*
			.compileWord(&CompositeForthWordWords::COMPILE_BEGIN())             // char* --
			.compileRepeat()                                                    // --
				.compileWord(&BootstrapWords::NEXT_TOKEN())						// -- char*
				.compileWord(&CoreForthWords::PARSE_NUMBER())					// char* -- [ value true | char* false ]
				.compileIf()                                                    // [ value true | char* false ] = [ value | char* ]
					.compilePtr(&PrimitiveForthWords::PUSH_NEXT_CELL())			// value -- value &PUSH_NEXT_CELL
					.compileWord(&CompositeForthWordWords::COMPILE_TOS())       // value &PUSH_NEXT_CELL --	value
					.compileWord(&CompositeForthWordWords::COMPILE_TOS())       // value --
					.compileWord(&PrimitiveForthWords::TRUE())
				.compileElse()
					.compileWord(&BootstrapWords::FIND_WORD())					// char* -- [ word true | char* false ]
					.compileIf()                                                // [ word true | char* false ] -- [ word | char* ]
						.compileWord(&CompositeForthWordWords::COMPILE_TOS())   // word --
						.compileWord(&PrimitiveForthWords::TRUE())
					.compileElse()
						.compilePtr(&CompilerImmediateVocab::getInstance())     // char* -- char* vocab
						.compileWord(&VocabWords::SEARCH_VOCAB())				// char* vocab -- [ word true | char* false ]
						.compileIf()                                            // [ word false | char* true ] -- [ word | char* ]
							.compileCell(&PrimitiveForthWords::EXECUTE())		// word --
						.compileElse()
							.compilePtr(&CompilerDeferredVocab::getInstance())
							.compileWord(&VocabWords::SEARCH_VOCAB())
							.compileIf()
								.compileWord(&CompositeForthWordWords::COMPILE_TOS())
								.compileWord(&PrimitiveForthWords::TRUE())
							.compileElse()
								.compileWord(&CompositeForthWordWords::COMPILE_END()) // char* -- char*
								.compileWord(&CompositeForthWordWords::FREE_WORD())	// char* -- char*
								.compileWord(&BootstrapWords::PRINT_STRING())		// char* --
								.compileInt('?')
								.compileWord(&PrimitiveForthWords::PRINT_CHAR())
								.compileInt('\n')
								.compileWord(&PrimitiveForthWords::PRINT_CHAR())
								.compileInt('\r')
								.compileWord(&PrimitiveForthWords::PRINT_CHAR())
								.compileWord(&PrimitiveForthWords::FLUSH_INPUT())
								.compileWord(&PrimitiveForthWords::FALSE())			// -- result of compile
								.compileWord(&PrimitiveForthWords::FALSE())			// -- cause compile to exit
							.compileEndIf()
						.compileEndIf()
					.compileEndIf()
				.compileEndIf()
				.compileWord(&PrimitiveForthWords::CONDITIONAL_NOT())
			.compileUntil()
			.build());
	return word;
}

ForthWord& CompilerWords::COLON() {
	static CompositeForthWord word(
		CompositeForthWordBuilder("CompilerWords::COLON")
		.compileWord(&COMPILE_WORD())
		.compileIf()
			.compileWord(&VocabWords::DEST_VOCAB())
			.compileWord(&VocabWords::ADD_WORD_TO_VOCAB())
		.compileEndIf()
		.build()
	);
	return word;
}
