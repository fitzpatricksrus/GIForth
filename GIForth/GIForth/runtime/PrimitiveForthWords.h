//
// Created by Dad on 9/17/19.
//

#ifndef GIFORTH_PRIMITIVEFORTHWORDS_H
#define GIFORTH_PRIMITIVEFORTHWORDS_H

#include "runtime/ForthVocab.h"
#include "runtime/utils/PrimitiveForthWordFunction.h"
#include "runtime/ForthCell.h"

class PrimitiveForthWords : public ForthVocab {
public:
	explicit PrimitiveForthWords(ForthVocab* next);
	PrimitiveForthWords(const PrimitiveForthWords& other) = default;
	~PrimitiveForthWords() override = default;

    static PrimitiveForthWordFunction NOP;

	// --
	static PrimitiveForthWordFunction JUMP;

	// bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
	static PrimitiveForthWordFunction JUMP_IF_FALSE;

	// --
	static PrimitiveForthWordFunction RETURN;
	static PrimitiveForthWordFunction EXIT_THREAD;

	// wordAddr --
	static PrimitiveForthWordFunction EXECUTE;

	// -- value ; pushes next cell in word onto data stack
	static PrimitiveForthWordFunction PUSH_NEXT_CELL;

	static PrimitiveForthWordFunction CHAR_SIZE;
    static PrimitiveForthWordFunction INT_SIZE;
    static PrimitiveForthWordFunction PTR_SIZE;
    static PrimitiveForthWordFunction WORD_SIZE;

    static PrimitiveForthWordFunction ALLOC;
    static PrimitiveForthWordFunction FREE;

    static PrimitiveForthWordFunction CHAR_AT;          // addr - char
    static PrimitiveForthWordFunction CHAR_PUT;         // char addr --
    static PrimitiveForthWordFunction CHAR_INDEX;       // ndx addr -- addr
    static PrimitiveForthWordFunction INT_AT;           // addr - char
    static PrimitiveForthWordFunction INT_PUT;			// char addr --
    static PrimitiveForthWordFunction INT_INDEX;		// ndx addr -- addr
    static PrimitiveForthWordFunction CELL_AT;          // addr -- cell
    static PrimitiveForthWordFunction CELL_PUT;         // value addr --
    static PrimitiveForthWordFunction CELL_INDEX;       // ndx addr -- addr

    static PrimitiveForthWordFunction TO_RETURN_STACK;  // >R
    static PrimitiveForthWordFunction FROM_RETURN_STACK; // R>
    static PrimitiveForthWordFunction AT_RETURN_STACK;  // R> dup >R

    static PrimitiveForthWordFunction SWAP;	// ( a b -- b a )
    static PrimitiveForthWordFunction PICK;	// ( a0 .. an x -- a0 .. an ax )
    static PrimitiveForthWordFunction OVER;	// ( a b -- a b a )
    static PrimitiveForthWordFunction ROLL;	// ( a0 .. an n -- a1 .. an a0 )
    static PrimitiveForthWordFunction DROP;
    static PrimitiveForthWordFunction DUP;

    static PrimitiveForthWordFunction ADD;
    static PrimitiveForthWordFunction SUBTRACT;
    static PrimitiveForthWordFunction MULTIPLY;
    static PrimitiveForthWordFunction DIVIDE;
    static PrimitiveForthWordFunction MOD;

    static PrimitiveForthWordFunction LESS_THAN;
    static PrimitiveForthWordFunction GREATER_THAN;
    static PrimitiveForthWordFunction EQUAL;

    static PrimitiveForthWordFunction CONDITIONAL_AND;
    static PrimitiveForthWordFunction CONDITIONAL_OR;
    static PrimitiveForthWordFunction CONDITIONAL_NOT;

    static PrimitiveForthWordFunction ACCEPT_INPUT;     // charPtr size -- inputSize
    static PrimitiveForthWordFunction PEEK_NEXT_INPUT_CHAR;
	static PrimitiveForthWordFunction GET_NEXT_INPUT_CHAR;
	static PrimitiveForthWordFunction FLUSH_INPUT;
    static PrimitiveForthWordFunction PRINT_CHAR;

    static PrimitiveForthWordFunction FALSE;
    static PrimitiveForthWordFunction TRUE;
    static PrimitiveForthWordFunction ZERO;
    static PrimitiveForthWordFunction ONE;
    static PrimitiveForthWordFunction NEGATIVE_ONE;
    static PrimitiveForthWordFunction ADD_ONE;
    static PrimitiveForthWordFunction SUBTRACT_ONE;

	static PrimitiveForthWordFunction REGISTER;
    enum THREAD_STORAGE {
		THREAD_STATE,
		SOURCE_VOCAB_STATE,
		DEST_VOCAB_STATE,

		COMPILE_STATE,

		THREAD_STORAGE_SIZE
	};
	static thread_local ForthCell registers[THREAD_STORAGE_SIZE];

	static PrimitiveForthWordFunction TRACE;	// bool --
};

#endif //GIFORTH_PRIMITIVEFORTHWORDS_H
