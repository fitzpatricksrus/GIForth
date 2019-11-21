//
// Created by Dad on 9/17/19.
//

#include "CompositeForthWordTest.h"

#include <string>
#include <runtime/CompositeForthWord.h>
#include <runtime/ForthThread.h>
#include <utils/CompositeForthWordBuilder.h>
#include <words/PrimitiveForthWords.h>
#include <utils/testing/TestRunner.h>
#include "utils/testing/catch.hpp"

TEST_CASE("runtime/tests/CompositeWordTest", "[RuntimeTests]") {
	CompositeForthWord innerWord(CompositeForthWordBuilder("CoreForthWordsTest::CompositeWordTest::innerWord")
										 .compileCell(&PrimitiveForthWords::ADD_ONE)
										 .compileCell(&PrimitiveForthWords::ADD_ONE)
			                        .build());
	CompositeForthWord outerWord(CompositeForthWordBuilder("CoreForthWordsTest::CompositeWordTest::outerWord")
			                             .compileConstant(10)
			                             .compileCell(&innerWord)
			                             .compileCell(&PrimitiveForthWords::ADD_ONE)
			                        .build());
	{
		TestRunner::Tracer t;
		ForthThread thread(TestRunner::runTestWord(&outerWord));
		REQUIRE(thread.getDataStackSize() == 1);
		CHECK(thread.popDataStack().integer == 13);
		CHECK(thread.getDataStackSize() == 0);
	}
}
