//
// Created by Dad on 9/17/19.
//

#include "PrimitiveForthWords.h"
#include "runtime/ForthThread.h"
#include "runtime/CompositeForthWord.h"
#include "utils/NativeOSFunctions.hpp"

using ParamType = PrimitiveForthWordFunction::ParamType;

PrimitiveForthWordFunction PrimitiveForthWords::NOP(&PrimitiveForthWords::F_NOP, "CoreForthWords::NOP");
void PrimitiveForthWords::F_NOP(ForthThread& thread) {
}

PrimitiveForthWordFunction PrimitiveForthWords::JUMP(&PrimitiveForthWords::F_JUMP, "CoreForthWords::JUMP", {ParamType::INT });
void PrimitiveForthWords::F_JUMP(ForthThread &thread) {
	thread.setIndex(thread.getNextCell().integer);
}

// bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
PrimitiveForthWordFunction PrimitiveForthWords::JUMP_IF_FALSE(&PrimitiveForthWords::F_JUMP_IF_FALSE, "CoreForthWords::JUMP_IF_FALSE", {ParamType::INT });
void PrimitiveForthWords::F_JUMP_IF_FALSE(ForthThread &thread) {
	int newNdx = thread.getNextCell().integer;  // consume next cell always
	if (!thread.popDataStack().integer) {
		thread.setIndex(newNdx);
	}
}

PrimitiveForthWordFunction PrimitiveForthWords::RETURN(&PrimitiveForthWords::F_RETURN, "CoreForthWords::RETURN");
void PrimitiveForthWords::F_RETURN(ForthThread &thread) {
	thread.popFrame();
}

PrimitiveForthWordFunction PrimitiveForthWords::EXECUTE(&PrimitiveForthWords::F_EXECUTE, "CoreForthWords::EXECUTE");
void PrimitiveForthWords::F_EXECUTE(ForthThread &thread) {
	// hey jf - will this actually work for both primitive and composite words?
	ForthWord *word = thread.popDataStack().word;
	word->execute(thread);
}

// -- value ; pushes next cell in word onto data stack
PrimitiveForthWordFunction PrimitiveForthWords::PUSH_NEXT_CELL(&PrimitiveForthWords::F_PUSH_NEXT_CELL, "CoreForthWords::PUSH_NEXT_CELL", {ParamType::INT });
void PrimitiveForthWords::F_PUSH_NEXT_CELL(ForthThread &thread) {
	thread.pushDataStack(thread.getNextCell());
}

PrimitiveForthWordFunction PrimitiveForthWords::CHAR_SIZE(&PrimitiveForthWords::F_CHAR_SIZE, "CoreForthWords::CHAR_SIZE");
void PrimitiveForthWords::F_CHAR_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::CHAR_TYPE));
}

PrimitiveForthWordFunction PrimitiveForthWords::INT_SIZE(&PrimitiveForthWords::F_INT_SIZE, "CoreForthWords::INT_SIZE");
void PrimitiveForthWords::F_INT_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::INT_TYPE));
}

PrimitiveForthWordFunction PrimitiveForthWords::PTR_SIZE(&PrimitiveForthWords::F_PTR_SIZE, "CoreForthWords::PTR_SIZE");
void PrimitiveForthWords::F_PTR_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::PTR_TYPE));
}

PrimitiveForthWordFunction PrimitiveForthWords::WORD_SIZE(&PrimitiveForthWords::F_WORD_SIZE, "CoreForthWords::WORD_SIZE");
void PrimitiveForthWords::F_WORD_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::word));
}

PrimitiveForthWordFunction PrimitiveForthWords::ALLOC(&PrimitiveForthWords::F_ALLOC, "CoreForthWords::ALLOC");
void PrimitiveForthWords::F_ALLOC(ForthThread& thread) {
    ForthCell::INT_TYPE size = thread.popDataStack().integer;
    thread.pushDataStack((ForthCell::PTR_TYPE)new char[size]);
}

PrimitiveForthWordFunction PrimitiveForthWords::FREE(&PrimitiveForthWords::F_FREE, "CoreForthWords::FREE");
void PrimitiveForthWords::F_FREE(ForthThread& thread) {
    ForthCell::PTR_TYPE ptr = thread.popDataStack().pointer;
    delete[] static_cast<char*>(ptr);
}

// addr - char
PrimitiveForthWordFunction PrimitiveForthWords::CHAR_AT(&PrimitiveForthWords::F_CHAR_AT, "CoreForthWords::CHAR_AT");
void PrimitiveForthWords::F_CHAR_AT(ForthThread& thread) {
    ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
    thread.pushDataStack(*ptr);
}

