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
	add(&NOP());
	add(&JUMP());
	add(&JUMP_IF_FALSE());
	add(&RETURN());
	add(&EXIT_THREAD());
	add(&EXECUTE());
	add(&PUSH_NEXT_CELL());
	add(&CHAR_SIZE());
	add(&INT_SIZE());
	add(&PTR_SIZE());
	add(&WORD_SIZE());
	add(&ALLOC());
	add(&FREE());
	add(&REGISTER());
	add(&CHAR_AT());
	add(&CHAR_PUT());
	add(&CHAR_INDEX());
	add(&INT_AT());
	add(&INT_PUT());
	add(&INT_INDEX());
	add(&CELL_AT());
	add(&CELL_PUT());
	add(&CELL_INDEX());
	add(&TO_RETURN_STACK());
	add(&FROM_RETURN_STACK());
	add(&AT_RETURN_STACK());
	add(&SWAP());
	add(&PICK());
	add(&OVER());
	add(&ROLL());
	add(&DROP());
	add(&DUP());
	add(&ADD());
	add(&SUBTRACT());
	add(&MULTIPLY());
	add(&DIVIDE());
	add(&MOD());
	add(&LESS_THAN());
	add(&GREATER_THAN());
	add(&EQUAL());
	add(&CONDITIONAL_AND());
	add(&CONDITIONAL_OR());
	add(&CONDITIONAL_NOT());
	add(&ACCEPT_INPUT());
	add(&PEEK_NEXT_INPUT_CHAR());
	add(&GET_NEXT_INPUT_CHAR());
	add(&PRINT_CHAR());
	add(&FALSE());
	add(&TRUE());
	add(&ZERO());
	add(&ONE());
	add(&NEGATIVE_ONE());
	add(&ADD_ONE());
	add(&SUBTRACT_ONE());
	add(&TRACE());
}

using ParamType = PrimitiveForthWordFunction::ParamType;

static void F_NOP(ForthThread& thread) {
}
ForthWord& PrimitiveForthWords::NOP() {
	static PrimitiveForthWordFunction word(&F_NOP, "PrimitiveForthWords::NOP", "nop");
	return word;
}

static void F_JUMP(ForthThread &thread) {
	thread.setIndex(thread.getNextCell().integer);
}
ForthWord& PrimitiveForthWords::JUMP() {
	static PrimitiveForthWordFunction word(&F_JUMP,
		"PrimitiveForthWords::JUMP", "(branch)",{PrimitiveForthWordFunction::INT });
	return word;
}

// bool --   if the tos is false, the next cell is set as the ip.ndx else it's just skipped
static void F_JUMP_IF_FALSE(ForthThread &thread) {
	int newNdx = thread.getNextCell().integer;  // consume next cell always
	if (!thread.popDataStack().integer) {
		thread.setIndex(newNdx);
	}
}
ForthWord& PrimitiveForthWords::JUMP_IF_FALSE() {
	static PrimitiveForthWordFunction word(&F_JUMP_IF_FALSE,
		"PrimitiveForthWords::JUMP_IF_FALSE", "(?branch)", {PrimitiveForthWordFunction::INT });
	return word;
}

static void F_RETURN(ForthThread &thread) {
	thread.popFrame();
	thread.setTraceDepth(thread.getTraceDepth() - 1);
}
ForthWord& PrimitiveForthWords::RETURN() {
	static PrimitiveForthWordFunction word(&F_RETURN,
		"PrimitiveForthWords::RETURN", "(return)");
	return word;
}

static void F_RECURSE(ForthThread &thread) {
	thread.recurse();
	thread.setTraceDepth(thread.getTraceDepth() + 1);
}
ForthWord& PrimitiveForthWords::RECURSE() {
	static PrimitiveForthWordFunction word(&F_RECURSE,
			"PrimitiveForthWords::RECURSE", "(recurse)");
	return word;
}

static void F_EXIT_THREAD(ForthThread &thread) {
	throw ForthThread::ThreadExitException();
}
ForthWord& PrimitiveForthWords::EXIT_THREAD() {
	static PrimitiveForthWordFunction word(&F_EXIT_THREAD,
		"PrimitiveForthWords::EXIT_THREAD", "exitThread");
	return word;
}

