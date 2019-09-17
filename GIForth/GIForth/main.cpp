//
//  main.cpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include <runtime/CompositeForthWord.h>
#include <runtime/ForthThread.h>
#include <words/HelloWorldWord.h>
#include <runtime/tests/CompositeForthWordTest.h>

int main(int argc, const char * argv[]) {
    CompositeForthWordTest::test();
	return 0;
}
