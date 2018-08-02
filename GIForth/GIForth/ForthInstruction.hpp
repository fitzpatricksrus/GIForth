//
//  ForthInstruction.hpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#ifndef ForthInstruction_hpp
#define ForthInstruction_hpp

// http://wiki.laptop.org/go/Forth_stack_operators

enum ForthInstruction {
	P_CHAR_SIZE,
	P_CELL_SIZE,
	
	P_CHAR_AT,
	P_CHAR_PUT,
	P_CHAR_INDEX,
	P_CELL_AT,
	P_CELL_PUT,
	P_CELL_INDEX,
	
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
	P_PUSH_NEXT_CELL_ADDRESS,
	P_RETURN,
	P_UNKNOWN
};

#endif /* ForthInstruction_hpp */
