/*
// http://wiki.laptop.org/go/Forth_stack_operators

enum ForthInstruction {
    P_NOP,

	P_CHAR_SIZE,
	P_CELL_SIZE,
	
	P_CHAR_AT,			// addr - char
	P_CHAR_PUT,			// char addr --
	P_CHAR_INDEX,		// ndx addr -- addr
	P_CELL_AT,			// addr -- cell
	P_CELL_PUT,			// value addr --
	P_CELL_INDEX,		// ndx addr -- addr

	P_ALLOCATE,			// size -- addr
	P_FREE,				// addr --
	
	P_TO_RETURN_STACK,
	P_FROM_RETURN_STACK,
	
	P_PICK,	// ( a0 .. an n -- a0 .. an a0 )
	P_ROLL,	// ( a0 .. an n -- a1 .. an a0 )
	P_DROP,
	
	P_ADD,
	P_SUBTRACT,
	P_MULTIPLY,
	P_DIVIDE,
	P_MOD,
	
	P_LESS_THAN,
	P_GREATER_THAN,
	P_EQUAL,
	
	P_CONDITIONAL_AND,
	P_CONDITIONAL_OR,
	P_CONDITIONAL_NOT,
	
	P_JUMP,
	P_JUMP_IF_FALSE,
	P_PUSH_NEXT_CELL,
	P_PUSH_NEXT_CELL_ADDRESS_AND_RETURN,
	P_RETURN,

	P_PEEK_NEXT_INPUT_CHAR,
	P_GET_NEXT_INPUT_CHAR,
	P_PRINT_CHAR,

	P_UNKNOWN
};
*/