static void F_EXECUTE(ForthThread &thread) {
	ForthWord *word = thread.popDataStack().word;
	word->execute(thread);
}
ForthWord& PrimitiveForthWords::EXECUTE() {
	static PrimitiveForthWordFunction word(&F_EXECUTE,
		"PrimitiveForthWords::EXECUTE", "execute");
	return word;
}

// -- value ; pushes next cell in word onto data stack
static void F_PUSH_NEXT_CELL(ForthThread &thread) {
	thread.pushDataStack(thread.getNextCell());
}
ForthWord& PrimitiveForthWords::PUSH_NEXT_CELL() {
	static PrimitiveForthWordFunction word(&F_PUSH_NEXT_CELL,
		"PrimitiveForthWords::PUSH_NEXT_CELL", "(literal)", {PrimitiveForthWordFunction::INT });
	return word;
}

static void F_TO_RETURN_STACK(ForthThread& thread) {
	thread.toReturnStack(thread.popDataStack());
}
ForthWord& PrimitiveForthWords::TO_RETURN_STACK() {
	static PrimitiveForthWordFunction word(&F_TO_RETURN_STACK,
		"PrimitiveForthWords::TO_RETURN_STACK", ">r");
	return word;
}

static void F_FROM_RETURN_STACK(ForthThread& thread) {
	thread.pushDataStack(thread.fromReturnStack().cell);
}
ForthWord& PrimitiveForthWords::FROM_RETURN_STACK() {
	static PrimitiveForthWordFunction word(&F_FROM_RETURN_STACK,
		"PrimitiveForthWords::FROM_RETURN_STACK", "r>");
	return word;
}

static void F_AT_RETURN_STACK(ForthThread &thread) {
	thread.pushDataStack(thread.topOfReturnStack().cell);
}
ForthWord& PrimitiveForthWords::AT_RETURN_STACK() {
	static PrimitiveForthWordFunction word(&F_AT_RETURN_STACK,
		"PrimitiveForthWords::AT_RETURN_STACK", "r@");
	return word;
}

static void F_CHAR_SIZE(ForthThread& thread) {
	thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::CHAR_TYPE));
}
ForthWord& PrimitiveForthWords::CHAR_SIZE() {
	static PrimitiveForthWordFunction word(
		&F_CHAR_SIZE, "PrimitiveForthWords::CHAR_SIZE", "CHAR_SIZE");
	return word;
}

static void F_INT_SIZE(ForthThread& thread) {
	thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::INT_TYPE));
}
ForthWord& PrimitiveForthWords::INT_SIZE() {
	static PrimitiveForthWordFunction word(&F_INT_SIZE, "PrimitiveForthWords::INT_SIZE", "INT_SIZE");
	return word;
}

static void F_PTR_SIZE(ForthThread& thread) {
	thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::PTR_TYPE));
}
ForthWord& PrimitiveForthWords::PTR_SIZE() {
	static PrimitiveForthWordFunction word(&F_PTR_SIZE, "PrimitiveForthWords::PTR_SIZE", "PTR_SIZE");
	return word;
}

static void F_WORD_SIZE(ForthThread& thread) {
	thread.pushDataStack((ForthCell::INT_TYPE)sizeof(ForthCell::word));
}
ForthWord& PrimitiveForthWords::WORD_SIZE() {
	static PrimitiveForthWordFunction word(&F_WORD_SIZE, "PrimitiveForthWords::WORD_SIZE", "WORD_SIZE");
	return word;
}

static void F_ALLOC(ForthThread& thread) {
	ForthCell::INT_TYPE size = thread.popDataStack().integer;
	thread.pushDataStack((ForthCell::PTR_TYPE)new char[size]);
}
ForthWord& PrimitiveForthWords::ALLOC() {
	static PrimitiveForthWordFunction word(&F_ALLOC, "PrimitiveForthWords::ALLOC", "allocMem");
	return word;
}

