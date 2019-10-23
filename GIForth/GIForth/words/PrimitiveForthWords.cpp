//
// Created by Dad on 9/17/19.
//

#include <words/bootstrap/CompositeForthWordBuilder.h>
#include "PrimitiveForthWords.h"
#include "runtime/ForthThread.h"
#include "runtime/CompositeForthWord.h"
#include "utils/NativeOSFunctions.hpp"
#include "utils/testing/catch.hpp"

PrimitiveForthWords::PrimitiveForthWords(ForthVocab *next)
	: BasicForthVocab(next)
{
	add(&NOP);
	add(&JUMP);
	add(&JUMP_IF_FALSE);
	add(&RETURN);
	add(&EXECUTE);
	add(&PUSH_NEXT_CELL);
	add(&CHAR_SIZE);
	add(&INT_SIZE);
	add(&PTR_SIZE);
	add(&WORD_SIZE);
	add(&ALLOC);
	add(&FREE);
	add(&CHAR_AT);
	add(&CHAR_PUT);
	add(&CHAR_INDEX);
	add(&INT_AT);
	add(&INT_PUT);
	add(&INT_INDEX);
	add(&CELL_AT);
	add(&CELL_PUT);
	add(&CELL_INDEX);
	add(&TO_RETURN_STACK);
	add(&FROM_RETURN_STACK);
	add(&AT_RETURN_STACK);
	add(&SWAP);
	add(&PICK);
	add(&OVER);
	add(&ROLL);
	add(&DROP);
	add(&DUP);
	add(&ADD);
	add(&SUBTRACT);
	add(&MULTIPLY);
	add(&DIVIDE);
	add(&MOD);
	add(&LESS_THAN);
	add(&GREATER_THAN);
	add(&EQUAL);
	add(&CONDITIONAL_AND);
	add(&CONDITIONAL_OR);
	add(&CONDITIONAL_NOT);
	add(&ACCEPT_INPUT);
	add(&PEEK_NEXT_INPUT_CHAR);
	add(&GET_NEXT_INPUT_CHAR);
	add(&PRINT_CHAR);
	add(&FALSE);
	add(&TRUE);
	add(&ZERO);
	add(&ONE);
	add(&NEGATIVE_ONE);
	add(&ADD_ONE);
	add(&SUBTRACT_ONE);
}

using ParamType = PrimitiveForthWordFunction::ParamType;

PrimitiveForthWordFunction PrimitiveForthWords::NOP(&PrimitiveForthWords::F_NOP, "PrimitiveForthWords::NOP");
void PrimitiveForthWords::F_NOP(ForthThread& thread) {
}
TEST_CASE( "words/PrimitiveForthWords::NOP", "[PrimitiveForthWords::NOP]" ) {
	ForthThread thread = ForthThread(ForthExecutionFrame());
	PrimitiveForthWords::NOP.execute(thread);
	REQUIRE(thread.getDataStackSize() == 0);
}

PrimitiveForthWordFunction PrimitiveForthWords::JUMP(&PrimitiveForthWords::F_JUMP, "PrimitiveForthWords::JUMP", {ParamType::INT });
void PrimitiveForthWords::F_JUMP(ForthThread &thread) {
	thread.setIndex(thread.getNextCell().integer);
}
TEST_CASE( "words/PrimitiveForthWords::JUMP", "[PrimitiveForthWords::JUMP]" ) {
	CompositeForthWord word(
			CompositeForthWordBuilder("")
					.append(static_cast<ForthCell::INT_TYPE>(32))
					.build()
	);
	ForthThread thread = ForthThread(&word);
	REQUIRE(thread.getDataStackSize() == 0);
	REQUIRE(thread.getIndex() == 0);
	PrimitiveForthWords::JUMP.execute(thread);
	REQUIRE(thread.getDataStackSize() == 0);
	REQUIRE(thread.getIndex() == 32);
}

// bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
PrimitiveForthWordFunction PrimitiveForthWords::JUMP_IF_FALSE(&PrimitiveForthWords::F_JUMP_IF_FALSE, "PrimitiveForthWords::JUMP_IF_FALSE", {ParamType::INT });
void PrimitiveForthWords::F_JUMP_IF_FALSE(ForthThread &thread) {
	int newNdx = thread.getNextCell().integer;  // consume next cell always
	if (!thread.popDataStack().integer) {
		thread.setIndex(newNdx);
	}
}
TEST_CASE( "words/PrimitiveForthWords::JUMP_IF_FALSE", "[PrimitiveForthWords::JUMP_IF_FALSE]" ) {
	CompositeForthWord word(
			CompositeForthWordBuilder("")
					.append(static_cast<ForthCell::INT_TYPE>(32))
					.append(static_cast<ForthCell::INT_TYPE>(42))
					.build()
	);
	ForthThread thread = ForthThread(&word);
	REQUIRE(thread.getDataStackSize() == 0);
	REQUIRE(thread.getIndex() == 0);
	thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(true));
	PrimitiveForthWords::JUMP_IF_FALSE.execute(thread);
	REQUIRE(thread.getDataStackSize() == 0);
	REQUIRE(thread.getIndex() == 1);
	thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(false));
	PrimitiveForthWords::JUMP_IF_FALSE.execute(thread);
	REQUIRE(thread.getDataStackSize() == 0);
	REQUIRE(thread.getIndex() == 42);
}

PrimitiveForthWordFunction PrimitiveForthWords::RETURN(&PrimitiveForthWords::F_RETURN, "PrimitiveForthWords::RETURN");
void PrimitiveForthWords::F_RETURN(ForthThread &thread) {
	thread.popFrame();
    thread.setTraceDepth(thread.getTraceDepth() - 1);
}

PrimitiveForthWordFunction PrimitiveForthWords::EXECUTE(&PrimitiveForthWords::F_EXECUTE, "PrimitiveForthWords::EXECUTE");
void PrimitiveForthWords::F_EXECUTE(ForthThread &thread) {
	// hey jf - will this actually work for both primitive and composite words?
	ForthWord *word = thread.popDataStack().word;
	word->execute(thread);
}

// -- value ; pushes next cell in word onto data stack
PrimitiveForthWordFunction PrimitiveForthWords::PUSH_NEXT_CELL(&PrimitiveForthWords::F_PUSH_NEXT_CELL, "PrimitiveForthWords::PUSH_NEXT_CELL", {ParamType::INT });
void PrimitiveForthWords::F_PUSH_NEXT_CELL(ForthThread &thread) {
	thread.pushDataStack(thread.getNextCell());
}

PrimitiveForthWordFunction PrimitiveForthWords::CHAR_SIZE(&PrimitiveForthWords::F_CHAR_SIZE, "PrimitiveForthWords::CHAR_SIZE");
void PrimitiveForthWords::F_CHAR_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::CHAR_TYPE));
}

PrimitiveForthWordFunction PrimitiveForthWords::INT_SIZE(&PrimitiveForthWords::F_INT_SIZE, "PrimitiveForthWords::INT_SIZE");
void PrimitiveForthWords::F_INT_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::INT_TYPE));
}

PrimitiveForthWordFunction PrimitiveForthWords::PTR_SIZE(&PrimitiveForthWords::F_PTR_SIZE, "PrimitiveForthWords::PTR_SIZE");
void PrimitiveForthWords::F_PTR_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::PTR_TYPE));
}

PrimitiveForthWordFunction PrimitiveForthWords::WORD_SIZE(&PrimitiveForthWords::F_WORD_SIZE, "PrimitiveForthWords::WORD_SIZE");
void PrimitiveForthWords::F_WORD_SIZE(ForthThread& thread) {
    thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::word));
}

