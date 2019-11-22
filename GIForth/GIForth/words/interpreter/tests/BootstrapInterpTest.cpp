//
// Created by Dad on 9/19/19.
//

#include "BootstrapInterpTest.h"
#include "words/interpreter/BootstrapInterp.h"
#include "runtime/ForthThread.h"

#define ENDLESS

void BootstrapInterpTest::test() {
	CompositeForthWord *interp = BootstrapInterp::getInstance();

	ForthThread thread;
	thread.enableTrace(true);
#ifdef ENDLESS
	thread.join(*interp);
#else
	for (int i = 0; i < interp->size()*2; i++) {
		thread.execute();
	}
#endif
}