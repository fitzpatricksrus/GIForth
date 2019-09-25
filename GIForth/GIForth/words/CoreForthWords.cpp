//
// Created by Dad on 9/17/19.
//

#include "CoreForthWords.h"
#include "runtime/ForthThread.h"
#include "runtime/CompositeForthWord.h"
#include "utils/NativeOSFunctions.hpp"

using ParamType = PrimativeForthWordFunction::ParamType;

PrimativeForthWordFunction CoreForthWords::NOP(&CoreForthWords::F_NOP, "CoreForthWords::NOP");
void CoreForthWords::F_NOP(ForthThread& thread) {
}

PrimativeForthWordFunction CoreForthWords::JUMP(&CoreForthWords::F_JUMP, "CoreForthWords::JUMP", { ParamType::INT });
void CoreForthWords::F_JUMP(ForthThread &thread) {
	thread.setIndex(thread.getNextCell().integer);
}

// bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
PrimativeForthWordFunction CoreForthWords::JUMP_IF_FALSE(&CoreForthWords::F_JUMP_IF_FALSE, "CoreForthWords::JUMP_IF_FALSE", { ParamType::INT });
void CoreForthWords::F_JUMP_IF_FALSE(ForthThread &thread) {
	int newNdx = thread.getNextCell().integer;  // consume next cell always
	if (!thread.popDataStack().boolean) {
		thread.setIndex(newNdx);
	}
}

PrimativeForthWordFunction CoreForthWords::RETURN(&CoreForthWords::F_RETURN, "CoreForthWords::RETURN");
void CoreForthWords::F_RETURN(ForthThread &thread) {
	thread.popFrame();
}

PrimativeForthWordFunction CoreForthWords::EXECUTE(&CoreForthWords::F_EXECUTE, "CoreForthWords::EXECUTE");
void CoreForthWords::F_EXECUTE(ForthThread &thread) {
	// hey jf - will this actually work for both primitive and composite words?
	ForthWord *word = thread.popDataStack().word;
	word->execute(thread);
}

// -- value ; pushes next cell in word onto data stack
PrimativeForthWordFunction CoreForthWords::PUSH_NEXT_CELL(&CoreForthWords::F_PUSH_NEXT_CELL, "CoreForthWords::PUSH_NEXT_CELL", { ParamType::INT });
void CoreForthWords::F_PUSH_NEXT_CELL(ForthThread &thread) {
	thread.pushDataStack(thread.getNextCell());
}

PrimativeForthWordFunction CoreForthWords::CHAR_SIZE(&CoreForthWords::F_CHAR_SIZE, "CoreForthWords::CHAR_SIZE");
void CoreForthWords::F_CHAR_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::character));
}

PrimativeForthWordFunction CoreForthWords::INT_SIZE(&CoreForthWords::F_INT_SIZE, "CoreForthWords::INT_SIZE");
void CoreForthWords::F_INT_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::integer));
}

PrimativeForthWordFunction CoreForthWords::PTR_SIZE(&CoreForthWords::F_PTR_SIZE, "CoreForthWords::PTR_SIZE");
void CoreForthWords::F_PTR_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::pointer));
}

PrimativeForthWordFunction CoreForthWords::WORD_SIZE(&CoreForthWords::F_WORD_SIZE, "CoreForthWords::WORD_SIZE");
void CoreForthWords::F_WORD_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::word));
}

PrimativeForthWordFunction CoreForthWords::ALLOC(&CoreForthWords::F_ALLOC, "CoreForthWords::ALLOC");
void CoreForthWords::F_ALLOC(ForthThread& thread) {
    ForthCell::INT_TYPE size = thread.popDataStack().integer;
    thread.pushDataStack((ForthCell::PTR_TYPE)new char[size]);
}

PrimativeForthWordFunction CoreForthWords::FREE(&CoreForthWords::F_FREE, "CoreForthWords::FREE");
void CoreForthWords::F_FREE(ForthThread& thread) {
    ForthCell::PTR_TYPE ptr = thread.popDataStack().pointer;
    delete[] static_cast<char*>(ptr);
}

// addr - char
PrimativeForthWordFunction CoreForthWords::CHAR_AT(&CoreForthWords::F_CHAR_AT, "CoreForthWords::CHAR_AT");
void CoreForthWords::F_CHAR_AT(ForthThread& thread) {
    ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
    thread.pushDataStack(*ptr);
}

// char addr --
PrimativeForthWordFunction CoreForthWords::CHAR_PUT(&CoreForthWords::F_CHAR_PUT, "CoreForthWords::CHAR_PUT");
void CoreForthWords::F_CHAR_PUT(ForthThread& thread) {
    ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
    (*ptr) = thread.popDataStack().character;
}

