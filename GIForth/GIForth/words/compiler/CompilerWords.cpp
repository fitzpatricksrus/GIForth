#include <runtime/CompositeForthWord.h>
#include <runtime/utils/CompositeForthWordBuilder.h>
#include "CompilerWords.h"

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
 		nextToken findWord not if
 			// not in standard vocab, so search compiler vocab
 			CompilerWords searchWord not if
				compileEnd freeWord
				printString '?' printChar 13 printChar
				false
				return
			else
				execute
			endif
		else
			compileTOS
		endif
	forever
 	;
*/
static CompositeForthWord F_COLON(
		CompositeForthWordBuilder("CompilerWords::COLON")
				.build());
ForthWord& CompilerWords::COLON = F_COLON;

/*
: ;
	compileEnd
 	r> drop
 	true
 	return
 	;

 */static CompositeForthWord F_SEMICOLON(
		CompositeForthWordBuilder("CompilerWords::SEMICOLON")
				.build());
ForthWord& CompilerWords::SEMICOLON = F_SEMICOLON;
