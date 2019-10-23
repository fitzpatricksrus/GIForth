//
//  main.cpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include "utils/testing/TestRunner.h"

int main(int argc, const char * argv[]) {
//    CompositeForthWordTest::test();
//    BootstrapWordsTest::testNextToken();
//	BootstrapInterpTest::test();
//	CoreForthWordsTest::testParseNumber();

	const char* testArgs[] = {
			"--list-test-names-only"
	};
	int testArgCount = sizeof(testArgs) / sizeof(testArgs[0]);
	TestRunner::run(testArgCount, testArgs);
	return 0;
}
