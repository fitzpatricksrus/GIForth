//
// Created by Dad on 12/5/19.
//

#include "OuterInterpTest.h"

#include "words/interpreter/OuterInterp.h"
#include "runtime/ForthThread.h"

void OuterInterpTest::test() {
	CompositeForthWord *interp = OuterInterp::getInstance();

	ForthThread thread;
//	thread.enableTrace(true);
	thread.join(*interp);
}