//
// Created by stuff on 11/21/2019.
//

#include <runtime/ForthThread.h>
#include <runtime/PrimitiveForthWords.h>
#include <runtime/utils/CompositeForthWordBuilder.h>
#include "utils/testing/catch.hpp"

TEST_CASE("runtime/tests/PrimitiveForthWords::NOP", "[RuntimeTests]") {
	ForthThread thread;
	PrimitiveForthWords::NOP.execute(thread);
	REQUIRE(thread.getDataStackSize() == 0);
}

TEST_CASE("runtime/tests/PrimitiveForthWords::JUMP", "[RuntimeTests]") {
	CompositeForthWord word(
		CompositeForthWordBuilder("PrimitiveForthWordsTest::JUMP")
			.compileCell(&PrimitiveForthWords::JUMP)
			.compileCell(static_cast<ForthCell::INT_TYPE>(4))
			.compileCell(&PrimitiveForthWords::PUSH_NEXT_CELL)
			.compileCell(static_cast<ForthCell::INT_TYPE >(99))
			.build()
	);
	ForthThread thread;
	REQUIRE(thread.getDataStackSize() == 0);
	REQUIRE(thread.getIndex() == 0);
	// we don't use thread.join here because we don't want to run more than
	// one instruction or we'll jump off the end of the world
	thread.join(word);
	REQUIRE(thread.getDataStackSize() == 0);
}

TEST_CASE("words/PrimitiveForthWords::JUMP_IF_FALSE", "[PrimitiveForthWords]") {
	CompositeForthWord word(
		CompositeForthWordBuilder("PrimitiveForthWordsTest::JUMP_IF_FALSE")
			.compileCell(static_cast<ForthCell::INT_TYPE>(32))
			.compileCell(static_cast<ForthCell::INT_TYPE>(42))
			.build()
	);
	ForthThread thread;
	thread.pushFrame(&word);
	REQUIRE(thread.getDataStackSize() == 0);
	REQUIRE(thread.getIndex() == 0);
	thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(true));
	PrimitiveForthWords::JUMP_IF_FALSE.execute(thread);
	REQUIRE(thread.getDataStackSize() == 0);
	REQUIRE(thread.getIndex() == 1);
	thread.pushDataStack(static_cast<ForthCell::BOOL_TYPE>(false));
	PrimitiveForthWords::JUMP_IF_FALSE.execute(thread);
	REQUIRE(thread.getDataStackSize() == 0);
	REQUIRE(thread.getIndex() == 42);
}

TEST_CASE("words/PrimitiveForthWords::EXECUTE", "[PrimitiveForthWords]") {
	CompositeForthWord innerWord(
		CompositeForthWordBuilder("PrimitiveForthWordsTest::EXECUTE.innerWord")
			.compileCell(&PrimitiveForthWords::ADD_ONE)
			.build()
	);
	CompositeForthWord word(
		CompositeForthWordBuilder("PrimitiveForthWordsTest::EXECUTE.outerWord")
			.compileConstant(static_cast<ForthCell::INT_TYPE >(98))
			.compileConstant(&PrimitiveForthWords::ADD_ONE)
			.compileCell(&PrimitiveForthWords::EXECUTE)
			.compileConstant(&innerWord)
			.compileCell(&PrimitiveForthWords::EXECUTE)
			.build()
	);
	ForthThread thread;
	REQUIRE(thread.getDataStackSize() == 0);
	REQUIRE(thread.getIndex() == 0);
	thread.join(word);
	REQUIRE(thread.getDataStackSize() == 1);
	REQUIRE(thread.popDataStack().integer == 100);
}
