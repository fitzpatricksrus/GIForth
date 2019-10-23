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
#include <words/CoreForthWords.h>
#include "utils/testing/catch.hpp"

TEST_CASE( "runtime/tests/CompositeWordTest", "[CompositeWordTest]" ) {
	CompositeForthWord innerWord(CompositeForthWordBuilder("CoreForthWordsTest::innerWord")
			                        .append(&PrimitiveForthWords::ADD_ONE)
			                        .build());
	CompositeForthWord outerWord(CompositeForthWordBuilder("CoreForthWordsTest::testParseDigit")
			                        .compileConstant(10)
			                        .append(&innerWord)
			                        .append(&PrimitiveForthWords::ADD_ONE)
			                        .build());
	ForthThread thread(&outerWord);
	thread.join();
	REQUIRE(thread.getDataStackSize() == 1);
	REQUIRE(thread.popDataStack().integer == 12);
	REQUIRE(thread.getDataStackSize() == 0);
}

class PrintStringWord : public ForthWord {
public:
    PrintStringWord(const std::string &string) : msg(string) {}
    void execute(ForthThread &thread) override {
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
            .append(&hello)
            .append(&space)
            .build());
    CompositeForthWord worldCr(
            CompositeForthWordBuilder("worldCr")
            .append(&world)
	        .append(&cr)
	        .build());
    CompositeForthWord message(
            CompositeForthWordBuilder("message")
            .append(&helloSpace)
        	.append(&worldCr)
        	.append(&hello)
        	.append(&space)
        	.append(&helloSpace)
        	.append(&worldCr)
        	.build());

    ForthThread thread(&message);
    thread.enableTrace(true);
    thread.join();
}
