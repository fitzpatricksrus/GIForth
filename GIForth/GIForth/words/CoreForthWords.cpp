//
// Created by Dad on 9/27/19.
//

#include "words/bootstrap/CompositeForthWordBuilder.h"
#include "runtime/CompositeForthWord.h"
#include "CoreForthWords.h"
#include "PrimitiveForthWords.h"

CoreForthWords::CoreForthWords(ForthVocab *next)
		: BasicForthVocab(next)
{
	add(&STRLEN);
	add(&STRCPY);
	add(&STRREVERSE);
	add(&PARSE_DIGIT);
	add(&PARSE_NUMBER);
	add(&NUMBER_TO_CHARACERS);
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
CompositeForthWord CoreForthWords::STRLEN(  // char* -- len
		CompositeForthWordBuilder("CoreForthWords::STRLEN")
				.compileCell(&PrimitiveForthWords::ZERO)
				.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
				.compileWhile()
					.compileCell(&PrimitiveForthWords::DUP)
					.compileCell(&PrimitiveForthWords::CHAR_AT)
				.compileDo()
					.compileCell(&PrimitiveForthWords::FROM_RETURN_STACK)
					.compileCell(&PrimitiveForthWords::ADD_ONE)
					.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
					.compileCell(&PrimitiveForthWords::ADD_ONE)
				.compileEndWhile()
				.compileCell(&PrimitiveForthWords::DROP)
				.compileCell(&PrimitiveForthWords::FROM_RETURN_STACK)
        .build()
);

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
CompositeForthWord CoreForthWords::STRCPY(  // src* dest* --
		CompositeForthWordBuilder("CoreForthWords::STRCPY")
				.compileCell(&PrimitiveForthWords::SWAP)
				.compileWhile()
					.compileCell(&PrimitiveForthWords::DUP)
					.compileCell(&PrimitiveForthWords::CHAR_AT)
				.compileDo()
					.compileCell(&PrimitiveForthWords::DUP)
					.compileCell(&PrimitiveForthWords::CHAR_AT)
					.compileCell(&PrimitiveForthWords::SWAP)
					.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
					.compileCell(&PrimitiveForthWords::OVER)
					.compileCell(&PrimitiveForthWords::CHAR_PUT)
					.compileCell(&PrimitiveForthWords::ADD_ONE)
					.compileCell(&PrimitiveForthWords::FROM_RETURN_STACK)
					.compileCell(&PrimitiveForthWords::ADD_ONE)
				.compileEndWhile()
				.compileCell(&PrimitiveForthWords::DROP)
				.compileCell(&PrimitiveForthWords::DROP)
        .build()
);

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
				.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
				.compileCell(&PrimitiveForthWords::SWAP)
				.compileWhile()
					.compileCell(&PrimitiveForthWords::FROM_RETURN_STACK)
					.compileCell(&PrimitiveForthWords::DUP)
					.compileCell(&PrimitiveForthWords::ZERO)
					.compileCell(&PrimitiveForthWords::GREATER_THAN)
				.compileDo()
					.compileCell(&PrimitiveForthWords::ONE)
					.compileCell(&PrimitiveForthWords::SUBTRACT)
					.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
					.compileCell(&PrimitiveForthWords::DUP)
					.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
					.compileCell(&PrimitiveForthWords::CHAR_AT)
					.compileCell(&PrimitiveForthWords::OVER)
					.compileCell(&PrimitiveForthWords::CHAR_PUT)
					.compileCell(&PrimitiveForthWords::ADD_ONE)
					.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
					.compileCell(&PrimitiveForthWords::ADD_ONE)
				.compileEndWhile()
				.compileCell(&PrimitiveForthWords::DROP)
				.compileCell(&PrimitiveForthWords::DROP)
				.compileConstant(static_cast<ForthCell::CHAR_TYPE>('\0'))
				.compileCell(&PrimitiveForthWords::CHAR_PUT)
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

CompositeForthWord CoreForthWords::STRREVERSE(
		CompositeForthWordBuilder("CoreForthWords::STR_REVERSE")
				.compileCell(&PrimitiveForthWords::DUP)
				.compileCell(&PrimitiveForthWords::ZERO)
				.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
				.compileWhile()
					.compileCell(&PrimitiveForthWords::DUP)
					.compileCell(&PrimitiveForthWords::CHAR_AT)
				.compileDo()
					.compileCell(&PrimitiveForthWords::DUP)
					.compileCell(&PrimitiveForthWords::CHAR_AT)
					.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
					.compileCell(&PrimitiveForthWords::ADD_ONE)
				.compileEndWhile()
				.compileCell(&PrimitiveForthWords::DROP)
				.compileWhile()
					.compileCell(&PrimitiveForthWords::FROM_RETURN_STACK)
					.compileCell(&PrimitiveForthWords::DUP)
				.compileDo()
					.compileCell(&PrimitiveForthWords::OVER)
					.compileCell(&PrimitiveForthWords::CHAR_PUT)
					.compileCell(&PrimitiveForthWords::ADD_ONE)
				.compileEndWhile()
				.compileCell(&PrimitiveForthWords::SWAP)
				.compileCell(&PrimitiveForthWords::CHAR_PUT)
				.build()
);

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
			.compileCell(&PrimitiveForthWords::DUP)
			.compileConstant(static_cast<ForthCell::CHAR_TYPE>('0'))
			.compileCell(&PrimitiveForthWords::LESS_THAN)
			.compileIf()
				.compileCell(&PrimitiveForthWords::DROP)
				.compileCell(&PrimitiveForthWords::NEGATIVE_ONE)
			.compileElse()
				.compileCell(&PrimitiveForthWords::DUP)
				.compileConstant(static_cast<ForthCell::CHAR_TYPE>('9'))
				.compileCell(&PrimitiveForthWords::GREATER_THAN)
				.compileIf()
					.compileCell(&PrimitiveForthWords::DROP)
					.compileCell(&PrimitiveForthWords::NEGATIVE_ONE)
				.compileElse()
					.compileConstant(static_cast<ForthCell::CHAR_TYPE>('0'))
					.compileCell(&PrimitiveForthWords::SUBTRACT)
	            .compileEndIf()
	        .compileEndIf()
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
				.compileCell(&PrimitiveForthWords::DUP)
				.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
				.compileCell(&PrimitiveForthWords::ZERO)
				.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
				.compileWhile()
					.compileCell(&PrimitiveForthWords::DUP)
					.compileCell(&PrimitiveForthWords::CHAR_AT)
				.compileDo()
					.compileCell(&PrimitiveForthWords::DUP)
					.compileCell(&PrimitiveForthWords::CHAR_AT)
					.compileCell(&PARSE_DIGIT)
					.compileCell(&PrimitiveForthWords::DUP)
					.compileCell(&PrimitiveForthWords::ZERO)
					.compileCell(&PrimitiveForthWords::LESS_THAN)
					.compileIf()
						.compileCell(&PrimitiveForthWords::DROP)
						.compileCell(&PrimitiveForthWords::DROP)
						.compileCell(&PrimitiveForthWords::FROM_RETURN_STACK)
						.compileCell(&PrimitiveForthWords::DROP)
						.compileCell(&PrimitiveForthWords::FROM_RETURN_STACK)
						.compileCell(&PrimitiveForthWords::FALSE)
						.compileCell(&PrimitiveForthWords::RETURN)
					.compileElse()
						.compileCell(&PrimitiveForthWords::FROM_RETURN_STACK)
						.compileConstant(static_cast<ForthCell::INT_TYPE>(10))
						.compileCell(&PrimitiveForthWords::MULTIPLY)
						.compileCell(&PrimitiveForthWords::ADD)
						.compileCell(&PrimitiveForthWords::TO_RETURN_STACK)
						.compileCell(&PrimitiveForthWords::ONE)
						.compileCell(&PrimitiveForthWords::ADD)
					.compileEndIf()
				.compileEndWhile()
				.compileCell(&PrimitiveForthWords::DROP)
				.compileCell(&PrimitiveForthWords::FROM_RETURN_STACK)
				.compileCell(&PrimitiveForthWords::TRUE)
				.compileCell(&PrimitiveForthWords::FROM_RETURN_STACK)
				.compileCell(&PrimitiveForthWords::DROP)
		.build()
);

/*
: NUMBER_TO_CHARS       ( value char* -- )
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
        begin           ( value )
            dup         ( value value )
        while           ( value )
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
;
 */
CompositeForthWord CoreForthWords::NUMBER_TO_CHARACERS(
        CompositeForthWordBuilder("CoreForthWords::NUMBER_TO_CHARACERS")
        .build());

