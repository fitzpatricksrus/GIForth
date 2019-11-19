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

    class Tracer {
    public:
		Tracer() { enableTrace = true; }
		~Tracer() { enableTrace = false; }
    };
};


#endif //GIFORTH_TESTRUNNER_H