static void F_FREE(ForthThread& thread) {
	ForthCell::PTR_TYPE ptr = thread.popDataStack().pointer;
	delete[] static_cast<char*>(ptr);
}
ForthWord& PrimitiveForthWords::FREE() {
	static PrimitiveForthWordFunction word(&F_FREE, "PrimitiveForthWords::FREE", "freeMem");
	return word;
}

thread_local ForthCell PrimitiveForthWords::registers[THREAD_STORAGE_SIZE];
static void F_REGISTERS(ForthThread& thread) {
	thread.pushDataStack(static_cast<ForthCell::PTR_TYPE>(PrimitiveForthWords::registers));
}
ForthWord& PrimitiveForthWords::REGISTER() {
	static PrimitiveForthWordFunction word(&F_REGISTERS, "PrimitiveForthWords::REGISTERS", "registers");
	return word;
}

// addr - char
static void F_CHAR_AT(ForthThread& thread) {
	ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
	thread.pushDataStack(*ptr);
}
ForthWord& PrimitiveForthWords::CHAR_AT() {
	static PrimitiveForthWordFunction word(&F_CHAR_AT, "PrimitiveForthWords::CHAR_AT", "c@");
	return word;
}

// char addr --
static void F_CHAR_PUT(ForthThread& thread) {
	ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
	(*ptr) = static_cast<char>(thread.popDataStack().integer);
}
ForthWord& PrimitiveForthWords::CHAR_PUT() {
	static PrimitiveForthWordFunction word(&F_CHAR_PUT, "PrimitiveForthWords::CHAR_PUT", "c!");
	return word;
}

// ndx addr -- addr
static void F_CHAR_INDEX(ForthThread& thread) {
	ForthCell::CHAR_TYPE* ptr = static_cast<ForthCell::CHAR_TYPE*>(thread.popDataStack().pointer);
	ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
	thread.pushDataStack(&ptr[ndx]);
}
ForthWord& PrimitiveForthWords::CHAR_INDEX() {
	static PrimitiveForthWordFunction word(&F_CHAR_INDEX, "PrimitiveForthWords::CHAR_INDEX", "c[]");
	return word;
}

// addr - INT
static void F_INT_AT(ForthThread& thread) {
	ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
	thread.pushDataStack(*ptr);
}
ForthWord& PrimitiveForthWords::INT_AT() {
	static PrimitiveForthWordFunction word(&F_INT_AT, "PrimitiveForthWords::INT_AT", "@");
	return word;
}

// INT addr --
static void F_INT_PUT(ForthThread& thread) {
	ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
	(*ptr) = thread.popDataStack().integer;
}
ForthWord& PrimitiveForthWords::INT_PUT() {
	static PrimitiveForthWordFunction word(&F_INT_PUT, "PrimitiveForthWords::INT_PUT", "!");
	return word;
}

// ndx addr -- addr
static void F_INT_INDEX(ForthThread& thread) {
	ForthCell::INT_TYPE* ptr = static_cast<ForthCell::INT_TYPE*>(thread.popDataStack().pointer);
	ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
	thread.pushDataStack(&ptr[ndx]);
}
ForthWord& PrimitiveForthWords::INT_INDEX() {
	static PrimitiveForthWordFunction word(&F_INT_INDEX,
		"PrimitiveForthWords::INT_INDEX", "[]");
	return word;
}

// addr - CELL
static void F_CELL_AT(ForthThread& thread) {
	ForthCell::WORD_TYPE* ptr = static_cast<ForthCell::WORD_TYPE*>(thread.popDataStack().pointer);
	thread.pushDataStack(*ptr);
}
ForthWord& PrimitiveForthWords::CELL_AT() {
	static PrimitiveForthWordFunction word(&F_CELL_AT,
		"PrimitiveForthWords::CELL_AT", "w@");
	return word;
}

// CELL addr --
static void F_CELL_PUT(ForthThread& thread) {
	ForthCell::WORD_TYPE* ptr = static_cast<ForthCell::WORD_TYPE*>(thread.popDataStack().pointer);
	(*ptr) = thread.popDataStack().word;
}
ForthWord& PrimitiveForthWords::CELL_PUT() {
	static PrimitiveForthWordFunction word(&F_CELL_PUT,
		"PrimitiveForthWords::CELL_PUT", "w!");
	return word;
}

