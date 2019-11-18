//
// Created by Dad on 9/17/19.
//

#include "CompositeForthWordTest.h"

#include <string>
#include <iostream>
#include <runtime/CompositeForthWord.h>
#include <runtime/ForthThread.h>
#include <words/bootstrap/CompositeForthWordBuilder.h>
#include <words/PrimitiveForthWords.h>
#include <utils/testing/TestRunner.h>
#include "utils/testing/catch.hpp"

TEST_CASE("runtime/tests/CompositeWordTest", "[RuntimeTests]") {
	CompositeForthWord innerWord(CompositeForthWordBuilder("CoreForthWordsTest::CompositeWordTest::innerWord")
										 .compileCell(&PrimitiveForthWords::ADD_ONE)
										 .compileCell(&PrimitiveForthWords::ADD_ONE)
			                        .build());
	CompositeForthWord outerWord(CompositeForthWordBuilder("CoreForthWordsTest::CompositeWordTest::outerWord")
			                             .compileConstant(10)
			                             .compileCell(&innerWord)
			                             .compileCell(&PrimitiveForthWords::ADD_ONE)
			                        .build());
	ForthThread thread(TestRunner::runTestWord(&outerWord));
	REQUIRE(thread.getDataStackSize() == 1);
	CHECK(thread.popDataStack().integer == 13);
	CHECK(thread.getDataStackSize() == 0);
}

class PrintStringWord : public ForthWord {
public:
    PrintStringWord(const std::string &string) : msg(string) {}
    void execute(ForthThread &thread) const override {
        std::cout << msg;
    }

    std::string getDisassemblyDetail(const ForthThread& thread) const override {
        return std::string("PrintStringWord(\"") + msg + "\")";
    };

    std::string getDisassemblyName() const override {
    	return "PrintStringWord";
    }
    
    int getDisassemblyParamCount() const override {
        return 0;
    }


private:
    std::string msg;
};

void CompositeForthWordTest::test() {
    PrintStringWord hello("Hello");
    PrintStringWord world("World");
    PrintStringWord space(" ");
    PrintStringWord cr("\n");

    CompositeForthWord helloSpace(
		    CompositeForthWordBuilder("helloSpace")
				    .compileCell(&hello)
				    .compileCell(&space)
            .build());
    CompositeForthWord worldCr(
		    CompositeForthWordBuilder("worldCr")
				    .compileCell(&world)
				    .compileCell(&cr)
	        .build());
    CompositeForthWord message(
		    CompositeForthWordBuilder("message")
				    .compileCell(&helloSpace)
				    .compileCell(&worldCr)
				    .compileCell(&hello)
				    .compileCell(&space)
				    .compileCell(&helloSpace)
				    .compileCell(&worldCr)
        	.build());

    ForthThread thread;
    thread.enableTrace(true);
    thread.join(message);
}
