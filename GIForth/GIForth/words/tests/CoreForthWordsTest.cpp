//
// Created by Dad on 9/28/19.
//

#include <iostream>
#include "runtime/ForthThread.h"
#include "words/bootstrap/CompositeForthWordBuilder.h"
#include "words/PrimitiveForthWords.h"
#include "words/CoreForthWords.h"
#include "CoreForthWordsTest.h"

static void testParseDigitWith(char c) {
	CompositeForthWord word(CompositeForthWordBuilder("CoreForthWordsTest::testParseDigit")
					.append(&PrimitiveForthWords::PUSH_NEXT_CELL)
					.append(static_cast<ForthCell::CHAR_TYPE>(c))
					.append(&CoreForthWords::PARSE_DIGIT)
					.build());
	ForthThread thread(&word);
	thread.enableTrace(true);
	thread.join();
	std::cout << "'" << c << "' CoreForthWords::PARSE_DIGIT . " << std::endl;
	std::cout << thread.popDataStack().integer << std::endl;
}

void CoreForthWordsTest::testParseDigit() {
	testParseDigitWith('0');
	testParseDigitWith('9');
	testParseDigitWith(static_cast<char>('0' - 1));
	testParseDigitWith(static_cast<char>('9' + 1));
}

static void testParseNUmberWith(const char* c) {
	CompositeForthWord word(CompositeForthWordBuilder("CoreForthWordsTest::testParseDigit")
			                        .append(&PrimitiveForthWords::PUSH_NEXT_CELL)
			                        .append(static_cast<ForthCell::PTR_TYPE>(const_cast<char*>(c)))
			                        .append(&CoreForthWords::PARSE_NUMBER)
			                        .build());
	ForthThread thread(&word);
	thread.enableTrace(true);
	thread.join();
	std::cout << "'" << c << "' CoreForthWords::PARSE_NUMBER . . " << std::endl;
	std::cout << thread.popDataStack().integer << "  " << thread.popDataStack().integer << std::endl;
}

void CoreForthWordsTest::testParseNumber() {
	// stringAddr -- [ value true | stringAddr false ]
	testParseNUmberWith("1234");
	testParseNUmberWith("1");
	testParseNUmberWith("999");
	testParseNUmberWith("0");
	testParseNUmberWith("123j3847");
	testParseNUmberWith("j1233847");
	testParseNUmberWith("1233847j");
	
}
