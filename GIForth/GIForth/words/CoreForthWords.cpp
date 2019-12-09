//
// Created by Dad on 9/27/19.
//

#include "runtime/utils/CompositeForthWordBuilder.h"
#include "runtime/CompositeForthWord.h"
#include "CoreForthWords.h"
#include "runtime/PrimitiveForthWords.h"

CoreForthWords::CoreForthWords(ForthVocab *next)
		: ForthVocab(next)
{
	add(&STRLEN());
	add(&STRCPY());
	add(&STRREVERSE());
	add(&PARSE_DIGIT());
	add(&PARSE_NUMBER());
	add(&NUMBER_TO_CHARACERS());
}

ForthWord& CoreForthWords::CURRENT_THREAD() {  // char* -- len
	static CompositeForthWord word(
			CompositeForthWordBuilder("CoreForthWords::currentThread")
					.compileConstant(&PrimitiveForthWords::registers[PrimitiveForthWords::THREAD_STATE])
					.build());
	return word;
}

/*
: strlen                ( char* -- len )
 0 >R
 while dup c@ do
    R> 1 + >R
    1 +
 endwhile
 drop
 R>
 ;
*/
ForthWord& CoreForthWords::STRLEN() {  // char* -- len
	static CompositeForthWord word(
			CompositeForthWordBuilder("CoreForthWords::strlen")
					.compileWord(&PrimitiveForthWords::ZERO())
					.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
					.compileWhile()
						.compileWord(&PrimitiveForthWords::DUP())
						.compileWord(&PrimitiveForthWords::CHAR_AT())
					.compileDo()
						.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
						.compileWord(&PrimitiveForthWords::ADD_ONE())
						.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
						.compileWord(&PrimitiveForthWords::ADD_ONE())
					.compileEndWhile()
					.compileWord(&PrimitiveForthWords::DROP())
					.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
					.build()
	);
	return word;
}

/*
: STRCPY                ( src* dest* -- )
    swap                ( dest* src* )
    while dup c@ do {   ( dest* src* )
        dup c@          ( dest* src* char )
        swap >R         ( dest* char ) ( src* )
        over c!         ( dest* ) ( src * )
        1 +             ( dest*+1 ) ( src* )
        R> 1 +          ( dest*+1 src*+1 )
    endwhile
    drop drop
 */
ForthWord& CoreForthWords::STRCPY() { // src* dest* --
	static CompositeForthWord word(
			CompositeForthWordBuilder("CoreForthWords::strcpy")
					.compileWord(&PrimitiveForthWords::SWAP())
					.compileWhile()
						.compileWord(&PrimitiveForthWords::DUP())
						.compileWord(&PrimitiveForthWords::CHAR_AT())
					.compileDo()
						.compileWord(&PrimitiveForthWords::DUP())
						.compileWord(&PrimitiveForthWords::CHAR_AT())
						.compileWord(&PrimitiveForthWords::SWAP())
						.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
						.compileWord(&PrimitiveForthWords::OVER())
						.compileWord(&PrimitiveForthWords::CHAR_PUT())
						.compileWord(&PrimitiveForthWords::ADD_ONE())
						.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
						.compileWord(&PrimitiveForthWords::ADD_ONE())
					.compileEndWhile()
					.compileWord(&PrimitiveForthWords::DROP())
					.compileWord(&PrimitiveForthWords::DROP())
					.build()
	);
	return word;
}

/**
src* dest* len --
    >R                  ( src* dest* ) ( len )
    swap                ( dest* src* ) ( len )
    while R> dup 0 > do ( dest* src* len ) ( )
        1 - >R          ( dest* src* ) ( len )
        dup >R c@       ( dest* char) ( len src* )
        over c!         ( dest* ) ( len src* )
        1 +             ( dest* ) ( len src* )
        R>              ( dest* src* ) ( len )
        1 +             ( dest* src* ) ( len )
    endwhile            ( dest* src* len )
    drop drop c!      	( )
 
CompositeForthWord CoreForthWords::STRNCPY(  // src start len dest
		CompositeForthWordBuilder("CoreForthWords::STRNCPY")
				.compileWord(&PrimitiveForthWords::TO_RETURN_STACK)
				.compileWord(&PrimitiveForthWords::SWAP)
				.compileWhile()
					.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK)
					.compileWord(&PrimitiveForthWords::DUP)
					.compileWord(&PrimitiveForthWords::ZERO)
					.compileWord(&PrimitiveForthWords::GREATER_THAN)
				.compileDo()
					.compileWord(&PrimitiveForthWords::ONE)
					.compileWord(&PrimitiveForthWords::SUBTRACT)
					.compileWord(&PrimitiveForthWords::TO_RETURN_STACK)
					.compileWord(&PrimitiveForthWords::DUP)
					.compileWord(&PrimitiveForthWords::TO_RETURN_STACK)
					.compileWord(&PrimitiveForthWords::CHAR_AT)
					.compileWord(&PrimitiveForthWords::OVER)
					.compileWord(&PrimitiveForthWords::CHAR_PUT)
					.compileWord(&PrimitiveForthWords::ADD_ONE)
					.compileWord(&PrimitiveForthWords::TO_RETURN_STACK)
					.compileWord(&PrimitiveForthWords::ADD_ONE)
				.compileEndWhile()
				.compileWord(&PrimitiveForthWords::DROP)
				.compileWord(&PrimitiveForthWords::DROP)
				.compileConstant(static_cast<ForthCell::CHAR_TYPE>('\0'))
				.compileWord(&PrimitiveForthWords::CHAR_PUT)
        .build()
);
*/

