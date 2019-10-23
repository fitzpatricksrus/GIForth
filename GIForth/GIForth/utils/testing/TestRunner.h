//
// Created by stuff on 9/29/2019.
//

#ifndef GIFORTH_TESTRUNNER_H
#define GIFORTH_TESTRUNNER_H


class CompositeForthWord;
#include "runtime/ForthThread.h"

class TestRunner {
public:
	static bool enableTrace;
    static int run(int argc, const char* argv[]);
    static ForthThread runTestWord(CompositeForthWord* word);
};


#endif //GIFORTH_TESTRUNNER_H