// char addr --
PrimitiveForthWordFunction PrimitiveForthWords::CHAR_PUT(&PrimitiveForthWords::F_CHAR_PUT, "CoreForthWords::CHAR_PUT");
void PrimitiveForthWords::F_CHAR_PUT(ForthThread& thread) {
    ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
    (*ptr) = static_cast<char>(thread.popDataStack().integer);
}

// ndx addr -- addr
PrimitiveForthWordFunction PrimitiveForthWords::CHAR_INDEX(&PrimitiveForthWords::F_CHAR_INDEX, "CoreForthWords::CHAR_INDEX");
void PrimitiveForthWords::F_CHAR_INDEX(ForthThread& thread) {
    ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
    ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
    thread.pushDataStack(&ptr[ndx]);
}

// addr - INT
PrimitiveForthWordFunction PrimitiveForthWords::INT_AT(&PrimitiveForthWords::F_INT_AT, "CoreForthWords::INT_AT");
void PrimitiveForthWords::F_INT_AT(ForthThread& thread) {
    ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
    thread.pushDataStack(*ptr);
}

// INT addr --
PrimitiveForthWordFunction PrimitiveForthWords::INT_PUT(&PrimitiveForthWords::F_INT_PUT, "CoreForthWords::INT_PUT");
void PrimitiveForthWords::F_INT_PUT(ForthThread& thread) {
    ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
    (*ptr) = thread.popDataStack().integer;
}

// ndx addr -- addr
PrimitiveForthWordFunction PrimitiveForthWords::INT_INDEX(&PrimitiveForthWords::F_INT_INDEX, "CoreForthWords::INT_INDEX");
void PrimitiveForthWords::F_INT_INDEX(ForthThread& thread) {
    ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
    ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
    thread.pushDataStack(&ptr[ndx]);
}

// addr - CELL
PrimitiveForthWordFunction PrimitiveForthWords::CELL_AT(&PrimitiveForthWords::F_CELL_AT, "CoreForthWords::CELL_AT");
void PrimitiveForthWords::F_CELL_AT(ForthThread& thread) {
    ForthCell::CELL_TYPE* ptr = static_cast<ForthCell::CELL_TYPE*>(thread.popDataStack().pointer);
    thread.pushDataStack(*ptr);
}

// CELL addr --
PrimitiveForthWordFunction PrimitiveForthWords::CELL_PUT(&PrimitiveForthWords::F_CELL_PUT, "CoreForthWords::CELL_PUT");
void PrimitiveForthWords::F_CELL_PUT(ForthThread& thread) {
    ForthCell::CELL_TYPE* ptr = static_cast<ForthCell::CELL_TYPE*>(thread.popDataStack().pointer);
    (*ptr) = thread.popDataStack().word;
}

// ndx addr -- addr
PrimitiveForthWordFunction PrimitiveForthWords::CELL_INDEX(&PrimitiveForthWords::F_CELL_INDEX, "CoreForthWords::CELL_INDEX");
void PrimitiveForthWords::F_CELL_INDEX(ForthThread& thread) {
    ForthCell::CELL_TYPE* ptr = static_cast<ForthCell::CELL_TYPE*>(thread.popDataStack().pointer);
    ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
    thread.pushDataStack(&ptr[ndx]);
}

PrimitiveForthWordFunction PrimitiveForthWords::TO_RETURN_STACK(&PrimitiveForthWords::F_TO_RETURN_STACK, "CoreForthWords::TO_RETURN_STACK");
void PrimitiveForthWords::F_TO_RETURN_STACK(ForthThread& thread) {
    thread.toReturnStack(thread.popDataStack());
}

PrimitiveForthWordFunction PrimitiveForthWords::FROM_RETURN_STACK(&PrimitiveForthWords::F_FROM_RETURN_STACK, "CoreForthWords::FROM_RETURN_STACK");
void PrimitiveForthWords::F_FROM_RETURN_STACK(ForthThread& thread) {
    thread.pushDataStack(thread.fromReturnStack().cell);
}

PrimitiveForthWordFunction PrimitiveForthWords::AT_RETURN_STACK(&PrimitiveForthWords::F_FROM_RETURN_STACK, "CoreForthWords::FROM_RETURN_STACK");
void PrimitiveForthWords::F_AT_RETURN_STACK(ForthThread &thread) {
    thread.pushDataStack(thread.topOfReturnStack().cell);
}

// ( a0 .. an n -- a0 .. an a0 )
PrimitiveForthWordFunction PrimitiveForthWords::PICK(&PrimitiveForthWords::F_PICK, "CoreForthWords::PICK");
void PrimitiveForthWords::F_PICK(ForthThread& thread) {
    thread.pushDataStack(thread[thread.popDataStack().integer]);
}

