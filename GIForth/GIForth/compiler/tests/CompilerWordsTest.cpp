//
// Created by Dad on 10/24/19.
//

#include <runtime/CompositeForthWord.h>
#include "CompilerWordsTest.h"
#include "utils/testing/catch.hpp"

#define __SHORT_FILE__ ({constexpr cstr sf__ {past_last_slash(__FILE__)}; sf__;})

TEST_CASE( "__FILE__", "[CompositeWordTest]" ) {
	CompositeForthWord innerWord(CompositeForthWordBuilder("CoreForthWordsTest::innerWord")
			                             .compileCell(&PrimitiveForthWords::ADD_ONE)
			                             .build());
	CompositeForthWord outerWord(CompositeForthWordBuilder("CoreForthWordsTest::testParseDigit")
			                             .compileConstant(10)
			                             .compileCell(&innerWord)
			                             .compileCell(&PrimitiveForthWords::ADD_ONE)
			                             .build());
	ForthThread thread(TestRunner::runTestWord(&outerWord));
	REQUIRE(thread.getDataStackSize() == 1);
	CHECK(thread.popDataStack().integer == 12);
	CHECK(thread.getDataStackSize() == 0);
}
