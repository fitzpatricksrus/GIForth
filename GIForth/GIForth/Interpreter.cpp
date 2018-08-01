//
//  Interpreter.cpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include "Interpreter.hpp"
#include "ForthInstruction.hpp"

Interpreter::Interpreter(ForthArchitecture& architecture)
: arch(architecture)
{
}

void Interpreter::interpret() {
	while (arch.returnStackDepth() != 0) {
		int ins = arch.getNextInstruction();
		switch (ins) {
		case P_CHAR_SIZE:
			arch.pushDataStack(sizeof(char));
			break;
		case P_CELL_SIZE:
			arch.pushDataStack(sizeof(int));
			break;
		case P_CHAR_AT:	// location -- value
			arch.pushDataStack(arch.getByte(arch.popDataStack()));
			break;
		case P_CHAR_PUT: { // value location --
			int location = arch.popDataStack();
			arch.setByte(location, arch.popDataStack());
			} break;
		case P_CHAR_INDEX:	// addr index -- addr
			arch.pushDataStack(arch.popDataStack() + arch.popDataStack());
			break;
		case P_CELL_AT:
			arch.pushDataStack(arch.getWord(arch.popDataStack()));
			break;
		case P_CELL_PUT: { // value location --
			int location = arch.popDataStack();
			arch.setWord(location, arch.popDataStack());
			} break;
		case P_CELL_INDEX:	{ // addr index -- addr
			int ndx = arch.popDataStack();
			arch.pushDataStack(arch.popDataStack() + ndx * sizeof(int));
			} break;
		case P_TO_RETURN_STACK:
		case P_FROM_RETURN_STACK:
		
		case P_PICK:	// ( a0 .. an n -- a0 .. an a0 )
		case P_ROLL:	// ( a0 .. an n -- a1 .. an a0 )
		case P_DROP:
		
		case P_ADD:
		case P_SUBTRACT:
		case P_MULTIPLY:
		case P_DIVIDE:
		case P_MOD:
		
		case P_LESS_THAN:
		case P_GREATER_THAN:
		case P_EQUAL:
		
		case P_AND:
		case P_OR:
		case P_NOT:
		case P_XOR:
		
		case P_JUMP:
		case P_JUMP_IF_FALSE:
		case P_PUSH_NEXT_CELL:
		default:
			break;
		}
	}
}
