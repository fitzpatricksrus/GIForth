//
// Created by Dad on 9/17/19.
//

#ifndef GIFORTH_PRIMITIVEFORTHWORDS_H
#define GIFORTH_PRIMITIVEFORTHWORDS_H

#include <utils/PrimitiveForthWordFunction.h>

class PrimitiveForthWords {
public:
    static PrimitiveForthWordFunction NOP;

	// --
	static PrimitiveForthWordFunction JUMP;

	// bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
	static PrimitiveForthWordFunction JUMP_IF_FALSE;

	// --
	static PrimitiveForthWordFunction RETURN;

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
    static PrimitiveForthWordFunction INT_AT;          // addr - char
    static PrimitiveForthWordFunction INT_PUT;         // char addr --
    static PrimitiveForthWordFunction INT_INDEX;       // ndx addr -- addr
    static PrimitiveForthWordFunction CELL_AT;          // addr -- cell
    static PrimitiveForthWordFunction CELL_PUT;         // value addr --
    static PrimitiveForthWordFunction CELL_INDEX;       // ndx addr -- addr

    static PrimitiveForthWordFunction TO_RETURN_STACK;  // >R
    static PrimitiveForthWordFunction FROM_RETURN_STACK; // R>
    static PrimitiveForthWordFunction AT_RETURN_STACK;  // R> dup >R

    static PrimitiveForthWordFunction PICK;	// ( a0 .. an n -- a0 .. an a0 )
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
    static PrimitiveForthWordFunction PRINT_CHAR;

    static PrimitiveForthWordFunction FALSE;
    static PrimitiveForthWordFunction TRUE;
    static PrimitiveForthWordFunction ZERO;
    static PrimitiveForthWordFunction ONE;
    static PrimitiveForthWordFunction NEGATIVE_ONE;
    static PrimitiveForthWordFunction ADD_ONE;
    static PrimitiveForthWordFunction SUBTRACT_ONE;

private:
    static void F_NOP(ForthThread& thread);

	static void F_JUMP(ForthThread &thread);
	static void F_JUMP_IF_FALSE(ForthThread &thread);
	static void F_RETURN(ForthThread &thread);
	static void F_EXECUTE(ForthThread &thread);
	static void F_PUSH_NEXT_CELL(ForthThread &thread);

    static void F_CHAR_SIZE(ForthThread& thread);
    static void F_INT_SIZE(ForthThread& thread);
    static void F_PTR_SIZE(ForthThread& thread);
    static void F_WORD_SIZE(ForthThread& thread);

    static void F_ALLOC(ForthThread& thread);
    static void F_FREE(ForthThread& thread);

    static void F_CHAR_AT(ForthThread& thread);         // ptr -- char
    static void F_CHAR_PUT(ForthThread& thread);        // value ptr --
    static void F_CHAR_INDEX(ForthThread& thread);      // ndx ptr -- ptr

    static void F_INT_AT(ForthThread& thread);
    static void F_INT_PUT(ForthThread& thread);
    static void F_INT_INDEX(ForthThread& thread);

    static void F_CELL_AT(ForthThread& thread);
    static void F_CELL_PUT(ForthThread& thread);
    static void F_CELL_INDEX(ForthThread& thread);

    static void F_TO_RETURN_STACK(ForthThread& thread);
    static void F_FROM_RETURN_STACK(ForthThread& thread);
    static void F_AT_RETURN_STACK(ForthThread& thread);

    static void F_PICK(ForthThread& thread);
    static void F_ROLL(ForthThread& thread);
	static void F_DROP(ForthThread& thread);
	static void F_DUP(ForthThread& thread);

    static void F_ADD(ForthThread& thread);
    static void F_SUBTRACT(ForthThread& thread);
    static void F_MULTIPLY(ForthThread& thread);
    static void F_DIVIDE(ForthThread& thread);
    static void F_MOD(ForthThread& thread);

    static void F_LESS_THAN(ForthThread& thread);
    static void F_GREATER_THAN(ForthThread& thread);
    static void F_EQUAL(ForthThread& thread);

    static void F_CONDITIONAL_AND(ForthThread& thread);
    static void F_CONDITIONAL_OR(ForthThread& thread);
    static void F_CONDITIONAL_NOT(ForthThread& thread);

    static void F_ACCEPT_INPUT(ForthThread& thread);
    static void F_PEEK_NEXT_INPUT_CHAR(ForthThread& thread);
    static void F_GET_NEXT_INPUT_CHAR(ForthThread& thread);
    static void F_PRINT_CHAR(ForthThread& thread);

    static void F_FALSE(ForthThread& thread);
    static void F_TRUE(ForthThread& thread);
    static void F_ZERO(ForthThread& thread);
    static void F_ONE(ForthThread& thread);
    static void F_NEGATIVE_ONE(ForthThread& thread);
    static void F_ADD_ONE(ForthThread& thread);
    static void F_SUBTRACT_ONE(ForthThread& thread);
};

#endif //GIFORTH_PRIMITIVEFORTHWORDS_H
