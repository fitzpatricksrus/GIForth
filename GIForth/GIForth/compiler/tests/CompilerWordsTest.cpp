//
// Created by Dad on 10/24/19.
//

#include <runtime/CompositeForthWord.h>
#include <words/bootstrap/CompositeForthWordBuilder.h>
#include <compiler/CompilerWords.h>
#include <words/PrimitiveForthWords.h>
#include <runtime/ForthThread.h>
#include <utils/testing/TestRunner.h>
#include "CompilerWordsTest.h"
#include "utils/testing/catch.hpp"

#define __SHORT_FILE__ ({constexpr cstr sf__ {past_last_slash(__FILE__)}; sf__;})

TEST_CASE( "__FILE__::VARIABLE_IMPL", "[CompilerWordTest]" ) {
	CompositeForthWord variableWord(CompositeForthWordBuilder("CompilerWordTest::VARIABLE_IMPL.variable")
			                                .compileCell(&CompilerWords::VARIABLE_IMPL)
			                                .compileCell(static_cast<ForthCell::INT_TYPE>(1234))
			                                .build());
	CompositeForthWord atWord(CompositeForthWordBuilder("CompilerWordTest::VARIABLE_IMPL.atWord")
			                          .compileCell(&variableWord)
			                          .compileCell(&PrimitiveForthWords::INT_AT)
			                          .build());
	CompositeForthWord putWord(CompositeForthWordBuilder("CompilerWordTest::VARIABLE_IMPL.putWord")
			                           .compileConstant(static_cast<ForthCell::INT_TYPE>(9876))
			                           .compileCell(&variableWord)
			                           .compileCell(&PrimitiveForthWords::INT_PUT)
			                           .compileCell(&variableWord)
			                           .compileCell(&PrimitiveForthWords::INT_AT)
			                           .build());
	
	TestRunner::enableTrace = true;
	ForthThread thread(TestRunner::runTestWord(&atWord));
	CHECK(thread.popDataStack().integer == 1234);
	
	ForthThread thread2 = TestRunner::runTestWord(&putWord);
	CHECK(thread2.popDataStack().integer == 9876);
}
