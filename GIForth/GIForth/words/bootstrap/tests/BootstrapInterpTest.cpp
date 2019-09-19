//
// Created by Dad on 9/19/19.
//

#include "BootstrapInterpTest.h"
#include "words/bootstrap/BootstrapInterp.h"
#include "runtime/ForthThread.h"

#define ENDLESS

void BootstrapInterpTest::test() {
	CompositeForthWord *interp = BootstrapInterp::getInstance();
	ForthThread thread(BootstrapInterp::getInstance());
#ifdef ENDLESS
	thread.join();
#else
	for (int i = 0; i < interp->size()*2; i++) {
		thread.execute();
	}
#endif
}