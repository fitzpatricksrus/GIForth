//
//  main.cpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include <runtime/tests/CompositeForthWordTest.h>
#include <words/bootstrap/tests/BootstrapWordsTest.h>
#include <words/bootstrap/tests/BootstrapInterpTest.h>

int main(int argc, const char * argv[]) {
//    CompositeForthWordTest::test();
//    BootstrapWordsTest::testNextToken();
	BootstrapInterpTest::test();
	return 0;
}