// ndx addr -- addr
static void F_CELL_INDEX(ForthThread& thread) {
	ForthCell::WORD_TYPE* ptr = static_cast<ForthCell::WORD_TYPE*>(thread.popDataStack().pointer);
	ForthCell::INT_TYPE ndx = thread.popDataStack().integer;
	thread.pushDataStack(&ptr[ndx]);
}
ForthWord& PrimitiveForthWords::CELL_INDEX() {
	static PrimitiveForthWordFunction word(&F_CELL_INDEX,
		"PrimitiveForthWords::CELL_INDEX", "w[]");
	return word;
}

static void F_SWAP(ForthThread& thread) {
	ForthCell v1 = thread.popDataStack();
	ForthCell v2 = thread.popDataStack();
	thread.pushDataStack(v1);
	thread.pushDataStack(v2);
}
ForthWord& PrimitiveForthWords::SWAP() {
	static PrimitiveForthWordFunction word(&F_SWAP,
		"PrimitiveForthWords::SWAP", "swap");
	return word;
}

// ( a0 .. an n -- a0 .. an a0 )
static void F_PICK(ForthThread& thread) {
	thread.pushDataStack(thread[thread.popDataStack().integer]);
}
ForthWord& PrimitiveForthWords::PICK() {
	static PrimitiveForthWordFunction word(&F_PICK,
		"PrimitiveForthWords::PICK", "pick");
	return word;
}

// ( a0 .. an n -- a0 .. an a0 )
static void F_OVER(ForthThread& thread) {
	thread.pushDataStack(thread[1]);
}
ForthWord& PrimitiveForthWords::OVER() {
	static PrimitiveForthWordFunction::Function f = [](ForthThread& thread) -> void {
		thread.pushDataStack(thread[1]);
	};
	static PrimitiveForthWordFunction word(f, "PrimitiveForthWords::OVER", "over");
	return word;
}

// ( a0 .. an n -- a1 .. an a0 )
static void F_ROLL(ForthThread& thread) {
	thread.rollDataStack(thread.popDataStack().integer);
}
ForthWord& PrimitiveForthWords::ROLL() {
	static PrimitiveForthWordFunction word(&F_ROLL, "PrimitiveForthWords::ROLL", "roll");
	return word;
}

static void F_DROP(ForthThread& thread) {
	thread.popDataStack();
}
ForthWord& PrimitiveForthWords::DROP() {
	static PrimitiveForthWordFunction word(&F_DROP,
		"PrimitiveForthWords::DROP", "drop");
	return word;
}

static void F_DUP(ForthThread& thread) {
	thread.pushDataStack(thread[0]);
}
ForthWord& PrimitiveForthWords::DUP() {
	static PrimitiveForthWordFunction word(&F_DUP,
		"PrimitiveForthWords::DUP", "dup");
	return word;
}

static void F_ADD(ForthThread& thread) {
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	thread.pushDataStack(x + y);
}
ForthWord& PrimitiveForthWords::ADD() {
	static PrimitiveForthWordFunction word(&F_ADD,
		"PrimitiveForthWords::ADD", "+");
	return word;
}

// a b -- (a - b)
static void F_SUBTRACT(ForthThread& thread) {
	// note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
	// of expression operands is undefined.
	ForthCell::INT_TYPE subtrahend = thread.popDataStack().integer;
	ForthCell::INT_TYPE value = thread.popDataStack().integer;
	thread.pushDataStack(value - subtrahend);
}
ForthWord& PrimitiveForthWords::SUBTRACT() {
	static PrimitiveForthWordFunction word(&F_SUBTRACT,
		"PrimitiveForthWords::SUBTRACT", "-");
	return word;
}

static void F_MULTIPLY(ForthThread& thread) {
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	thread.pushDataStack(x * y);
}
ForthWord& PrimitiveForthWords::MULTIPLY() {
	static PrimitiveForthWordFunction word(&F_MULTIPLY,
		"PrimitiveForthWords::MULTIPLY", "*");
	return word;
}

