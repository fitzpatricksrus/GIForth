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
		Tracer(bool enable = true);
		~Tracer();

		bool save;
    };
};

inline TestRunner::Tracer::Tracer(bool e)
: save(enableTrace)
{
	enableTrace = e;
}

inline TestRunner::Tracer::~Tracer() {
	enableTrace = save;
}

#endif //GIFORTH_TESTRUNNER_H
