//
//  main.cpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include <words/interpreter/tests/OuterInterpTest.h>
#include "utils/testing/TestRunner.h"

int main(int argc, const char * argv[]) {
	const char* testArgs[] = {
			"dummy", //"--listtags"
	};
	int testArgCount = sizeof(testArgs) / sizeof(testArgs[0]);
	TestRunner::run(testArgCount, testArgs);
	OuterInterpTest::test();
	return 0;
}
