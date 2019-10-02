//
// Created by Dad on 9/27/19.
//

#include "words/bootstrap/CompositeForthWordBuilder.h"
#include "runtime/CompositeForthWord.h"
#include "CoreForthWords.h"
#include "PrimitiveForthWords.h"

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
                .append(&PrimitiveForthWords::ZERO)
                .append(&PrimitiveForthWords::TO_RETURN_STACK)
                .compileWhileLink()
                .append(&PrimitiveForthWords::DUP)
                .append(&PrimitiveForthWords::CHAR_AT)
                .compileDoLink()
                .append(&PrimitiveForthWords::FROM_RETURN_STACK)
                .append(&PrimitiveForthWords::ADD_ONE)
                .append(&PrimitiveForthWords::TO_RETURN_STACK)
                .append(&PrimitiveForthWords::ADD_ONE)
                .compileEndWhileLink()
                .append(&PrimitiveForthWords::DROP)
                .append(&PrimitiveForthWords::FROM_RETURN_STACK)
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
        .append(&PrimitiveForthWords::SWAP)
        .compileWhileLink()
                .append(&PrimitiveForthWords::DUP)
                .append(&PrimitiveForthWords::CHAR_AT)
        .compileDoLink()
                .append(&PrimitiveForthWords::DUP)
                .append(&PrimitiveForthWords::CHAR_AT)
                .append(&PrimitiveForthWords::SWAP)
                .append(&PrimitiveForthWords::TO_RETURN_STACK)
                .append(&PrimitiveForthWords::OVER)
                .append(&PrimitiveForthWords::CHAR_PUT)
                .append(&PrimitiveForthWords::ADD_ONE)
                .append(&PrimitiveForthWords::FROM_RETURN_STACK)
                .append(&PrimitiveForthWords::ADD_ONE)
        .compileEndWhileLink()
        .append(&PrimitiveForthWords::DROP)
        .append(&PrimitiveForthWords::DROP)
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
    endwhile            ( desr* src* len )
    drop drop drop      ( )
 */
CompositeForthWord CoreForthWords::STRNCPY(  // src start len dest
        CompositeForthWordBuilder("CoreForthWords::STRNCPY")
        .append(&PrimitiveForthWords::TO_RETURN_STACK)
        .append(&PrimitiveForthWords::SWAP)
        .compileWhileLink()
            .append(&PrimitiveForthWords::FROM_RETURN_STACK)
            .append(&PrimitiveForthWords::DUP)
            .append(&PrimitiveForthWords::ZERO)
            .append(&PrimitiveForthWords::GREATER_THAN)
        .compileDoLink()
            .append(&PrimitiveForthWords::ONE)
            .append(&PrimitiveForthWords::SUBTRACT)
            .append(&PrimitiveForthWords::TO_RETURN_STACK)
            .append(&PrimitiveForthWords::DUP)
            .append(&PrimitiveForthWords::TO_RETURN_STACK)
            .append(&PrimitiveForthWords::CHAR_AT)
            .append(&PrimitiveForthWords::OVER)
            .append(&PrimitiveForthWords::CHAR_PUT)
            .append(&PrimitiveForthWords::ADD_ONE)
            .append(&PrimitiveForthWords::TO_RETURN_STACK)
            .append(&PrimitiveForthWords::ADD_ONE)
        .compileEndWhileLink()
        .append(&PrimitiveForthWords::DROP)
        .append(&PrimitiveForthWords::DROP)
        .append(&PrimitiveForthWords::DROP)
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
			.append(&PrimitiveForthWords::DUP)
			.compileConstant(static_cast<ForthCell::CHAR_TYPE>('0'))
			.append(&PrimitiveForthWords::LESS_THAN)
			.compileIfLink()
				.append(&PrimitiveForthWords::DROP)
				.append(&PrimitiveForthWords::NEGATIVE_ONE)
			.compileElseLink()
				.append(&PrimitiveForthWords::DUP)
				.compileConstant(static_cast<ForthCell::CHAR_TYPE>('9'))
				.append(&PrimitiveForthWords::GREATER_THAN)
				.compileIfLink()
					.append(&PrimitiveForthWords::DROP)
					.append(&PrimitiveForthWords::NEGATIVE_ONE)
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
		.append(&PrimitiveForthWords::ZERO)
		.append(&PrimitiveForthWords::TO_RETURN_STACK)
		.compileWhileLink()
				.append(&PrimitiveForthWords::DUP)
				.append(&PrimitiveForthWords::CHAR_AT)
		.compileDoLink()
				.append(&PrimitiveForthWords::DUP)
				.append(&PrimitiveForthWords::CHAR_AT)
				.append(&PARSE_DIGIT)
				.append(&PrimitiveForthWords::DUP)
				.append(&PrimitiveForthWords::ZERO)
				.append(&PrimitiveForthWords::LESS_THAN)
				.compileIfLink()
						.append(&PrimitiveForthWords::DROP)
						.append(&PrimitiveForthWords::DROP)
						.append(&PrimitiveForthWords::FROM_RETURN_STACK)
						.append(&PrimitiveForthWords::DROP)
						.append(&PrimitiveForthWords::FROM_RETURN_STACK)
						.append(&PrimitiveForthWords::FALSE)
						.append(&PrimitiveForthWords::RETURN)
				.compileElseLink()
						.append(&PrimitiveForthWords::FROM_RETURN_STACK)
						.append(&PrimitiveForthWords::PUSH_NEXT_CELL)
						.append(ForthCell(static_cast<ForthCell::INT_TYPE>(10)))
						.append(&PrimitiveForthWords::MULTIPLY)
						.append(&PrimitiveForthWords::ADD)
						.append(&PrimitiveForthWords::TO_RETURN_STACK)
						.append(&PrimitiveForthWords::ONE)
						.append(&PrimitiveForthWords::ADD)
				.compileEndIfLink()
		.compileEndWhileLink()
		.append(&PrimitiveForthWords::DROP)
		.append(&PrimitiveForthWords::FROM_RETURN_STACK)
		.append(&PrimitiveForthWords::TRUE)
		.append(&PrimitiveForthWords::FROM_RETURN_STACK)
		.append(&PrimitiveForthWords::DROP)
		.build()
);



/*
: reverseString         ( str* -- )
    dup                 ( str* str* )
    0 >R                ( str* str* ) ( 0 )
    while dup c@ do     ( str* str* )
        dup c@ >R       ( str* str* ) ( char 0 )
        1 +             ( str* str*+1 ) ( char 0 )
    endwhile            ( str* str*+n ) ( char .. char 0 )
    drop                ( str* ) ( char .. char 0 )
    while R> dup do     ( str* char ) ( char .. char 0 )
        over c!         ( str* ) ( char .. char 0 )
        1 +             ( str*+1 ) ( char .. char 0 )
    endwhile            ( str*+n ) ( )
    drop                ( ) ( )
;
*/

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