// ndx addr -- addr
PrimativeForthWordFunction CoreForthWords::CHAR_INDEX(&CoreForthWords::F_CHAR_INDEX, "CoreForthWords::CHAR_INDEX");
void CoreForthWords::F_CHAR_INDEX(ForthThread& thread) {
    ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
    ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
    thread.pushDataStack(&ptr[ndx]);
}

// addr - INT
PrimativeForthWordFunction CoreForthWords::INT_AT(&CoreForthWords::F_INT_AT, "CoreForthWords::INT_AT");
void CoreForthWords::F_INT_AT(ForthThread& thread) {
    ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
    thread.pushDataStack(*ptr);
}

// INT addr --
PrimativeForthWordFunction CoreForthWords::INT_PUT(&CoreForthWords::F_INT_PUT, "CoreForthWords::INT_PUT");
void CoreForthWords::F_INT_PUT(ForthThread& thread) {
    ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
    (*ptr) = thread.popDataStack().integer;
}

// ndx addr -- addr
PrimativeForthWordFunction CoreForthWords::INT_INDEX(&CoreForthWords::F_INT_INDEX, "CoreForthWords::INT_INDEX");
void CoreForthWords::F_INT_INDEX(ForthThread& thread) {
    ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
    ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
    thread.pushDataStack(&ptr[ndx]);
}

// addr - CELL
PrimativeForthWordFunction CoreForthWords::CELL_AT(&CoreForthWords::F_CELL_AT, "CoreForthWords::CELL_AT");
void CoreForthWords::F_CELL_AT(ForthThread& thread) {
    ForthCell::CELL_TYPE* ptr = static_cast<ForthCell::CELL_TYPE*>(thread.popDataStack().pointer);
    thread.pushDataStack(*ptr);
}

// CELL addr --
PrimativeForthWordFunction CoreForthWords::CELL_PUT(&CoreForthWords::F_CELL_PUT, "CoreForthWords::CELL_PUT");
void CoreForthWords::F_CELL_PUT(ForthThread& thread) {
    ForthCell::CELL_TYPE* ptr = static_cast<ForthCell::CELL_TYPE*>(thread.popDataStack().pointer);
    (*ptr) = thread.popDataStack().word;
}

// ndx addr -- addr
PrimativeForthWordFunction CoreForthWords::CELL_INDEX(&CoreForthWords::F_CELL_INDEX, "CoreForthWords::CELL_INDEX");
void CoreForthWords::F_CELL_INDEX(ForthThread& thread) {
    ForthCell::CELL_TYPE* ptr = static_cast<ForthCell::CELL_TYPE*>(thread.popDataStack().pointer);
    ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
    thread.pushDataStack(&ptr[ndx]);
}

PrimativeForthWordFunction CoreForthWords::TO_RETURN_STACK(&CoreForthWords::F_TO_RETURN_STACK, "CoreForthWords::TO_RETURN_STACK");
void CoreForthWords::F_TO_RETURN_STACK(ForthThread& thread) {
    thread.toReturnStack(thread.popDataStack());
}

PrimativeForthWordFunction CoreForthWords::FROM_RETURN_STACK(&CoreForthWords::F_FROM_RETURN_STACK, "CoreForthWords::FROM_RETURN_STACK");
void CoreForthWords::F_FROM_RETURN_STACK(ForthThread& thread) {
    thread.pushDataStack(thread.fromReturnStack().cell);
}

// ( a0 .. an n -- a0 .. an a0 )
PrimativeForthWordFunction CoreForthWords::PICK(&CoreForthWords::F_PICK, "CoreForthWords::PICK");
void CoreForthWords::F_PICK(ForthThread& thread) {
    thread.pushDataStack(thread[thread.popDataStack().integer]);
}

// ( a0 .. an n -- a1 .. an a0 )
PrimativeForthWordFunction CoreForthWords::ROLL(&CoreForthWords::F_ROLL, "CoreForthWords::ROLL");
void CoreForthWords::F_ROLL(ForthThread& thread) {
    thread.rollDataStack(thread.popDataStack().integer);
}

PrimativeForthWordFunction CoreForthWords::DROP(&CoreForthWords::F_DROP, "CoreForthWords::DROP");
void CoreForthWords::F_DROP(ForthThread& thread) {
    thread.popDataStack();
}

PrimativeForthWordFunction CoreForthWords::ADD(&CoreForthWords::F_ADD, "CoreForthWords::ADD");
void CoreForthWords::F_ADD(ForthThread& thread) {
    thread.pushDataStack(thread.popDataStack().integer + thread.popDataStack().integer);
}