PrimitiveForthWordFunction PrimitiveForthWords::ALLOC(&PrimitiveForthWords::F_ALLOC, "PrimitiveForthWords::ALLOC");
void PrimitiveForthWords::F_ALLOC(ForthThread& thread) {
    ForthCell::INT_TYPE size = thread.popDataStack().integer;
    thread.pushDataStack((ForthCell::PTR_TYPE)new char[size]);
}

PrimitiveForthWordFunction PrimitiveForthWords::FREE(&PrimitiveForthWords::F_FREE, "PrimitiveForthWords::FREE");
void PrimitiveForthWords::F_FREE(ForthThread& thread) {
    ForthCell::PTR_TYPE ptr = thread.popDataStack().pointer;
    delete[] static_cast<char*>(ptr);
}

// addr - char
PrimitiveForthWordFunction PrimitiveForthWords::CHAR_AT(&PrimitiveForthWords::F_CHAR_AT, "PrimitiveForthWords::CHAR_AT");
void PrimitiveForthWords::F_CHAR_AT(ForthThread& thread) {
    ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
    thread.pushDataStack(*ptr);
}

// char addr --
PrimitiveForthWordFunction PrimitiveForthWords::CHAR_PUT(&PrimitiveForthWords::F_CHAR_PUT, "PrimitiveForthWords::CHAR_PUT");
void PrimitiveForthWords::F_CHAR_PUT(ForthThread& thread) {
    ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
    (*ptr) = static_cast<char>(thread.popDataStack().integer);
}

// ndx addr -- addr
PrimitiveForthWordFunction PrimitiveForthWords::CHAR_INDEX(&PrimitiveForthWords::F_CHAR_INDEX, "PrimitiveForthWords::CHAR_INDEX");
void PrimitiveForthWords::F_CHAR_INDEX(ForthThread& thread) {
    ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
    ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
    thread.pushDataStack(&ptr[ndx]);
}

// addr - INT
PrimitiveForthWordFunction PrimitiveForthWords::INT_AT(&PrimitiveForthWords::F_INT_AT, "PrimitiveForthWords::INT_AT");
void PrimitiveForthWords::F_INT_AT(ForthThread& thread) {
    ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
    thread.pushDataStack(*ptr);
}

// INT addr --
PrimitiveForthWordFunction PrimitiveForthWords::INT_PUT(&PrimitiveForthWords::F_INT_PUT, "PrimitiveForthWords::INT_PUT");
void PrimitiveForthWords::F_INT_PUT(ForthThread& thread) {
    ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
    (*ptr) = thread.popDataStack().integer;
}

// ndx addr -- addr
PrimitiveForthWordFunction PrimitiveForthWords::INT_INDEX(&PrimitiveForthWords::F_INT_INDEX, "PrimitiveForthWords::INT_INDEX");
void PrimitiveForthWords::F_INT_INDEX(ForthThread& thread) {
    ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
    ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
    thread.pushDataStack(&ptr[ndx]);
}

// addr - CELL
PrimitiveForthWordFunction PrimitiveForthWords::CELL_AT(&PrimitiveForthWords::F_CELL_AT, "PrimitiveForthWords::CELL_AT");
void PrimitiveForthWords::F_CELL_AT(ForthThread& thread) {
    ForthCell::CELL_TYPE* ptr = static_cast<ForthCell::CELL_TYPE*>(thread.popDataStack().pointer);
    thread.pushDataStack(*ptr);
}

// CELL addr --
PrimitiveForthWordFunction PrimitiveForthWords::CELL_PUT(&PrimitiveForthWords::F_CELL_PUT, "PrimitiveForthWords::CELL_PUT");
void PrimitiveForthWords::F_CELL_PUT(ForthThread& thread) {
    ForthCell::CELL_TYPE* ptr = static_cast<ForthCell::CELL_TYPE*>(thread.popDataStack().pointer);
    (*ptr) = thread.popDataStack().word;
}

