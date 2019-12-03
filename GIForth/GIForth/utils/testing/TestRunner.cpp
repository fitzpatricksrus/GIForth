//
// Created by stuff on 9/29/2019.
//

#include "runtime/ForthThread.h"
#include "TestRunner.h"

//
// Created by stuff on 9/29/2019.
//

#define CATCH_CONFIG_RUNNER
#include "utils/testing/catch.hpp"
#include "runtime/CompositeForthWord.h"

bool TestRunner::traceEnabled = false;

int TestRunner::run( int argc, const char* argv[] ) {
    // global setup...

    int result = Catch::Session().run( argc, argv );

    // global clean-up...

    return result;
}

ForthThread TestRunner::runTestWord(CompositeForthWord* word) {
	ForthThread thread;
	bool s = thread.isTraceEnabled();
	thread.enableTrace(traceEnabled);
	thread.join(*word);
	thread.enableTrace(s);
	return thread;
}

TestRunner::Tracer::Tracer(bool e)
{
	ForthThread* currentThread = ForthThread::getCurrentThread();
	if (currentThread) {
		save = currentThread->isTraceEnabled();
		currentThread->enableTrace(e);
	} else {
		save = traceEnabled;
		traceEnabled = e;
	}
}

TestRunner::Tracer::~Tracer() {
	ForthThread* currentThread = ForthThread::getCurrentThread();
	if (currentThread) {
		currentThread->enableTrace(save);
	} else {
		traceEnabled = save;
	}
}
