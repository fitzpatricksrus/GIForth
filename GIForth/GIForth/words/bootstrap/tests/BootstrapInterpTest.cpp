//
// Created by Dad on 9/19/19.
//

#include <iostream>
#include "BootstrapInterpTest.h"
#include "words/bootstrap/BootstrapInterp.h"
#include "runtime/ForthThread.h"

#define ENDLESS

void BootstrapInterpTest::test() {
	CompositeForthWord *interp = BootstrapInterp::getInstance();
	for (std::string s : interp->getDisassembly()) {
		std::cout << s << std::endl;
	}

	ForthThread thread(interp);
	thread.enableTrace(true);
#ifdef ENDLESS
	thread.join();
#else
	for (int i = 0; i < interp->size()*2; i++) {
		thread.execute();
	}
#endif
}