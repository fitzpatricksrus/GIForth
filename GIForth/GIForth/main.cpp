//
//  main.cpp
//  GIForth
//
//  Created by Dad on 7/31/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#include <iostream>
#include <runtime/CompositeForthWord.h>
#include <runtime/ForthThread.h>
#include <words/HelloWorldWord.h>


int main(int argc, const char * argv[]) {
    CompositeForthWord comp;
    HelloWorldWord hw;
    comp.appendCell(ForthCell(&hw));
    ForthExecutionFrame frame(&comp);
    ForthThread thread(frame);
    thread.join();
	return 0;
}
