//
// Created by Dad on 9/17/19.
//

#include "PrimitiveForthWords.h"
#include "runtime/ForthThread.h"
#include "runtime/CompositeForthWord.h"
#include "runtime/NativeOSFunctions.hpp"

PrimitiveForthWords::PrimitiveForthWords(ForthVocab *next)
	: ForthVocab(next)
{
	add(&NOP);
	add(&JUMP);
	add(&JUMP_IF_FALSE);
	add(&RETURN);
	add(&EXIT_THREAD);
	add(&EXECUTE);
	add(&PUSH_NEXT_CELL);
	add(&CHAR_SIZE);
	add(&INT_SIZE);
	add(&PTR_SIZE);
	add(&WORD_SIZE);
	add(&ALLOC);
	add(&FREE);
	add(&REGISTER);
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
	add(&TRACE);
}

using ParamType = PrimitiveForthWordFunction::ParamType;

static void F_NOP(ForthThread& thread) {
}
PrimitiveForthWordFunction PrimitiveForthWords::NOP(&F_NOP, "PrimitiveForthWords::NOP", "nop");

static void F_JUMP(ForthThread &thread) {
	thread.setIndex(thread.getNextCell().integer);
}
PrimitiveForthWordFunction PrimitiveForthWords::JUMP(&F_JUMP,
		"PrimitiveForthWords::JUMP", "(branch)",{ParamType::INT });

// bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
static void F_JUMP_IF_FALSE(ForthThread &thread) {
	int newNdx = thread.getNextCell().integer;  // consume next cell always
	if (!thread.popDataStack().integer) {
		thread.setIndex(newNdx);
	}
}
PrimitiveForthWordFunction PrimitiveForthWords::JUMP_IF_FALSE(&F_JUMP_IF_FALSE,
		"PrimitiveForthWords::JUMP_IF_FALSE", "(?branch)",{ParamType::INT });

static void F_RETURN(ForthThread &thread) {
	thread.popFrame();
	thread.setTraceDepth(thread.getTraceDepth() - 1);
}
PrimitiveForthWordFunction PrimitiveForthWords::RETURN(&F_RETURN,
		"PrimitiveForthWords::RETURN", "(return)");

static void F_EXIT_THREAD(ForthThread &thread) {
	throw ForthThread::ThreadExitException();
}
PrimitiveForthWordFunction PrimitiveForthWords::EXIT_THREAD(&F_EXIT_THREAD,
		"PrimitiveForthWords::EXIT_THREAD", "exitThread");

static void F_EXECUTE(ForthThread &thread) {
	ForthWord *word = thread.popDataStack().word;
	word->execute(thread);
}
PrimitiveForthWordFunction PrimitiveForthWords::EXECUTE(&F_EXECUTE,
		"PrimitiveForthWords::EXECUTE", "execute");

// -- value ; pushes next cell in word onto data stack
static void F_PUSH_NEXT_CELL(ForthThread &thread) {
	thread.pushDataStack(thread.getNextCell());
}
PrimitiveForthWordFunction PrimitiveForthWords::PUSH_NEXT_CELL(&F_PUSH_NEXT_CELL,
		"PrimitiveForthWords::PUSH_NEXT_CELL", "(PUSH_NEXT_CELL)", {ParamType::INT });

static void F_CHAR_SIZE(ForthThread& thread) {
	thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::CHAR_TYPE));
}
PrimitiveForthWordFunction PrimitiveForthWords::CHAR_SIZE(
		&F_CHAR_SIZE, "PrimitiveForthWords::CHAR_SIZE", "CHAR_SIZE");

static void F_INT_SIZE(ForthThread& thread) {
	thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::INT_TYPE));
}
PrimitiveForthWordFunction PrimitiveForthWords::INT_SIZE(&F_INT_SIZE, "PrimitiveForthWords::INT_SIZE", "INT_SIZE");

