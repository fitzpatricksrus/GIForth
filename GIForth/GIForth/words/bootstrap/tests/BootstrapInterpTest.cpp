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
/*	ForthThread disassemblyThread1(interp);
	while (!disassemblyThread1.currentWordComplete()) {
	    ForthCell cell = disassemblyThread1.getNextCell();
	    std::cout << cell.word->getDisassembly(disassemblyThread1) << std::endl;
	    disassemblyThread1.offsetIndex(cell.word->getDisassemblyParamCount());
	}
*/
    ForthThread thread(interp);
	CompositeForthWord::enableTrace(true);
#ifdef ENDLESS
	thread.join();
#else
	for (int i = 0; i < interp->size()*2; i++) {
		thread.execute();
	}
#endif
}