//
// Created by Dad on 9/19/19.
//

#include "BootstrapInterpTest.h"
#include "words/bootstrap/BootstrapInterp.h"
#include "runtime/ForthThread.h"

#define ENDLESS

void BootstrapInterpTest::test() {
	CompositeForthWord *interp = BootstrapInterp::getInstance();
	ForthThread disassemble1(BootstrapInterp::getInstance());
	std::string da1 = interp->disassemble(disassemble1);
    ForthThread disassemble2(BootstrapInterp::getInstance());
    std::vector<std::string> dump;
    interp->disassemble(disassemble2, dump);

#ifdef ENDLESS
    ForthThread thread(BootstrapInterp::getInstance());
	thread.join();
#else
	for (int i = 0; i < interp->size()*2; i++) {
		thread.execute();
	}
#endif
}