#include "CompilerWords.h"

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
	add("compileWord", &COMPILE_WORD);
	add(":", &COLON);
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
		else
			findWord if
				compileTOS
			else
				CompilerWords searchVocab if
					execute
				else
					compileEnd freeWord
					printString '?' printChar 13 printChar
					false
					return
				endif
			endif
		endif
	forever
 	;
*/
static CompositeForthWord F_COMPILE_WORD(
		CompositeForthWordBuilder("CompilerWords::COMPILE_WORD")
			.compileWord(&BootstrapWords::NEXT_TOKEN)							// -- char*
			.compileWord(&CompositeForthWordWords::COMPILE_BEGIN)				// char* --
			.compileRepeat()														// --
				.compileWord(&BootstrapWords::NEXT_TOKEN)						// -- char*
				.compileWord(&CoreForthWords::PARSE_NUMBER)						// char* -- [ value true | char* false ]
				.compileIf()													// [ value true | char* false ] = [ value | char* ]
					.compilePtr(&PrimitiveForthWords::PUSH_NEXT_CELL)			// value -- value &PUSH_NEXT_CELL
					.compileWord(&CompositeForthWordWords::COMPILE_TOS)			// value &PUSH_NEXT_CELL --	value
					.compileWord(&CompositeForthWordWords::COMPILE_TOS)			// value --
				.compileElse()
					.compileWord(&BootstrapWords::FIND_WORD)					// char* -- [ word true | char* false ]
					.compileIf()												// [ word true | char* false ] -- [ word | char* ]
						.compileWord(&CompositeForthWordWords::COMPILE_TOS)		// word --
					.compileElse()
						.compilePtr(CompilerWords::getCompilerVocabInstance())	// char* -- char* vocab
						.compileWord(&VocabWords::SEARCH_VOCAB)					// char* vocab -- [ word true | char* false ]
						.compileIf()											// [ word false | char* true ] -- [ word | char* ]
							.compileCell(&PrimitiveForthWords::EXECUTE)			// word --
						.compileElse()
							.compileWord(&CompositeForthWordWords::COMPILE_END)	// char* -- char*
							.compileWord(&CompositeForthWordWords::FREE_WORD)	// char* -- char*
							.compileWord(&BootstrapWords::PRINT_STRING)			// char* --
							.compileInt('?')
							.compileWord(&PrimitiveForthWords::PRINT_CHAR)
							.compileInt('\n')
							.compileCell(&PrimitiveForthWords::PRINT_CHAR)
							.compileWord(&PrimitiveForthWords::FALSE)			// -- false
							.compileWord(&PrimitiveForthWords::RETURN)
						.compileEndIf()
					.compileEndIf()
				.compileEndIf()
			.compileForever()
			.build());
ForthWord& CompilerWords::COMPILE_WORD = F_COMPILE_WORD;

static CompositeForthWord F_COLON(
		CompositeForthWordBuilder("CompilerWords::COLON")
		.compileWord(&F_COMPILE_WORD)
		.compileIf()
			.compileWord(&VocabWords::DEST_VOCAB)
			.compileWord(&VocabWords::ADD_WORD_TO_VOCAB)
		.compileEndIf()
		.build()
);
ForthWord& CompilerWords::COLON = F_COLON;

/*
: ;
	compileEnd
 	r> drop
 	true
 	return
 	;

 */
 static CompositeForthWord SEMICOLON(
		CompositeForthWordBuilder("CompilerWords::SEMICOLON")
			.compileWord(&CompositeForthWordWords::COMPILE_END)
			.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK)		//TODO: this needs to change trace indent somehow
			.compileWord(&PrimitiveForthWords::DROP)
			.compileWord(&PrimitiveForthWords::TRUE)
			.compileWord(&PrimitiveForthWords::RETURN)
			.build());
ForthVocab* CompilerWords::getCompilerVocabInstance() {
	static ForthVocab words(nullptr);
	static bool addCompilerWords = true;
	if (addCompilerWords) {
		words.add(";", &SEMICOLON);
		addCompilerWords = false;
	}
	return &words;
}