/*
: reverseString         ( str* -- )
    dup                 ( str* str* )
    0 >R                ( str* str* ) ( 0 )
    while dup c@ do     ( str* str* ) ( 0 )
        dup c@ >R       ( str* str* ) ( 0 char )
        1 +             ( str* str*+1 ) ( 0 char )
    endwhile            ( str* str*+n ) ( 0 char .. char )
    drop                ( str* ) ( 0 char .. char )
    while R> dup do     ( str* char ) ( 0 char .. char )
        over c!         ( str* ) ( 0 char .. char )
        1 +             ( str*+1 ) ( 0 char .. char )
    endwhile            ( str*+n ) ( )
	swap C!
;
*/

ForthWord& CoreForthWords::STRREVERSE() {
	static CompositeForthWord word(
		CompositeForthWordBuilder("CoreForthWords::strReverse")
			.compileWord(&PrimitiveForthWords::DUP())
			.compileWord(&PrimitiveForthWords::ZERO())
			.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
			.compileWhile()
				.compileWord(&PrimitiveForthWords::DUP())
				.compileWord(&PrimitiveForthWords::CHAR_AT())
			.compileDo()
				.compileWord(&PrimitiveForthWords::DUP())
				.compileWord(&PrimitiveForthWords::CHAR_AT())
				.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
				.compileWord(&PrimitiveForthWords::ADD_ONE())
			.compileEndWhile()
			.compileWord(&PrimitiveForthWords::DROP())
			.compileWhile()
				.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
				.compileWord(&PrimitiveForthWords::DUP())
			.compileDo()
				.compileWord(&PrimitiveForthWords::OVER())
				.compileWord(&PrimitiveForthWords::CHAR_PUT())
				.compileWord(&PrimitiveForthWords::ADD_ONE())
			.compileEndWhile()
			.compileWord(&PrimitiveForthWords::SWAP())
			.compileWord(&PrimitiveForthWords::CHAR_PUT())
			.build()
	);
	return word;
}

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
ForthWord& CoreForthWords::PARSE_DIGIT() {
	static CompositeForthWord word(
		CompositeForthWordBuilder("CoreForthWords::char2Int")
			.compileWord(&PrimitiveForthWords::DUP())
			.compileConstant(static_cast<ForthCell::CHAR_TYPE>('0'))
			.compileWord(&PrimitiveForthWords::LESS_THAN())
			.compileIf()
				.compileWord(&PrimitiveForthWords::DROP())
				.compileWord(&PrimitiveForthWords::NEGATIVE_ONE())
			.compileElse()
				.compileWord(&PrimitiveForthWords::DUP())
				.compileConstant(static_cast<ForthCell::CHAR_TYPE>('9'))
				.compileWord(&PrimitiveForthWords::GREATER_THAN())
				.compileIf()
					.compileWord(&PrimitiveForthWords::DROP())
					.compileWord(&PrimitiveForthWords::NEGATIVE_ONE())
				.compileElse()
					.compileConstant(static_cast<ForthCell::CHAR_TYPE>('0'))
					.compileWord(&PrimitiveForthWords::SUBTRACT())
	            .compileEndIf()
	        .compileEndIf()
		.build()
	);
	return word;
}

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
ForthWord& CoreForthWords::PARSE_NUMBER() {
	static CompositeForthWord word(
		CompositeForthWordBuilder("CoreForthWords::str2Int")
		.compileWord(&PrimitiveForthWords::DUP())
		.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
		.compileWord(&PrimitiveForthWords::ZERO())
		.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
		.compileWhile()
			.compileWord(&PrimitiveForthWords::DUP())
			.compileWord(&PrimitiveForthWords::CHAR_AT())
		.compileDo()
			.compileWord(&PrimitiveForthWords::DUP())
			.compileWord(&PrimitiveForthWords::CHAR_AT())
			.compileWord(&PARSE_DIGIT())
			.compileWord(&PrimitiveForthWords::DUP())
			.compileWord(&PrimitiveForthWords::ZERO())
			.compileWord(&PrimitiveForthWords::LESS_THAN())
			.compileIf()
				.compileWord(&PrimitiveForthWords::DROP())
				.compileWord(&PrimitiveForthWords::DROP())
				.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
				.compileWord(&PrimitiveForthWords::DROP())
				.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
				.compileWord(&PrimitiveForthWords::FALSE())
				.compileWord(&PrimitiveForthWords::RETURN())
			.compileElse()
				.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
				.compileConstant(static_cast<ForthCell::INT_TYPE>(10))
				.compileWord(&PrimitiveForthWords::MULTIPLY())
				.compileWord(&PrimitiveForthWords::ADD())
				.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
				.compileWord(&PrimitiveForthWords::ONE())
				.compileWord(&PrimitiveForthWords::ADD())
			.compileEndIf()
		.compileEndWhile()
		.compileWord(&PrimitiveForthWords::DROP())
		.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
		.compileWord(&PrimitiveForthWords::TRUE())
		.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
		.compileWord(&PrimitiveForthWords::DROP())
		.build()
	);
	return word;
}

