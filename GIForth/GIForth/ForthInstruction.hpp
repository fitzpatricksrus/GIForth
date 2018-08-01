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
	P_AT,
	P_PUT,
	
	P_TO_RETURN_STACK,
	P_FROM_RETURN_STACK,
	
	P_PICK,	// ( a0 .. an n -- a0 .. an a0 )
	P_ROLL,	// ( a0 .. an n -- a1 .. an a0 )
	P_DROP,
	
	P_JUMP,
	P_JUMP_IF_FALSE,
	
	
};

#endif /* ForthInstruction_hpp */
