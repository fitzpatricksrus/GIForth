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
		case P_CHAR_INDEX:	// index addr -- addr
			arch.pushDataStack(arch.popDataStack() + arch.popDataStack());
			break;
		case P_CELL_AT:
			arch.pushDataStack(arch.getWord(arch.popDataStack()));
			break;
		case P_CELL_PUT: { // value location --
			int location = arch.popDataStack();
			arch.setWord(location, arch.popDataStack());
			} break;
		case P_CELL_INDEX: // index addr -- addr
			arch.pushDataStack(arch.popDataStack() + arch.popDataStack() * sizeof(int));
			break;
			
		case P_ALLOCATE:
			arch.pushDataStack(arch.allocateMemory(arch.popDataStack()));
			break;
		case P_FREE:
			arch.freeMemory(arch.popDataStack());
			break;

		case P_TO_RETURN_STACK:
			arch.toReturnStack(arch.popDataStack());
			break;
		case P_FROM_RETURN_STACK:
			arch.pushDataStack(arch.fromReturnStack());
			break;
			
		case P_PICK:	// ( a0 .. an n -- a0 .. an a0 )
			arch.pushDataStack(arch.peekDataStack(arch.popDataStack()));
			break;
		case P_ROLL:	// ( a0 .. an n -- a1 .. an a0 )
			arch.rollDataStack(arch.popDataStack());
			break;
		case P_DROP:
			arch.popDataStack();
			break;
			
		case P_ADD:
			arch.pushDataStack(arch.popDataStack() + arch.popDataStack());
			break;
		case P_SUBTRACT: {	// x y -- x - y
			int x = arch.popDataStack();
			arch.pushDataStack(x - arch.popDataStack());
			} break;
		case P_MULTIPLY:
			arch.pushDataStack(arch.popDataStack() * arch.popDataStack());
			break;
		case P_DIVIDE: {	// x y -- x / y
			int x = arch.popDataStack();
			arch.pushDataStack(x / arch.popDataStack());
			} break;
		case P_MOD: {	// x y -- x % y
			int x = arch.popDataStack();
			arch.pushDataStack(x % arch.popDataStack());
			} break;
			
		case P_LESS_THAN:	// x y -- x < y
			arch.pushDataStack(arch.popDataStack() > arch.popDataStack());
			break;
		case P_GREATER_THAN:
			arch.pushDataStack(arch.popDataStack() < arch.popDataStack());
			break;
		case P_EQUAL:
			arch.pushDataStack(arch.popDataStack() != arch.popDataStack());
			break;
			
		case P_CONDITIONAL_AND:
			arch.pushDataStack(arch.popDataStack() && arch.popDataStack());
			break;
		case P_CONDITIONAL_OR:
			arch.pushDataStack(arch.popDataStack() || arch.popDataStack());
			break;
		case P_CONDITIONAL_NOT:
			arch.pushDataStack(!arch.popDataStack());
			break;
			
		case P_JUMP:
			arch.setIP(arch.getNextInstruction());
			break;
		case P_JUMP_IF_FALSE:
			if (arch.popDataStack()) {
				// just eat the next instruction
				arch.getNextInstruction();
			} else {
				arch.setIP(arch.getNextInstruction());
			}
			break;
		case P_PUSH_NEXT_CELL:
			arch.pushDataStack(arch.getNextInstruction());
			break;
		case P_PUSH_NEXT_CELL_ADDRESS_AND_RETURN:
			// used as the sole/last instruction of a word, push the addr of the next word
			// on the data stack and return
			arch.pushDataStack(arch.getIP());
			arch.setIP(arch.fromReturnStack());
			break;
		case P_RETURN:
			arch.setIP(arch.fromReturnStack());
			break;
		case P_UNKNOWN:
		default:
			// considered a composite word.
			arch.toReturnStack(arch.getIP());
			arch.setIP(ins);
			break;
		}
	}
}
