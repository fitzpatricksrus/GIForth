//
// Created by Dad on 9/28/19.
//

#include <iostream>
#include "utils/testing/TestRunner.h"
#include "runtime/ForthThread.h"
#include "words/bootstrap/CompositeForthWordBuilder.h"
#include "words/PrimitiveForthWords.h"
#include "words/CoreForthWords.h"
#include "CoreForthWordsTest.h"
#include "utils/testing/catch.hpp"

static int testParseDigitWith(char c) {
	CompositeForthWord word(CompositeForthWordBuilder("CoreForthWordsTest")
					.append(&PrimitiveForthWords::PUSH_NEXT_CELL)
					.append(static_cast<ForthCell::CHAR_TYPE>(c))
					.append(&CoreForthWords::PARSE_DIGIT)
					.build());
	ForthThread thread(TestRunner::runTestWord(&word));
	return thread.popDataStack().integer;
}
TEST_CASE( "words/tests/CoreForthWordsTest::testParseDigit", "[CoreForthWordsTest]" ) {
	CHECK(testParseDigitWith('0') == 0);
	CHECK(testParseDigitWith('9') == 9);
	CHECK(testParseDigitWith(static_cast<char>('0' - 1)) == -1);
	CHECK(testParseDigitWith(static_cast<char>('9' + 1)) == -1);
}

static int testParseNumberWith(const char* c) {
	CompositeForthWord word(CompositeForthWordBuilder("CoreForthWordsTest::testParseDigit")
			                        .append(&PrimitiveForthWords::PUSH_NEXT_CELL)
			                        .append(static_cast<ForthCell::PTR_TYPE>(const_cast<char*>(c)))
			                        .append(&CoreForthWords::PARSE_NUMBER)
			                        .build());
	ForthThread thread(TestRunner::runTestWord(&word));
	int isNumber = thread.popDataStack().integer;
	if (isNumber == 0) {
		return -1;
	} else {
		return thread.popDataStack().integer;
	}
}
TEST_CASE( "words/tests/CoreForthWordsTest::testParseNumber", "[CoreForthWordsTest]" ) {
	CHECK(testParseNumberWith("1234") == 1234);
	CHECK(testParseNumberWith("1") == 1);
	CHECK(testParseNumberWith("999") == 999);
	CHECK(testParseNumberWith("0") == 0);
	CHECK(testParseNumberWith("123j3847") == -1);
	CHECK(testParseNumberWith("j1233847") == -1);
	CHECK(testParseNumberWith("1233847j") == -1);
}
