#include <runtime/utils/CompositeForthWordBuilder.h>
#include <runtime/CompositeForthWordWords.h>
#include <runtime/PrimitiveForthWords.h>
#include "utils/testing/catch.hpp"
#include "runtime/ForthThread.h"
#include "utils/testing/TestRunner.h"

TEST_CASE("runtime/tests/CompilerWordTest", "[RuntimeTests]") {
	char compilingWordName[] = "RuntimeTests::CompilerWordTest::compilingWord";
	CompositeForthWord compilingWord(CompositeForthWordBuilder("RuntimeTests::CompilerWordTest")
										 .compileConstant(static_cast<ForthCell::PTR_TYPE>(&compilingWordName))
										 .compileCell(&CompositeForthWordWords::COMPILE_BEGIN)
										 .compileConstant(static_cast<ForthCell::PTR_TYPE>(&PrimitiveForthWords::ONE))
										 .compileCell(&CompositeForthWordWords::COMPILE_TOS)
										 .compileConstant(static_cast<ForthCell::PTR_TYPE>(&PrimitiveForthWords::ADD_ONE))
										 .compileCell(&CompositeForthWordWords::COMPILE_TOS)
										 .compileCell(&CompositeForthWordWords::COMPILE_END)
										 .compileCell(&PrimitiveForthWords::DUP)
										 .compileCell(&PrimitiveForthWords::EXECUTE)
										 .compileCell(&PrimitiveForthWords::SWAP)
										 .compileCell(&CompositeForthWordWords::FREE_WORD)
										 .build());

	ForthThread thread(TestRunner::runTestWord(&compilingWord));
	REQUIRE(thread.getDataStackSize() == 1);
	REQUIRE(thread.popDataStack().integer == 2);
}