// ndx addr -- addr
PrimitiveForthWordFunction PrimitiveForthWords::CELL_INDEX(&PrimitiveForthWords::F_CELL_INDEX, "PrimitiveForthWords::CELL_INDEX");
void PrimitiveForthWords::F_CELL_INDEX(ForthThread& thread) {
    ForthCell::CELL_TYPE* ptr = static_cast<ForthCell::CELL_TYPE*>(thread.popDataStack().pointer);
    ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
    thread.pushDataStack(&ptr[ndx]);
}

PrimitiveForthWordFunction PrimitiveForthWords::TO_RETURN_STACK(&PrimitiveForthWords::F_TO_RETURN_STACK, "PrimitiveForthWords::TO_RETURN_STACK");
void PrimitiveForthWords::F_TO_RETURN_STACK(ForthThread& thread) {
    thread.toReturnStack(thread.popDataStack());
}

PrimitiveForthWordFunction PrimitiveForthWords::FROM_RETURN_STACK(&PrimitiveForthWords::F_FROM_RETURN_STACK, "PrimitiveForthWords::FROM_RETURN_STACK");
void PrimitiveForthWords::F_FROM_RETURN_STACK(ForthThread& thread) {
    thread.pushDataStack(thread.fromReturnStack().cell);
}

PrimitiveForthWordFunction PrimitiveForthWords::AT_RETURN_STACK(&PrimitiveForthWords::F_FROM_RETURN_STACK, "PrimitiveForthWords::FROM_RETURN_STACK");
void PrimitiveForthWords::F_AT_RETURN_STACK(ForthThread &thread) {
    thread.pushDataStack(thread.topOfReturnStack().cell);
}

PrimitiveForthWordFunction PrimitiveForthWords::SWAP(&PrimitiveForthWords::F_SWAP, "PrimitiveForthWords::SWAP");
void PrimitiveForthWords::F_SWAP(ForthThread& thread) {
    ForthCell v1 = thread.popDataStack();
    ForthCell v2 = thread.popDataStack();
    thread.pushDataStack(v1);
    thread.pushDataStack(v2);
}

// ( a0 .. an n -- a0 .. an a0 )
PrimitiveForthWordFunction PrimitiveForthWords::PICK(&PrimitiveForthWords::F_PICK, "PrimitiveForthWords::PICK");
void PrimitiveForthWords::F_PICK(ForthThread& thread) {
    thread.pushDataStack(thread[thread.popDataStack().integer]);
}

// ( a0 .. an n -- a0 .. an a0 )
PrimitiveForthWordFunction PrimitiveForthWords::OVER(&PrimitiveForthWords::F_OVER, "PrimitiveForthWords::OVER");
void PrimitiveForthWords::F_OVER(ForthThread& thread) {
    thread.pushDataStack(thread[1]);
}

// ( a0 .. an n -- a1 .. an a0 )
PrimitiveForthWordFunction PrimitiveForthWords::ROLL(&PrimitiveForthWords::F_ROLL, "PrimitiveForthWords::ROLL");
void PrimitiveForthWords::F_ROLL(ForthThread& thread) {
    thread.rollDataStack(thread.popDataStack().integer);
}

PrimitiveForthWordFunction PrimitiveForthWords::DROP(&PrimitiveForthWords::F_DROP, "PrimitiveForthWords::DROP");
void PrimitiveForthWords::F_DROP(ForthThread& thread) {
    thread.popDataStack();
}

PrimitiveForthWordFunction PrimitiveForthWords::DUP(&PrimitiveForthWords::F_DUP, "PrimitiveForthWords::DUP");
void PrimitiveForthWords::F_DUP(ForthThread& thread) {
    thread.pushDataStack(thread[0]);
}

PrimitiveForthWordFunction PrimitiveForthWords::ADD(&PrimitiveForthWords::F_ADD, "PrimitiveForthWords::ADD", "+");
void PrimitiveForthWords::F_ADD(ForthThread& thread) {
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	thread.pushDataStack(x + y);
}

