//
//  main.cpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include <runtime/tests/CompositeForthWordTest.h>
#include <runtime/tests/BootstrapWordsTest.h>

int main(int argc, const char * argv[]) {
    CompositeForthWordTest::test();
    BootstrapWordsTest::testNextToken();
	return 0;
}
