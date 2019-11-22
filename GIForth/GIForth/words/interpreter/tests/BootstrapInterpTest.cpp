//
// Created by Dad on 9/19/19.
//

#include "BootstrapInterpTest.h"
#include "words/interpreter/BootstrapInterp.h"
#include "runtime/ForthThread.h"

void BootstrapInterpTest::test() {
	CompositeForthWord *interp = BootstrapInterp::getInstance();

	ForthThread thread;
	thread.join(*interp);
}