// a b -- (a - b)
PrimitiveForthWordFunction PrimitiveForthWords::SUBTRACT(&PrimitiveForthWords::F_SUBTRACT, "PrimitiveForthWords::SUBTRACT", "-");
void PrimitiveForthWords::F_SUBTRACT(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
	ForthCell::INT_TYPE subtrahend = thread.popDataStack().integer;
	ForthCell::INT_TYPE value = thread.popDataStack().integer;
    thread.pushDataStack(value - subtrahend);
}

PrimitiveForthWordFunction PrimitiveForthWords::MULTIPLY(&PrimitiveForthWords::F_MULTIPLY, "PrimitiveForthWords::MULTIPLY", "*");
void PrimitiveForthWords::F_MULTIPLY(ForthThread& thread) {
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
    thread.pushDataStack(x * y);
}

// x y -- (x / y)
PrimitiveForthWordFunction PrimitiveForthWords::DIVIDE(&PrimitiveForthWords::F_DIVIDE, "PrimitiveForthWords::DIVIDE", "/");
void PrimitiveForthWords::F_DIVIDE(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
	ForthCell::INT_TYPE divisor = thread.popDataStack().integer;
	ForthCell::INT_TYPE dividend = thread.popDataStack().integer;
    thread.pushDataStack(dividend / divisor);
}

// x y -- (x % y)
PrimitiveForthWordFunction PrimitiveForthWords::MOD(&PrimitiveForthWords::F_MOD, "PrimitiveForthWords::MOD", "%");
void PrimitiveForthWords::F_MOD(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
	ForthCell::INT_TYPE modulus = thread.popDataStack().integer;
	ForthCell::INT_TYPE value = thread.popDataStack().integer;
    
    thread.pushDataStack(value % modulus);
}


// x y -- (x < y)
PrimitiveForthWordFunction PrimitiveForthWords::LESS_THAN(&PrimitiveForthWords::F_LESS_THAN, "PrimitiveForthWords::LESS_THAN", "<");
void PrimitiveForthWords::F_LESS_THAN(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
    thread.pushDataStack(x < y);
}

// x y -- (x > y)
PrimitiveForthWordFunction PrimitiveForthWords::GREATER_THAN(&PrimitiveForthWords::F_GREATER_THAN, "PrimitiveForthWords::GREATER_THAN", ">");
void PrimitiveForthWords::F_GREATER_THAN(ForthThread& thread) {
    // note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
    // of expression operands is undefined.
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
    thread.pushDataStack(x > y);
}

// x y -- (x == y)
PrimitiveForthWordFunction PrimitiveForthWords::EQUAL(&PrimitiveForthWords::F_EQUAL, "PrimitiveForthWords::EQUAL", "=");
void PrimitiveForthWords::F_EQUAL(ForthThread& thread) {
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
    thread.pushDataStack(x == y);
}

// x y -- (x && y)
PrimitiveForthWordFunction PrimitiveForthWords::CONDITIONAL_AND(&PrimitiveForthWords::F_CONDITIONAL_AND, "PrimitiveForthWords::AND", "&&");
void PrimitiveForthWords::F_CONDITIONAL_AND(ForthThread& thread) {
	bool b1 = static_cast<bool>(thread.popDataStack().integer);
	bool b2 = static_cast<bool>(thread.popDataStack().integer);
    thread.pushDataStack(b1 && b2);
}

// x y -- (x && y)
PrimitiveForthWordFunction PrimitiveForthWords::CONDITIONAL_OR(&PrimitiveForthWords::F_CONDITIONAL_OR, "PrimitiveForthWords::OR", "||");
void PrimitiveForthWords::F_CONDITIONAL_OR(ForthThread& thread) {
	bool b1 = static_cast<bool>(thread.popDataStack().integer);
	bool b2 = static_cast<bool>(thread.popDataStack().integer);
    thread.pushDataStack(b1 && b2);
}

// x -- !x)
PrimitiveForthWordFunction PrimitiveForthWords::CONDITIONAL_NOT(&PrimitiveForthWords::F_CONDITIONAL_NOT, "PrimitiveForthWords::NOT");
void PrimitiveForthWords::F_CONDITIONAL_NOT(ForthThread& thread) {
    thread.pushDataStack(!static_cast<bool>(thread.popDataStack().integer));
}

