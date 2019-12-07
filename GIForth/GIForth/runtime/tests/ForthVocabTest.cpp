#include <runtime/PrimitiveForthWords.h>
#include "utils/testing/catch.hpp"
#include "runtime/ForthVocab.h"

TEST_CASE("runtime/tests/ForthVocabTest", "[RuntimeTests]") {
	const char* nopChars = "NOP";
	std::string nopStr = nopChars;
	const char* trueChars = "true";
	std::string trueStr = trueChars;
	ForthVocab v1(nullptr);
	ForthVocab v2(&v1);

	v1.add(&PrimitiveForthWords::NOP);
	v2.add(&PrimitiveForthWords::TRUE);

	CHECK(v1.findWord(nopChars) == &PrimitiveForthWords::NOP);
	CHECK(v1.findWord(nopStr) == &PrimitiveForthWords::NOP);
	CHECK(v1.findWord(trueChars) == nullptr);
	CHECK(v1.findWord(trueStr) == nullptr);

	CHECK(v2.findWord(nopChars) == &PrimitiveForthWords::NOP);
	CHECK(v2.findWord(nopStr) == &PrimitiveForthWords::NOP);
	CHECK(v2.findWord(trueChars) == &PrimitiveForthWords::TRUE);
	CHECK(v2.findWord(trueStr) == &PrimitiveForthWords::TRUE);
}

