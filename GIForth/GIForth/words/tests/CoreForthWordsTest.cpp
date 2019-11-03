//
// Created by Dad on 9/28/19.
//

#include "utils/testing/TestRunner.h"
#include "runtime/ForthThread.h"
#include "words/bootstrap/CompositeForthWordBuilder.h"
#include "words/CoreForthWords.h"
#include "utils/testing/catch.hpp"
#include <cstring>

TEST_CASE( "words/tests/CoreForthWordsTest::testStrLen", "[CoreForthWordsTest]" ) {
	static char str[] = "Hello World";
	CompositeForthWord word(CompositeForthWordBuilder("CoreForthWordsTest::testStrLen")
                .compileConstant(static_cast<ForthCell::PTR_TYPE>(str))
                .compileCell(&CoreForthWords::STRLEN)
                .build());
	ForthThread thread(TestRunner::runTestWord(&word));
	CHECK(thread.getDataStackSize() == 1);
	CHECK(thread.popDataStack().integer == sizeof(str) - 1);
}

TEST_CASE( "words/tests/CoreForthWordsTest::testStrCpy", "[CoreForthWordsTest]" ) {
	static char str[] = "Hello World";
	char dest[sizeof(str)];
	CompositeForthWord word(CompositeForthWordBuilder("CoreForthWordsTest::testStrCpy")
                .compileConstant(static_cast<ForthCell::PTR_TYPE>(str))
                .compileConstant(static_cast<ForthCell::PTR_TYPE>(dest))
                .compileCell(&CoreForthWords::STRCPY)
                .build());
	ForthThread thread(TestRunner::runTestWord(&word));
	CHECK(thread.getDataStackSize() == 0);
	CHECK(strcmp(str, dest) == 0);
}

TEST_CASE( "words/tests/CoreForthWordsTest::testStrReverse", "[CoreForthWordsTest]" ) {
	static char str[] = "abc";
	CompositeForthWord word(CompositeForthWordBuilder("CoreForthWordsTest::testStrReverse")
                .compileConstant(static_cast<ForthCell::PTR_TYPE>(str))
                .compileCell(&CoreForthWords::STRREVERSE)
                .build());
	ForthThread thread(TestRunner::runTestWord(&word));
	CHECK(thread.getDataStackSize() == 0);
	CHECK(strcmp("cba", str) == 0);
}

static int testParseDigitWith(char c) {
	CompositeForthWord word(CompositeForthWordBuilder("CoreForthWordsTest::testParseDigitWith")
                .compileConstant(static_cast<ForthCell::CHAR_TYPE>(c))
                .compileCell(&CoreForthWords::PARSE_DIGIT)
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
	CompositeForthWord word(CompositeForthWordBuilder("CoreForthWordsTest::testParseNumber")
			                        .compileConstant(static_cast<ForthCell::PTR_TYPE>(const_cast<char*>(c)))
			                        .compileCell(&CoreForthWords::PARSE_NUMBER)
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

static std::string testNumbersToCharacters(int number) {
	char scratch[20] = "";
	CompositeForthWord word(CompositeForthWordBuilder("CoreForthWordsTest::testNumbersToCharacters")
									.compileConstant(static_cast<ForthCell::INT_TYPE >(number))
									.compileConstant(static_cast<ForthCell::PTR_TYPE>(scratch))
									.compileCell(&CoreForthWords::NUMBER_TO_CHARACERS)
									.build());
	ForthThread thread(TestRunner::runTestWord(&word));
	return std::string(scratch);
}
TEST_CASE("words/tests/CoreForthWordsTest::testNumbersToCharacters", "[CoreForthWordsTest]") {
	CHECK(testNumbersToCharacters(0) == "0");
	CHECK(testNumbersToCharacters(1) == "1");
	CHECK(testNumbersToCharacters(1234) == "1234");
	CHECK(testNumbersToCharacters(999) == "999");
}
