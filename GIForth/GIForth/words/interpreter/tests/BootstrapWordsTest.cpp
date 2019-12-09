//
// Created by Dad on 9/18/19.
//

#include <string>
#include <sstream>
#include <runtime/NativeOSFunctions.hpp>
#include "words/interpreter/BootstrapWords.h"
#include "runtime/ForthThread.h"
#include "utils/testing/catch.hpp"

TEST_CASE( "words/interpreter/BootstrapWords::testNextToken", "[InterpreterTest]" ) {
	std::string inputText = "this is a test\n1 2 3 exit";
	std::istringstream iss(inputText);
	NativeOSFunctions::InputPatch input(iss);
	std::string requiredOutput[] = { "this", "is", "a", "test", "1", "2", "3", "exit"};
	for (const std::string& s : requiredOutput) {
		ForthThread thread;
		BootstrapWords::NEXT_TOKEN().execute(thread);
		std::string token = static_cast<char*>(thread.popDataStack().pointer);
		CHECK(token == s);
	}
}