static void F_PTR_SIZE(ForthThread& thread) {
	thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::PTR_TYPE));
}
PrimitiveForthWordFunction PrimitiveForthWords::PTR_SIZE(&F_PTR_SIZE, "PrimitiveForthWords::PTR_SIZE", "PTR_SIZE");

static void F_WORD_SIZE(ForthThread& thread) {
	thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::word));
}
PrimitiveForthWordFunction PrimitiveForthWords::WORD_SIZE(
		&F_WORD_SIZE, "PrimitiveForthWords::WORD_SIZE", "WORD_SIZE");

static void F_ALLOC(ForthThread& thread) {
	ForthCell::INT_TYPE size = thread.popDataStack().integer;
	thread.pushDataStack((ForthCell::PTR_TYPE)new char[size]);
}
PrimitiveForthWordFunction PrimitiveForthWords::ALLOC(&F_ALLOC, "PrimitiveForthWords::ALLOC", "allocMem");

static void F_FREE(ForthThread& thread) {
	ForthCell::PTR_TYPE ptr = thread.popDataStack().pointer;
	delete[] static_cast<char*>(ptr);
}
PrimitiveForthWordFunction PrimitiveForthWords::FREE(&F_FREE, "PrimitiveForthWords::FREE", "freeMem");

thread_local ForthCell PrimitiveForthWords::registers[THREAD_STORAGE_SIZE];
static void F_REGISTERS(ForthThread& thread) {
	thread.pushDataStack(static_cast<ForthCell::PTR_TYPE>(PrimitiveForthWords::registers));
}
PrimitiveForthWordFunction PrimitiveForthWords::REGISTER(&F_REGISTERS, "PrimitiveForthWords::REGISTERS", "registers");

// addr - char
static void F_CHAR_AT(ForthThread& thread) {
	ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
	thread.pushDataStack(*ptr);
}
PrimitiveForthWordFunction PrimitiveForthWords::CHAR_AT(&F_CHAR_AT, "PrimitiveForthWords::CHAR_AT", "c@");

// char addr --
static void F_CHAR_PUT(ForthThread& thread) {
	ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
	(*ptr) = static_cast<char>(thread.popDataStack().integer);
}
PrimitiveForthWordFunction PrimitiveForthWords::CHAR_PUT(&F_CHAR_PUT, "PrimitiveForthWords::CHAR_PUT", "c!");

// ndx addr -- addr
static void F_CHAR_INDEX(ForthThread& thread) {
	ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
	ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
	thread.pushDataStack(&ptr[ndx]);
}
PrimitiveForthWordFunction PrimitiveForthWords::CHAR_INDEX(&F_CHAR_INDEX, "PrimitiveForthWords::CHAR_INDEX", "c[]");

// addr - INT
static void F_INT_AT(ForthThread& thread) {
	ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
	thread.pushDataStack(*ptr);
}
PrimitiveForthWordFunction PrimitiveForthWords::INT_AT(&F_INT_AT, "PrimitiveForthWords::INT_AT", "@");

// INT addr --
static void F_INT_PUT(ForthThread& thread) {
	ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
	(*ptr) = thread.popDataStack().integer;
}
PrimitiveForthWordFunction PrimitiveForthWords::INT_PUT(&F_INT_PUT, "PrimitiveForthWords::INT_PUT", "!");

// ndx addr -- addr
static void F_INT_INDEX(ForthThread& thread) {
	ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
	ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
	thread.pushDataStack(&ptr[ndx]);
}
PrimitiveForthWordFunction PrimitiveForthWords::INT_INDEX(&F_INT_INDEX,
		"PrimitiveForthWords::INT_INDEX", "[]");

// addr - CELL
static void F_CELL_AT(ForthThread& thread) {
	ForthCell::WORD_TYPE* ptr = static_cast<ForthCell::WORD_TYPE*>(thread.popDataStack().pointer);
	thread.pushDataStack(*ptr);
}
PrimitiveForthWordFunction PrimitiveForthWords::CELL_AT(&F_CELL_AT,
		"PrimitiveForthWords::CELL_AT", "w@");

