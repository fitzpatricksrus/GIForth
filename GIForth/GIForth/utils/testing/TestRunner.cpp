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

int TestRunner::run( int argc, const char* argv[] ) {
    // global setup...

    int result = Catch::Session().run( argc, argv );

    // global clean-up...

    return result;
}

bool TestRunner::enableTrace = false;

ForthThread TestRunner::runTestWord(CompositeForthWord* word) {
	ForthThread thread;
	thread.enableTrace(TestRunner::enableTrace);
	thread.join(*word);
	return thread;
}