// ( a0 .. an n -- a0 .. an a0 )
PrimitiveForthWordFunction PrimitiveForthWords::OVER(&PrimitiveForthWords::F_OVER, "CoreForthWords::OVER");
void PrimitiveForthWords::F_OVER(ForthThread& thread) {
    thread.pushDataStack(thread[1]);
}

// ( a0 .. an n -- a1 .. an a0 )
PrimitiveForthWordFunction PrimitiveForthWords::ROLL(&PrimitiveForthWords::F_ROLL, "CoreForthWords::ROLL");
void PrimitiveForthWords::F_ROLL(ForthThread& thread) {
    thread.rollDataStack(thread.popDataStack().integer);
}

PrimitiveForthWordFunction PrimitiveForthWords::DROP(&PrimitiveForthWords::F_DROP, "CoreForthWords::DROP");
void PrimitiveForthWords::F_DROP(ForthThread& thread) {
    thread.popDataStack();
}

PrimitiveForthWordFunction PrimitiveForthWords::DUP(&PrimitiveForthWords::F_DUP, "CoreForthWords::DUP");
void PrimitiveForthWords::F_DUP(ForthThread& thread) {
    thread.pushDataStack(thread[0]);
}

PrimitiveForthWordFunction PrimitiveForthWords::ADD(&PrimitiveForthWords::F_ADD, "CoreForthWords::ADD");
void PrimitiveForthWords::F_ADD(ForthThread& thread) {
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	thread.pushDataStack(x + y);
}

// a b -- (a - b)
PrimitiveForthWordFunction PrimitiveForthWords::SUBTRACT(&PrimitiveForthWords::F_SUBTRACT, "CoreForthWords::SUBTRACT");
void PrimitiveForthWords::F_SUBTRACT(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
	ForthCell::INT_TYPE subtrahend = thread.popDataStack().integer;
	ForthCell::INT_TYPE value = thread.popDataStack().integer;
    thread.pushDataStack(value - subtrahend);
}

PrimitiveForthWordFunction PrimitiveForthWords::MULTIPLY(&PrimitiveForthWords::F_MULTIPLY, "CoreForthWords::MULTIPLY");
void PrimitiveForthWords::F_MULTIPLY(ForthThread& thread) {
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
    thread.pushDataStack(x * y);
}

// x y -- (x / y)
PrimitiveForthWordFunction PrimitiveForthWords::DIVIDE(&PrimitiveForthWords::F_DIVIDE, "CoreForthWords::DIVIDE");
void PrimitiveForthWords::F_DIVIDE(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
	ForthCell::INT_TYPE divisor = thread.popDataStack().integer;
	ForthCell::INT_TYPE dividend = thread.popDataStack().integer;
    thread.pushDataStack(dividend / divisor);
}

// x y -- (x % y)
PrimitiveForthWordFunction PrimitiveForthWords::MOD(&PrimitiveForthWords::F_MOD, "CoreForthWords::MOD");
void PrimitiveForthWords::F_MOD(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
	ForthCell::INT_TYPE modulus = thread.popDataStack().integer;
	ForthCell::INT_TYPE value = thread.popDataStack().integer;
    
    thread.pushDataStack(value % modulus);
}


// x y -- (x < y)
PrimitiveForthWordFunction PrimitiveForthWords::LESS_THAN(&PrimitiveForthWords::F_LESS_THAN, "CoreForthWords::LESS_THAN");
void PrimitiveForthWords::F_LESS_THAN(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
    thread.pushDataStack(x < y);
}

// x y -- (x > y)
PrimitiveForthWordFunction PrimitiveForthWords::GREATER_THAN(&PrimitiveForthWords::F_GREATER_THAN, "CoreForthWords::GREATER_THAN");
void PrimitiveForthWords::F_GREATER_THAN(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
    thread.pushDataStack(x > y);
}

// x y -- (x == y)
PrimitiveForthWordFunction PrimitiveForthWords::EQUAL(&PrimitiveForthWords::F_EQUAL, "CoreForthWords::EQUAL");
void PrimitiveForthWords::F_EQUAL(ForthThread& thread) {
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
    thread.pushDataStack(x == y);
}

// x y -- (x && y)
PrimitiveForthWordFunction PrimitiveForthWords::CONDITIONAL_AND(&PrimitiveForthWords::F_CONDITIONAL_AND, "CoreForthWords::AND");
void PrimitiveForthWords::F_CONDITIONAL_AND(ForthThread& thread) {
	bool b1 = static_cast<bool>(thread.popDataStack().integer);
	bool b2 = static_cast<bool>(thread.popDataStack().integer);
    thread.pushDataStack(b1 && b2);
}

