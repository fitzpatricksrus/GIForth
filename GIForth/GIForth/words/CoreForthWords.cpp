//
// Created by Dad on 9/27/19.
//

#include "words/bootstrap/CompositeForthWordBuilder.h"
#include "runtime/CompositeForthWord.h"
#include "CoreForthWords.h"
#include "PrimitiveForthWords.h"

/*
: parse_digit				( char -- value | -1 )
 	dup '0' < if
 		drop
 		-1
	else
 		dup '9' > if
 			drop
			-1
		else
			'0' -
		endif
	endif
 ;
 */
CompositeForthWord CoreForthWords::PARSE_DIGIT(
		CompositeForthWordBuilder("CoreForthWords::PARSE_DIGIT")
			.append(&PrimitiveForthWords::DUP)
			.compileConstant(static_cast<ForthCell::CHAR_TYPE>('0'))
			.append(&PrimitiveForthWords::LESS_THAN)
			.compileIfLink()
				.append(&PrimitiveForthWords::DROP)
				.compileConstant(static_cast<ForthCell::INT_TYPE>(-1))
			.compileElseLink()
				.append(&PrimitiveForthWords::DUP)
				.compileConstant(static_cast<ForthCell::CHAR_TYPE>('9'))
				.append(&PrimitiveForthWords::GREATER_THAN)
				.compileIfLink()
					.append(&PrimitiveForthWords::DROP)
					.compileConstant(static_cast<ForthCell::INT_TYPE>(-1))
				.compileElseLink()
					.compileConstant(static_cast<ForthCell::CHAR_TYPE>('0'))
					.append(&PrimitiveForthWords::SUBTRACT)
				.compileEndIfLink()
			.compileEndIfLink()
		.build()
	);

/*
 : parse_positive_number	// stringAddr -- [ value true | stringAddr false ]
 	dup >R					// (save original strAddr)
 	0 >R
	while dup c@ do		// strAddr
 		dup c@ parse_digit	// strAddr (value | -1)
 		dup 0 < if			// strAddr (value | -1)
 			drop drop		//
 			R> drop			//	(drop sum)
 			R>				//	strAddr (restore strAddr)
 			false			//  strAddr false
 			return
		else				// strAddr value
			R> 10 * + >R	// strAddr
			1 +				// strAddr++
		endif				// strAddr++
	endwhile				// strAddr++
 	drop					//
 	R>						// value
 	true					// value true
 	R> drop					// value true (drop original strAddr)
 */
CompositeForthWord CoreForthWords::PARSE_NUMBER(
		CompositeForthWordBuilder("CoreForthWords::PARSE_NUMBER")
		.append(&PrimitiveForthWords::DUP)
				.append(&PrimitiveForthWords::TO_RETURN_STACK)
				.append(&PrimitiveForthWords::PUSH_NEXT_CELL)
		.append(ForthCell(static_cast<ForthCell::INT_TYPE>(0)))
		.append(&PrimitiveForthWords::TO_RETURN_STACK)
		.compileWhileLink()
				.append(&PrimitiveForthWords::DUP)
				.append(&PrimitiveForthWords::CHAR_AT)
		.compileDoLink()
				.append(&PrimitiveForthWords::DUP)
				.append(&PrimitiveForthWords::CHAR_AT)
				.append(&PARSE_DIGIT)
				.append(&PrimitiveForthWords::DUP)
				.append(&PrimitiveForthWords::PUSH_NEXT_CELL)
				.append(ForthCell(static_cast<ForthCell::INT_TYPE>(0)))
				.append(&PrimitiveForthWords::LESS_THAN)
				.compileIfLink()
						.append(&PrimitiveForthWords::DROP)
						.append(&PrimitiveForthWords::DROP)
						.append(&PrimitiveForthWords::FROM_RETURN_STACK)
						.append(&PrimitiveForthWords::DROP)
						.append(&PrimitiveForthWords::FROM_RETURN_STACK)
						.append(&PrimitiveForthWords::PUSH_NEXT_CELL)
						.append(ForthCell(static_cast<ForthCell::BOOL_TYPE>(false)))
						.append(&PrimitiveForthWords::RETURN)
				.compileElseLink()
						.append(&PrimitiveForthWords::FROM_RETURN_STACK)
						.append(&PrimitiveForthWords::PUSH_NEXT_CELL)
						.append(ForthCell(static_cast<ForthCell::INT_TYPE>(10)))
						.append(&PrimitiveForthWords::MULTIPLY)
						.append(&PrimitiveForthWords::ADD)
						.append(&PrimitiveForthWords::TO_RETURN_STACK)
						.append(&PrimitiveForthWords::PUSH_NEXT_CELL)
						.append(ForthCell(static_cast<ForthCell::INT_TYPE>(1)))
						.append(&PrimitiveForthWords::ADD)
				.compileEndIfLink()
		.compileEndWhileLink()
		.append(&PrimitiveForthWords::DROP)
		.append(&PrimitiveForthWords::FROM_RETURN_STACK)
		.append(&PrimitiveForthWords::PUSH_NEXT_CELL)
		.append(ForthCell(static_cast<ForthCell::BOOL_TYPE>(true)))
		.append(&PrimitiveForthWords::FROM_RETURN_STACK)
		.append(&PrimitiveForthWords::DROP)
		.build()
);