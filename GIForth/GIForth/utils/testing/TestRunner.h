//
// Created by stuff on 9/29/2019.
//

#ifndef GIFORTH_TESTRUNNER_H
#define GIFORTH_TESTRUNNER_H


class CompositeForthWord;
#include "runtime/ForthThread.h"

class TestRunner {
public:
    static int run(int argc, const char* argv[]);
    static ForthThread runTestWord(CompositeForthWord* word);
    static bool traceEnabled;

    class Tracer {
    public:
		Tracer(bool enable = true);
		~Tracer();

		bool save;
    };
};

#endif //GIFORTH_TESTRUNNER_H