PrimitiveForthWordFunction PrimitiveForthWords::ACCEPT_INPUT(&PrimitiveForthWords::F_ACCEPT_INPUT, "PrimitiveForthWords::ACCEPT_INPUT");
void PrimitiveForthWords::F_ACCEPT_INPUT(ForthThread& thread) {
    ForthCell::INT_TYPE size = thread.popDataStack().integer;
    ForthCell::PTR_TYPE ptr = thread.popDataStack().pointer;
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(NativeOSFunctions::accept(static_cast<char*>(ptr), size)));
}

PrimitiveForthWordFunction PrimitiveForthWords::PEEK_NEXT_INPUT_CHAR(&PrimitiveForthWords::F_PEEK_NEXT_INPUT_CHAR, "PrimitiveForthWords::PEEK_NEXT_INPUT_CHAR");
void PrimitiveForthWords::F_PEEK_NEXT_INPUT_CHAR(ForthThread& thread) {
    thread.pushDataStack(NativeOSFunctions::peekNextChar());
}

PrimitiveForthWordFunction PrimitiveForthWords::GET_NEXT_INPUT_CHAR(&PrimitiveForthWords::F_GET_NEXT_INPUT_CHAR, "PrimitiveForthWords::GET_NEXT_INPUT_CHAR");
void PrimitiveForthWords::F_GET_NEXT_INPUT_CHAR(ForthThread& thread) {
    thread.pushDataStack(NativeOSFunctions::nextChar());
}

PrimitiveForthWordFunction PrimitiveForthWords::PRINT_CHAR(&PrimitiveForthWords::F_PRINT_CHAR, "PrimitiveForthWords::PRINT_CHAR");
void PrimitiveForthWords::F_PRINT_CHAR(ForthThread& thread) {
    NativeOSFunctions::printChar(static_cast<char>(thread.popDataStack().integer));
}

PrimitiveForthWordFunction PrimitiveForthWords::FALSE(&PrimitiveForthWords::F_FALSE, "PrimitiveForthWords::FALSE");
void PrimitiveForthWords::F_FALSE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(false));
}

PrimitiveForthWordFunction PrimitiveForthWords::TRUE(&PrimitiveForthWords::F_TRUE, "PrimitiveForthWords::TRUE");
void PrimitiveForthWords::F_TRUE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(true));
}

PrimitiveForthWordFunction PrimitiveForthWords::ZERO(&PrimitiveForthWords::F_ZERO, "PrimitiveForthWords::ZERO");
void PrimitiveForthWords::F_ZERO(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(0));
}

PrimitiveForthWordFunction PrimitiveForthWords::ONE(&PrimitiveForthWords::F_ONE, "PrimitiveForthWords::ONE", "1");
void PrimitiveForthWords::F_ONE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(1));
}

PrimitiveForthWordFunction PrimitiveForthWords::NEGATIVE_ONE(&PrimitiveForthWords::F_NEGATIVE_ONE, "PrimitiveForthWords::NEGATIVE_ONE", "-1");
void PrimitiveForthWords::F_NEGATIVE_ONE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(-1));
}

PrimitiveForthWordFunction PrimitiveForthWords::ADD_ONE(&PrimitiveForthWords::F_ADD_ONE, "PrimitiveForthWords::ADD_ONE", "+=1");
void PrimitiveForthWords::F_ADD_ONE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(1 + thread.popDataStack().integer));
}

PrimitiveForthWordFunction PrimitiveForthWords::SUBTRACT_ONE(&PrimitiveForthWords::F_ADD_ONE, "PrimitiveForthWords::SUBTRACT_ONE", "-=1");
void PrimitiveForthWords::F_SUBTRACT_ONE(ForthThread &thread) {
    thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(thread.popDataStack().integer - 1));
}