// x y -- (x && y)
PrimitiveForthWordFunction PrimitiveForthWords::CONDITIONAL_OR(&PrimitiveForthWords::F_CONDITIONAL_OR, "CoreForthWords::OR");
void PrimitiveForthWords::F_CONDITIONAL_OR(ForthThread& thread) {
	bool b1 = static_cast<bool>(thread.popDataStack().integer);
	bool b2 = static_cast<bool>(thread.popDataStack().integer);
    thread.pushDataStack(b1 && b2);
}

// x -- !x)
PrimitiveForthWordFunction PrimitiveForthWords::CONDITIONAL_NOT(&PrimitiveForthWords::F_CONDITIONAL_NOT, "CoreForthWords::NOT");
void PrimitiveForthWords::F_CONDITIONAL_NOT(ForthThread& thread) {
    thread.pushDataStack(!static_cast<bool>(thread.popDataStack().integer));
}

PrimitiveForthWordFunction PrimitiveForthWords::ACCEPT_INPUT(&PrimitiveForthWords::F_ACCEPT_INPUT, "CoreForthWords::ACCEPT_INPUT");
void PrimitiveForthWords::F_ACCEPT_INPUT(ForthThread& thread) {
    ForthCell::INT_TYPE size = thread.popDataStack().integer;
    ForthCell::PTR_TYPE ptr = thread.popDataStack().pointer;
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(NativeOSFunctions::accept(static_cast<char*>(ptr), size)));
}

PrimitiveForthWordFunction PrimitiveForthWords::PEEK_NEXT_INPUT_CHAR(&PrimitiveForthWords::F_PEEK_NEXT_INPUT_CHAR, "CoreForthWords::PEEK_NEXT_INPUT_CHAR");
void PrimitiveForthWords::F_PEEK_NEXT_INPUT_CHAR(ForthThread& thread) {
    thread.pushDataStack(NativeOSFunctions::peekNextChar());
}

PrimitiveForthWordFunction PrimitiveForthWords::GET_NEXT_INPUT_CHAR(&PrimitiveForthWords::F_GET_NEXT_INPUT_CHAR, "CoreForthWords::GET_NEXT_INPUT_CHAR");
void PrimitiveForthWords::F_GET_NEXT_INPUT_CHAR(ForthThread& thread) {
    thread.pushDataStack(NativeOSFunctions::nextChar());
}

PrimitiveForthWordFunction PrimitiveForthWords::PRINT_CHAR(&PrimitiveForthWords::F_PRINT_CHAR, "CoreForthWords::PRINT_CHAR");
void PrimitiveForthWords::F_PRINT_CHAR(ForthThread& thread) {
    NativeOSFunctions::printChar(static_cast<char>(thread.popDataStack().integer));
}

PrimitiveForthWordFunction PrimitiveForthWords::FALSE(&PrimitiveForthWords::F_FALSE, "CoreForthWords::FALSE");
void PrimitiveForthWords::F_FALSE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(false));
}

PrimitiveForthWordFunction PrimitiveForthWords::TRUE(&PrimitiveForthWords::F_TRUE, "CoreForthWords::TRUE");
void PrimitiveForthWords::F_TRUE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(true));
}

PrimitiveForthWordFunction PrimitiveForthWords::ZERO(&PrimitiveForthWords::F_ZERO, "CoreForthWords::ZERO");
void PrimitiveForthWords::F_ZERO(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(0));
}

PrimitiveForthWordFunction PrimitiveForthWords::ONE(&PrimitiveForthWords::F_ONE, "CoreForthWords::ONE");
void PrimitiveForthWords::F_ONE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(1));
}

PrimitiveForthWordFunction PrimitiveForthWords::NEGATIVE_ONE(&PrimitiveForthWords::F_NEGATIVE_ONE, "CoreForthWords::NEGATIVE_ONE");
void PrimitiveForthWords::F_NEGATIVE_ONE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(-1));
}

PrimitiveForthWordFunction PrimitiveForthWords::ADD_ONE(&PrimitiveForthWords::F_ADD_ONE, "CoreForthWords::ADD_ONE");
void PrimitiveForthWords::F_ADD_ONE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(1 + thread.popDataStack().integer));
}

PrimitiveForthWordFunction PrimitiveForthWords::SUBTRACT_ONE(&PrimitiveForthWords::F_ADD_ONE, "CoreForthWords::SUBTRACT_ONE");
void PrimitiveForthWords::F_SUBTRACT_ONE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(thread.popDataStack().integer - 1));
}