// CELL addr --
static void F_CELL_PUT(ForthThread& thread) {
	ForthCell::WORD_TYPE* ptr = static_cast<ForthCell::WORD_TYPE*>(thread.popDataStack().pointer);
	(*ptr) = thread.popDataStack().word;
}
PrimitiveForthWordFunction PrimitiveForthWords::CELL_PUT(&F_CELL_PUT,
		"PrimitiveForthWords::CELL_PUT", "w!");

// ndx addr -- addr
static void F_CELL_INDEX(ForthThread& thread) {
	ForthCell::WORD_TYPE* ptr = static_cast<ForthCell::WORD_TYPE*>(thread.popDataStack().pointer);
	ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
	thread.pushDataStack(&ptr[ndx]);
}
PrimitiveForthWordFunction PrimitiveForthWords::CELL_INDEX(&F_CELL_INDEX,
		"PrimitiveForthWords::CELL_INDEX", "w[]");

static void F_TO_RETURN_STACK(ForthThread& thread) {
	thread.toReturnStack(thread.popDataStack());
}
PrimitiveForthWordFunction PrimitiveForthWords::TO_RETURN_STACK(&F_TO_RETURN_STACK,
		"PrimitiveForthWords::TO_RETURN_STACK", ">r");

static void F_FROM_RETURN_STACK(ForthThread& thread) {
	thread.pushDataStack(thread.fromReturnStack().cell);
}
PrimitiveForthWordFunction PrimitiveForthWords::FROM_RETURN_STACK(&F_FROM_RETURN_STACK,
		"PrimitiveForthWords::FROM_RETURN_STACK", "r>");

static void F_AT_RETURN_STACK(ForthThread &thread) {
	thread.pushDataStack(thread.topOfReturnStack().cell);
}
PrimitiveForthWordFunction PrimitiveForthWords::AT_RETURN_STACK(&F_AT_RETURN_STACK,
		"PrimitiveForthWords::AT_RETURN_STACK", "r@");

static void F_SWAP(ForthThread& thread) {
	ForthCell v1 = thread.popDataStack();
	ForthCell v2 = thread.popDataStack();
	thread.pushDataStack(v1);
	thread.pushDataStack(v2);
}
PrimitiveForthWordFunction PrimitiveForthWords::SWAP(&F_SWAP,
		"PrimitiveForthWords::SWAP", "swap");

// ( a0 .. an n -- a0 .. an a0 )
static void F_PICK(ForthThread& thread) {
	thread.pushDataStack(thread[thread.popDataStack().integer]);
}
PrimitiveForthWordFunction PrimitiveForthWords::PICK(&F_PICK,
		"PrimitiveForthWords::PICK", "pick");

// ( a0 .. an n -- a0 .. an a0 )
static void F_OVER(ForthThread& thread) {
	thread.pushDataStack(thread[1]);
}
PrimitiveForthWordFunction PrimitiveForthWords::OVER(&F_OVER,
		"PrimitiveForthWords::OVER", "over");

// ( a0 .. an n -- a1 .. an a0 )
static void F_ROLL(ForthThread& thread) {
	thread.rollDataStack(thread.popDataStack().integer);
}
PrimitiveForthWordFunction PrimitiveForthWords::ROLL(&F_ROLL,
		"PrimitiveForthWords::ROLL", "roll");

static void F_DROP(ForthThread& thread) {
	thread.popDataStack();
}
PrimitiveForthWordFunction PrimitiveForthWords::DROP(&F_DROP,
		"PrimitiveForthWords::DROP", "drop");

static void F_DUP(ForthThread& thread) {
	thread.pushDataStack(thread[0]);
}
PrimitiveForthWordFunction PrimitiveForthWords::DUP(&F_DUP,
		"PrimitiveForthWords::DUP", "dup");

static void F_ADD(ForthThread& thread) {
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	thread.pushDataStack(x + y);
}
PrimitiveForthWordFunction PrimitiveForthWords::ADD(&F_ADD,
		"PrimitiveForthWords::ADD", "+");