// x y -- (x / y)
static void F_DIVIDE(ForthThread& thread) {
	// note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
	// of expression operands is undefined.
	ForthCell::INT_TYPE divisor = thread.popDataStack().integer;
	ForthCell::INT_TYPE dividend = thread.popDataStack().integer;
	thread.pushDataStack(dividend / divisor);
}
ForthWord& PrimitiveForthWords::DIVIDE() {
	static PrimitiveForthWordFunction word(&F_DIVIDE,
		"PrimitiveForthWords::DIVIDE", "/");
	return word;
}

// x y -- (x % y)
static void F_MOD(ForthThread& thread) {
	// note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
	// of expression operands is undefined.
	ForthCell::INT_TYPE modulus = thread.popDataStack().integer;
	ForthCell::INT_TYPE value = thread.popDataStack().integer;

	thread.pushDataStack(value % modulus);
}
ForthWord& PrimitiveForthWords::MOD() {
	static PrimitiveForthWordFunction word(&F_MOD, "PrimitiveForthWords::MOD", "%");
	return word;
}

// x y -- (x < y)
static void F_LESS_THAN(ForthThread& thread) {
	// note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
	// of expression operands is undefined.
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	thread.pushDataStack(x < y);
}
ForthWord& PrimitiveForthWords::LESS_THAN() {
	static PrimitiveForthWordFunction word(&F_LESS_THAN,
		"PrimitiveForthWords::LESS_THAN", "<");
	return word;
}

// x y -- (x > y)
static void F_GREATER_THAN(ForthThread& thread) {
	// note, this isn't done in a single statement because C++ DOES NOT guarantee order of evaluation
	// of expression operands is undefined.
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	thread.pushDataStack(x > y);
}
ForthWord& PrimitiveForthWords::GREATER_THAN() {
	static PrimitiveForthWordFunction word(&F_GREATER_THAN,
		"PrimitiveForthWords::GREATER_THAN", ">");
	return word;
}

// x y -- (x == y)
static void F_EQUAL(ForthThread& thread) {
	ForthCell::INT_TYPE y = thread.popDataStack().integer;
	ForthCell::INT_TYPE x = thread.popDataStack().integer;
	thread.pushDataStack(x == y);
}
ForthWord& PrimitiveForthWords::EQUAL() {
	static PrimitiveForthWordFunction word(&F_EQUAL, "PrimitiveForthWords::EQUAL", "=");
	return word;
}

// x y -- (x && y)
static void F_CONDITIONAL_AND(ForthThread& thread) {
	bool b1 = static_cast<bool>(thread.popDataStack().integer);
	bool b2 = static_cast<bool>(thread.popDataStack().integer);
	thread.pushDataStack(b1 && b2);
}
ForthWord& PrimitiveForthWords::CONDITIONAL_AND() {
	static PrimitiveForthWordFunction word(
		&F_CONDITIONAL_AND, "PrimitiveForthWords::AND", "&&");
	return word;
}

// x y -- (x && y)
static void F_CONDITIONAL_OR(ForthThread& thread) {
	bool b1 = static_cast<bool>(thread.popDataStack().integer);
	bool b2 = static_cast<bool>(thread.popDataStack().integer);
	thread.pushDataStack(b1 && b2);
}
ForthWord& PrimitiveForthWords::CONDITIONAL_OR() {
	static PrimitiveForthWordFunction word(
		&F_CONDITIONAL_OR, "PrimitiveForthWords::OR", "||");
	return word;
}

// x -- !x)
static void F_CONDITIONAL_NOT(ForthThread& thread) {
	thread.pushDataStack(!static_cast<bool>(thread.popDataStack().integer));
}
ForthWord& PrimitiveForthWords::CONDITIONAL_NOT() {
	static PrimitiveForthWordFunction word(
		&F_CONDITIONAL_NOT, "PrimitiveForthWords::NOT", "not");
	return word;
}

static void F_ACCEPT_INPUT(ForthThread& thread) {
	ForthCell::INT_TYPE size = thread.popDataStack().integer;
	ForthCell::PTR_TYPE ptr = thread.popDataStack().pointer;
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(NativeOSFunctions::accept(static_cast<char*>(ptr), size)));
}
ForthWord& PrimitiveForthWords::ACCEPT_INPUT() {
	static PrimitiveForthWordFunction word(&F_ACCEPT_INPUT,
		"PrimitiveForthWords::ACCEPT_INPUT", "acceptInput");
	return word;
}

