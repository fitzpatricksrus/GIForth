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

    static ForthWord& NOP();

	// --
	static ForthWord& JUMP();
	// bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
	static ForthWord& JUMP_IF_FALSE();
	// --
	static ForthWord& RETURN();
	// -- value pushes next cell in word onto data stack
	static ForthWord& PUSH_NEXT_CELL();
	static ForthWord& TO_RETURN_STACK();
	static ForthWord& FROM_RETURN_STACK();
	static ForthWord& AT_RETURN_STACK();

	static ForthWord& EXIT_THREAD();

	// wordAddr --
	static ForthWord& EXECUTE();

	static ForthWord& CHAR_SIZE();
    static ForthWord& INT_SIZE();
    static ForthWord& PTR_SIZE();
    static ForthWord& WORD_SIZE();

    static ForthWord& ALLOC();
    static ForthWord& FREE();

    static ForthWord& CHAR_AT();          // addr - char
    static ForthWord& CHAR_PUT();         // char addr --
    static ForthWord& CHAR_INDEX();       // ndx addr -- addr
    static ForthWord& INT_AT();           // addr - char
    static ForthWord& INT_PUT();			// char addr --
    static ForthWord& INT_INDEX();		// ndx addr -- addr
    static ForthWord& CELL_AT();          // addr -- cell
    static ForthWord& CELL_PUT();         // value addr --
    static ForthWord& CELL_INDEX();       // ndx addr -- addr

	// >R
	// R>
	// R> dup >R

    static ForthWord& SWAP();	// ( a b -- b a )
    static ForthWord& PICK();	// ( a0 .. an x -- a0 .. an ax )
    static ForthWord& OVER();	// ( a b -- a b a )
    static ForthWord& ROLL();	// ( a0 .. an n -- a1 .. an a0 )
    static ForthWord& DROP();
    static ForthWord& DUP();

    static ForthWord& ADD();
    static ForthWord& SUBTRACT();
    static ForthWord& MULTIPLY();
    static ForthWord& DIVIDE();
    static ForthWord& MOD();

    static ForthWord& LESS_THAN();
    static ForthWord& GREATER_THAN();
    static ForthWord& EQUAL();

    static ForthWord& CONDITIONAL_AND();
    static ForthWord& CONDITIONAL_OR();
    static ForthWord& CONDITIONAL_NOT();

    static ForthWord& ACCEPT_INPUT();     // charPtr size -- inputSize
    static ForthWord& PEEK_NEXT_INPUT_CHAR();
	static ForthWord& GET_NEXT_INPUT_CHAR();
	static ForthWord& FLUSH_INPUT();
    static ForthWord& PRINT_CHAR();

    static ForthWord& FALSE();
    static ForthWord& TRUE();
    static ForthWord& ZERO();
    static ForthWord& ONE();
    static ForthWord& NEGATIVE_ONE();
    static ForthWord& ADD_ONE();
    static ForthWord& SUBTRACT_ONE();

	static ForthWord& REGISTER();
    enum THREAD_STORAGE {
		THREAD_STATE,
		SOURCE_VOCAB_STATE,
		DEST_VOCAB_STATE,

		COMPILE_STATE,

		THREAD_STORAGE_SIZE
	};
	static thread_local ForthCell registers[THREAD_STORAGE_SIZE];

	static ForthWord& TRACE();	// bool --
};

#endif //GIFORTH_PRIMITIVEFORTHWORDS_H