// a b -- (a - b)
static void F_SUBTRACT(ForthThread& thread) {
	// note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
	// of expression operands is undefined.
	ForthCell::INT_TYPE subtrahend = thread.popDataStack().integer;
	ForthCell::INT_TYPE value = thread.popDataStack().integer;
	thread.pushDataStack(value - subtrahend);
}
PrimitiveForthWordFunction PrimitiveForthWords::SUBTRACT(&F_SUBTRACT,
		"PrimitiveForthWords::SUBTRACT", "-");

static void F_MULTIPLY(ForthThread& thread) {
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	thread.pushDataStack(x * y);
}
PrimitiveForthWordFunction PrimitiveForthWords::MULTIPLY(&F_MULTIPLY,
		"PrimitiveForthWords::MULTIPLY", "*");

// x y -- (x / y)
static void F_DIVIDE(ForthThread& thread) {
	// note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
	// of expression operands is undefined.
	ForthCell::INT_TYPE divisor = thread.popDataStack().integer;
	ForthCell::INT_TYPE dividend = thread.popDataStack().integer;
	thread.pushDataStack(dividend / divisor);
}
PrimitiveForthWordFunction PrimitiveForthWords::DIVIDE(&F_DIVIDE,
		"PrimitiveForthWords::DIVIDE", "/");

// x y -- (x % y)
static void F_MOD(ForthThread& thread) {
	// note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
	// of expression operands is undefined.
	ForthCell::INT_TYPE modulus = thread.popDataStack().integer;
	ForthCell::INT_TYPE value = thread.popDataStack().integer;

	thread.pushDataStack(value % modulus);
}
PrimitiveForthWordFunction PrimitiveForthWords::MOD(&F_MOD, "PrimitiveForthWords::MOD", "%");

// x y -- (x < y)
static void F_LESS_THAN(ForthThread& thread) {
	// note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
	// of expression operands is undefined.
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	thread.pushDataStack(x < y);
}
PrimitiveForthWordFunction PrimitiveForthWords::LESS_THAN(&F_LESS_THAN,
		"PrimitiveForthWords::LESS_THAN", "<");

// x y -- (x > y)
static void F_GREATER_THAN(ForthThread& thread) {
	// note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
	// of expression operands is undefined.
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	thread.pushDataStack(x > y);
}
PrimitiveForthWordFunction PrimitiveForthWords::GREATER_THAN(&F_GREATER_THAN,
		"PrimitiveForthWords::GREATER_THAN", ">");

// x y -- (x == y)
static void F_EQUAL(ForthThread& thread) {
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	thread.pushDataStack(x == y);
}
PrimitiveForthWordFunction PrimitiveForthWords::EQUAL(&F_EQUAL, "PrimitiveForthWords::EQUAL", "=");

// x y -- (x && y)
static void F_CONDITIONAL_AND(ForthThread& thread) {
	bool b1 = static_cast<bool>(thread.popDataStack().integer);
	bool b2 = static_cast<bool>(thread.popDataStack().integer);
	thread.pushDataStack(b1 && b2);
}
PrimitiveForthWordFunction PrimitiveForthWords::CONDITIONAL_AND(
		&F_CONDITIONAL_AND, "PrimitiveForthWords::AND", "&&");

// x y -- (x && y)
static void F_CONDITIONAL_OR(ForthThread& thread) {
	bool b1 = static_cast<bool>(thread.popDataStack().integer);
	bool b2 = static_cast<bool>(thread.popDataStack().integer);
	thread.pushDataStack(b1 && b2);
}
PrimitiveForthWordFunction PrimitiveForthWords::CONDITIONAL_OR(
		&F_CONDITIONAL_OR, "PrimitiveForthWords::OR", "||");

// x -- !x)
static void F_CONDITIONAL_NOT(ForthThread& thread) {
	thread.pushDataStack(!static_cast<bool>(thread.popDataStack().integer));
}
PrimitiveForthWordFunction PrimitiveForthWords::CONDITIONAL_NOT(
		&F_CONDITIONAL_NOT, "PrimitiveForthWords::NOT", "not");