static void F_PEEK_NEXT_INPUT_CHAR(ForthThread& thread) {
	thread.pushDataStack(NativeOSFunctions::peekNextChar());
}
ForthWord& PrimitiveForthWords::PEEK_NEXT_INPUT_CHAR() {
	static PrimitiveForthWordFunction word(&F_PEEK_NEXT_INPUT_CHAR,
		"PrimitiveForthWords::PEEK_NEXT_INPUT_CHAR", "peekInput");
	return word;
}

static void F_GET_NEXT_INPUT_CHAR(ForthThread& thread) {
	thread.pushDataStack(NativeOSFunctions::nextChar());
}
ForthWord& PrimitiveForthWords::GET_NEXT_INPUT_CHAR() {
	static PrimitiveForthWordFunction word(&F_GET_NEXT_INPUT_CHAR,
		"PrimitiveForthWords::GET_NEXT_INPUT_CHAR", "getInput");
	return word;
}

static void F_FLUSH_INPUT(ForthThread& thread) {
	NativeOSFunctions::flushInput();
}
ForthWord& PrimitiveForthWords::FLUSH_INPUT() {
	static PrimitiveForthWordFunction word(&F_FLUSH_INPUT,
		"PrimitiveForthWords::FLUSH_INPUT", "flushInput");
	return word;
}

static void F_PRINT_CHAR(ForthThread& thread) {
	NativeOSFunctions::printChar(static_cast<char>(thread.popDataStack().integer));
}
ForthWord& PrimitiveForthWords::PRINT_CHAR() {
	static PrimitiveForthWordFunction word(&F_PRINT_CHAR,
		"PrimitiveForthWords::PRINT_CHAR", "printChar");
	return word;
}

static void F_FALSE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(false));
}
ForthWord& PrimitiveForthWords::FALSE() {
	static PrimitiveForthWordFunction word(&F_FALSE, "PrimitiveForthWords::FALSE", "false");
	return word;
}

static void F_TRUE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(true));
}
ForthWord& PrimitiveForthWords::TRUE() {
	static PrimitiveForthWordFunction word(&F_TRUE, "PrimitiveForthWords::TRUE", "true");
	return word;
}

static void F_ZERO(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(0));
}
ForthWord& PrimitiveForthWords::ZERO() {
	static PrimitiveForthWordFunction word(&F_ZERO, "PrimitiveForthWords::ZERO", "0");
	return word;
}

static void F_ONE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(1));
}
ForthWord& PrimitiveForthWords::ONE() {
	static PrimitiveForthWordFunction word(&F_ONE, "PrimitiveForthWords::ONE", "1");
	return word;
}

static void F_NEGATIVE_ONE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(-1));
}
ForthWord& PrimitiveForthWords::NEGATIVE_ONE() {
	static PrimitiveForthWordFunction word(
		&F_NEGATIVE_ONE, "PrimitiveForthWords::NEGATIVE_ONE", "-1");
	return word;
}

static void F_ADD_ONE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(1 + thread.popDataStack().integer));
}
ForthWord& PrimitiveForthWords::ADD_ONE() {
	static PrimitiveForthWordFunction word(&F_ADD_ONE, "PrimitiveForthWords::ADD_ONE", "+=1");
	return word;
}

static void F_SUBTRACT_ONE(ForthThread &thread) {
	thread.pushDataStack(static_cast<ForthCell::INT_TYPE>(thread.popDataStack().integer - 1));
}
ForthWord& PrimitiveForthWords::SUBTRACT_ONE() {
	static PrimitiveForthWordFunction word(
		&F_SUBTRACT_ONE, "PrimitiveForthWords::SUBTRACT_ONE", "-=1");
	return word;
}

static void F_TRACE(ForthThread &thread) {
	thread.enableTrace(thread.popDataStack().integer);
}
ForthWord& PrimitiveForthWords::TRACE() {
	static PrimitiveForthWordFunction word(&F_TRACE, "PrimitiveForthWords::TRACE", "trace");
	return word;
}