/*
: NUMBER_TO_CHARS       ( value char* -- )
	over if
		dup >R >R           ( value )
		dup                 ( value value )
		not if              ( value )
			'0'             ( '0' )
			R@ c!           ( )
			R> 1 + >R       ( )
		else                ( value )
			dup 0 < if      ( value )
				'-'         ( value '-' )
				R@ c!       ( value )
				R> 1 + >R   ( value )
				-1 *        ( -value )
			endif           ( value )
			while           ( value )
				dup         ( value value )
			do	            ( value )
				dup         ( value value )
				10 mod      ( value value%10 )
				'0' +       ( value char )
				r@ c!       ( value )
				r> 1 + R>   ( value ) ( increment address )
				10 /        ( remain /= 10 )
			endwhile        ( remaining )
			drop            ( )
		endif               ( )
		0 r> c!             ( null terminate string )
		r> reverseString
	else					( value char* )
		swap drop			( char* )
		'0' over c!			( char* )
		1 + 0 swap c!       ( )
	endif
;
 */
ForthWord& CoreForthWords::NUMBER_TO_CHARACERS() {
	static CompositeForthWord word(
		CompositeForthWordBuilder("CoreForthWords::int2Str")
			.compileWord(&PrimitiveForthWords::OVER())
			.compileIf()
				.compileWord(&PrimitiveForthWords::DUP())
				.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
				.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
				.compileWord(&PrimitiveForthWords::DUP())
				.compileWord(&PrimitiveForthWords::CONDITIONAL_NOT())
				.compileIf()
					.compileWord(&PrimitiveForthWords::ZERO())
					.compileWord(&PrimitiveForthWords::AT_RETURN_STACK())
					.compileWord(&PrimitiveForthWords::CHAR_PUT())
					.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
					.compileWord(&PrimitiveForthWords::ADD_ONE())
					.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
				.compileElse()
					.compileWord(&PrimitiveForthWords::DUP())
					.compileWord(&PrimitiveForthWords::ZERO())
					.compileWord(&PrimitiveForthWords::LESS_THAN())
					.compileIf()
						.compileConstant(static_cast<ForthCell::CHAR_TYPE>('-'))
						.compileWord(&PrimitiveForthWords::AT_RETURN_STACK())
						.compileWord(&PrimitiveForthWords::CHAR_PUT())
						.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
						.compileWord(&PrimitiveForthWords::ADD_ONE())
						.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
						.compileWord(&PrimitiveForthWords::NEGATIVE_ONE())
						.compileWord(&PrimitiveForthWords::MULTIPLY())
					.compileEndIf()
					.compileWhile()
						.compileWord(&PrimitiveForthWords::DUP())
					.compileDo()
						.compileWord(&PrimitiveForthWords::DUP())
						.compileConstant(static_cast<ForthCell::INT_TYPE >(10))
						.compileWord(&PrimitiveForthWords::MOD())
						.compileConstant(static_cast<ForthCell::CHAR_TYPE>('0'))
						.compileWord(&PrimitiveForthWords::ADD())
						.compileWord(&PrimitiveForthWords::AT_RETURN_STACK())
						.compileWord(&PrimitiveForthWords::CHAR_PUT())
						.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
						.compileWord(&PrimitiveForthWords::ADD_ONE())
						.compileWord(&PrimitiveForthWords::TO_RETURN_STACK())
						.compileConstant(static_cast<ForthCell::INT_TYPE >(10))
						.compileWord(&PrimitiveForthWords::DIVIDE())
					.compileEndWhile()
					.compileWord(&PrimitiveForthWords::DROP())
				.compileEndIf()
				.compileWord(&PrimitiveForthWords::ZERO())
				.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
				.compileWord(&PrimitiveForthWords::CHAR_PUT())
				.compileWord(&PrimitiveForthWords::FROM_RETURN_STACK())
				.compileWord(&STRREVERSE())
			.compileElse()
				.compileWord(&PrimitiveForthWords::SWAP())
				.compileWord(&PrimitiveForthWords::DROP())
				.compileConstant(static_cast<ForthCell::CHAR_TYPE>('0'))
				.compileWord(&PrimitiveForthWords::OVER())
				.compileWord(&PrimitiveForthWords::CHAR_PUT())
				.compileWord(&PrimitiveForthWords::ADD_ONE())
				.compileWord(&PrimitiveForthWords::ZERO())
				.compileWord(&PrimitiveForthWords::OVER())
				.compileWord(&PrimitiveForthWords::CHAR_PUT())
			.compileEndIf()
		.build()
	);
	return word;
}