// a b -- (a - b)
PrimativeForthWordFunction CoreForthWords::SUBTRACT(&CoreForthWords::F_SUBTRACT, "CoreForthWords::SUBTRACT");
void CoreForthWords::F_SUBTRACT(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
    ForthCell::INT_TYPE subtrahend = thread.popDataStack().integer;
    thread.pushDataStack(thread.popDataStack().integer - subtrahend);
}

PrimativeForthWordFunction CoreForthWords::MULTIPLY(&CoreForthWords::F_MULTIPLY, "CoreForthWords::MULTIPLY");
void CoreForthWords::F_MULTIPLY(ForthThread& thread) {
    thread.pushDataStack(thread.popDataStack().integer * thread.popDataStack().integer);
}

// x y -- (x / y)
PrimativeForthWordFunction CoreForthWords::DIVIDE(&CoreForthWords::F_DIVIDE, "CoreForthWords::DIVIDE");
void CoreForthWords::F_DIVIDE(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
    ForthCell::INT_TYPE divisor = thread.popDataStack().integer;
    thread.pushDataStack(thread.popDataStack().integer / divisor);
}

// x y -- (x % y)
PrimativeForthWordFunction CoreForthWords::MOD(&CoreForthWords::F_MOD, "CoreForthWords::MOD");
void CoreForthWords::F_MOD(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
    ForthCell::INT_TYPE modulus = thread.popDataStack().integer;
    thread.pushDataStack(thread.popDataStack().integer / modulus);
}


// x y -- (x < y)
PrimativeForthWordFunction CoreForthWords::LESS_THAN(&CoreForthWords::F_LESS_THAN, "CoreForthWords::LESS_THAN");
void CoreForthWords::F_LESS_THAN(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
    ForthCell::INT_TYPE y = thread.popDataStack().integer;
    thread.pushDataStack(thread.popDataStack().integer < y);
}

// x y -- (x > y)
PrimativeForthWordFunction CoreForthWords::GREATER_THAN(&CoreForthWords::F_GREATER_THAN, "CoreForthWords::GREATER_THAN");
void CoreForthWords::F_GREATER_THAN(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
    ForthCell::INT_TYPE y = thread.popDataStack().integer;
    thread.pushDataStack(thread.popDataStack().integer > y);
}

// x y -- (x == y)
PrimativeForthWordFunction CoreForthWords::EQUAL(&CoreForthWords::F_EQUAL, "CoreForthWords::EQUAL");
void CoreForthWords::F_EQUAL(ForthThread& thread) {
    thread.pushDataStack(thread.popDataStack().integer == thread.popDataStack().integer);
}

// x y -- (x && y)
PrimativeForthWordFunction CoreForthWords::CONDITIONAL_AND(&CoreForthWords::F_CONDITIONAL_AND, "CoreForthWords::AND");
void CoreForthWords::F_CONDITIONAL_AND(ForthThread& thread) {
    thread.pushDataStack(thread.popDataStack().boolean && thread.popDataStack().boolean);
}

// x y -- (x && y)
PrimativeForthWordFunction CoreForthWords::CONDITIONAL_OR(&CoreForthWords::F_CONDITIONAL_OR, "CoreForthWords::OR");
void CoreForthWords::F_CONDITIONAL_OR(ForthThread& thread) {
    thread.pushDataStack(thread.popDataStack().boolean || thread.popDataStack().boolean);
}

// x -- !x)
PrimativeForthWordFunction CoreForthWords::CONDITIONAL_NOT(&CoreForthWords::F_CONDITIONAL_NOT, "CoreForthWords::NOT");
void CoreForthWords::F_CONDITIONAL_NOT(ForthThread& thread) {
    thread.pushDataStack(!thread.popDataStack().boolean);
}

PrimativeForthWordFunction CoreForthWords::PEEK_NEXT_INPUT_CHAR(&CoreForthWords::F_PEEK_NEXT_INPUT_CHAR, "CoreForthWords::PEEK_NEXT_INPUT_CHAR");
void CoreForthWords::F_PEEK_NEXT_INPUT_CHAR(ForthThread& thread) {
    thread.pushDataStack(NativeOSFunctions::peekNextChar());
}

PrimativeForthWordFunction CoreForthWords::GET_NEXT_INPUT_CHAR(&CoreForthWords::F_GET_NEXT_INPUT_CHAR, "CoreForthWords::GET_NEXT_INPUT_CHAR");
void CoreForthWords::F_GET_NEXT_INPUT_CHAR(ForthThread& thread) {
    thread.pushDataStack(NativeOSFunctions::nextChar());
}

PrimativeForthWordFunction CoreForthWords::PRINT_CHAR(&CoreForthWords::F_PRINT_CHAR, "CoreForthWords::PRINT_CHAR");
void CoreForthWords::F_PRINT_CHAR(ForthThread& thread) {
    NativeOSFunctions::printChar(thread.popDataStack().character);
}