static void F_ACCEPT_INPUT(ForthThread& thread) {
	ForthCell::INT_TYPE size = thread.popDataStack().integer;
	ForthCell::PTR_TYPE ptr = thread.popDataStack().pointer;
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(NativeOSFunctions::accept(static_cast<char*>(ptr), size)));
}
PrimitiveForthWordFunction PrimitiveForthWords::ACCEPT_INPUT(&F_ACCEPT_INPUT,
		"PrimitiveForthWords::ACCEPT_INPUT", "acceptInput");

static void F_PEEK_NEXT_INPUT_CHAR(ForthThread& thread) {
	thread.pushDataStack(NativeOSFunctions::peekNextChar());
}
PrimitiveForthWordFunction PrimitiveForthWords::PEEK_NEXT_INPUT_CHAR(&F_PEEK_NEXT_INPUT_CHAR,
		"PrimitiveForthWords::PEEK_NEXT_INPUT_CHAR", "peekInput");

static void F_GET_NEXT_INPUT_CHAR(ForthThread& thread) {
	thread.pushDataStack(NativeOSFunctions::nextChar());
}
PrimitiveForthWordFunction PrimitiveForthWords::GET_NEXT_INPUT_CHAR(&F_GET_NEXT_INPUT_CHAR,
		"PrimitiveForthWords::GET_NEXT_INPUT_CHAR", "getInput");

static void F_FLUSH_INPUT(ForthThread& thread) {
	NativeOSFunctions::flushInput();
}
PrimitiveForthWordFunction PrimitiveForthWords::FLUSH_INPUT(&F_FLUSH_INPUT,
		"PrimitiveForthWords::FLUSH_INPUT", "flushInput");

static void F_PRINT_CHAR(ForthThread& thread) {
	NativeOSFunctions::printChar(static_cast<char>(thread.popDataStack().integer));
}
PrimitiveForthWordFunction PrimitiveForthWords::PRINT_CHAR(&F_PRINT_CHAR,
		"PrimitiveForthWords::PRINT_CHAR", "printChar");

static void F_FALSE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(false));
}
PrimitiveForthWordFunction PrimitiveForthWords::FALSE(&F_FALSE, "PrimitiveForthWords::FALSE", "false");

static void F_TRUE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(true));
}
PrimitiveForthWordFunction PrimitiveForthWords::TRUE(&F_TRUE, "PrimitiveForthWords::TRUE", "true");

static void F_ZERO(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(0));
}
PrimitiveForthWordFunction PrimitiveForthWords::ZERO(&F_ZERO, "PrimitiveForthWords::ZERO", "0");

static void F_ONE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(1));
}
PrimitiveForthWordFunction PrimitiveForthWords::ONE(&F_ONE, "PrimitiveForthWords::ONE", "1");

static void F_NEGATIVE_ONE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(-1));
}
PrimitiveForthWordFunction PrimitiveForthWords::NEGATIVE_ONE(
		&F_NEGATIVE_ONE, "PrimitiveForthWords::NEGATIVE_ONE", "-1");

static void F_ADD_ONE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(1 + thread.popDataStack().integer));
}
PrimitiveForthWordFunction PrimitiveForthWords::ADD_ONE(&F_ADD_ONE, "PrimitiveForthWords::ADD_ONE", "+=1");

static void F_SUBTRACT_ONE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(thread.popDataStack().integer - 1));
}
PrimitiveForthWordFunction PrimitiveForthWords::SUBTRACT_ONE(
		&F_SUBTRACT_ONE, "PrimitiveForthWords::SUBTRACT_ONE", "-=1");

static void F_TRACE(ForthThread &thread) {
	thread.enableTrace(thread.popDataStack().integer);
}
PrimitiveForthWordFunction PrimitiveForthWords::TRACE(
		&F_TRACE, "PrimitiveForthWords::TRACE", "trace");

