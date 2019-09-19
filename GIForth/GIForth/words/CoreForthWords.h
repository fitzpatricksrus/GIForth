//
// Created by Dad on 9/17/19.
//

#ifndef GIFORTH_COREFORTHWORDS_H
#define GIFORTH_COREFORTHWORDS_H

#include <utils/PrimativeForthWordFunction.h>

class CoreForthWords {
public:
    static PrimativeForthWordFunction NOP;

	// --
	static PrimativeForthWordFunction JUMP;

	// bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
	static PrimativeForthWordFunction JUMP_IF_FALSE;

	// --
	static PrimativeForthWordFunction RETURN;

	// wordAddr --
	static PrimativeForthWordFunction EXECUTE;

	// -- value ; pushes next cell in word onto data stack
	static PrimativeForthWordFunction PUSH_NEXT_CELL;

	static PrimativeForthWordFunction CHAR_SIZE;
    static PrimativeForthWordFunction INT_SIZE;
    static PrimativeForthWordFunction PTR_SIZE;
    static PrimativeForthWordFunction WORD_SIZE;

    static PrimativeForthWordFunction ALLOC;
    static PrimativeForthWordFunction FREE;

    static PrimativeForthWordFunction CHAR_AT;          // addr - char
    static PrimativeForthWordFunction CHAR_PUT;         // char addr --
    static PrimativeForthWordFunction CHAR_INDEX;       // ndx addr -- addr
    static PrimativeForthWordFunction INT_AT;          // addr - char
    static PrimativeForthWordFunction INT_PUT;         // char addr --
    static PrimativeForthWordFunction INT_INDEX;       // ndx addr -- addr
    static PrimativeForthWordFunction CELL_AT;          // addr -- cell
    static PrimativeForthWordFunction CELL_PUT;         // value addr --
    static PrimativeForthWordFunction CELL_INDEX;       // ndx addr -- addr

    static PrimativeForthWordFunction TO_RETURN_STACK;
    static PrimativeForthWordFunction FROM_RETURN_STACK;

    static PrimativeForthWordFunction PICK;	// ( a0 .. an n -- a0 .. an a0 )
    static PrimativeForthWordFunction ROLL;	// ( a0 .. an n -- a1 .. an a0 )
    static PrimativeForthWordFunction DROP;

    static PrimativeForthWordFunction ADD;
    static PrimativeForthWordFunction SUBTRACT;
    static PrimativeForthWordFunction MULTIPLY;
    static PrimativeForthWordFunction DIVIDE;
    static PrimativeForthWordFunction MOD;

    static PrimativeForthWordFunction LESS_THAN;
    static PrimativeForthWordFunction GREATER_THAN;
    static PrimativeForthWordFunction EQUAL;

    static PrimativeForthWordFunction CONDITIONAL_AND;
    static PrimativeForthWordFunction CONDITIONAL_OR;
    static PrimativeForthWordFunction CONDITIONAL_NOT;

    static PrimativeForthWordFunction PEEK_NEXT_INPUT_CHAR;
    static PrimativeForthWordFunction GET_NEXT_INPUT_CHAR;
    static PrimativeForthWordFunction PRINT_CHAR;
    
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

    static void F_CHAR_AT(ForthThread& thread);
    static void F_CHAR_PUT(ForthThread& thread);
    static void F_CHAR_INDEX(ForthThread& thread);

    static void F_INT_AT(ForthThread& thread);
    static void F_INT_PUT(ForthThread& thread);
    static void F_INT_INDEX(ForthThread& thread);

    static void F_CELL_AT(ForthThread& thread);
    static void F_CELL_PUT(ForthThread& thread);
    static void F_CELL_INDEX(ForthThread& thread);

    static void F_TO_RETURN_STACK(ForthThread& thread);
    static void F_FROM_RETURN_STACK(ForthThread& thread);

    static void F_PICK(ForthThread& thread);
    static void F_ROLL(ForthThread& thread);
    static void F_DROP(ForthThread& thread);

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

    static void F_PEEK_NEXT_INPUT_CHAR(ForthThread& thread);
    static void F_GET_NEXT_INPUT_CHAR(ForthThread& thread);
    static void F_PRINT_CHAR(ForthThread& thread);
};

#endif //GIFORTH_COREFORTHWORDS_H
