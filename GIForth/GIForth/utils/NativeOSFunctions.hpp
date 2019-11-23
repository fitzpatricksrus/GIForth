//
//  NativeOSFunctions.hpp
//  GIForth
//
//  Created by Dad on 8/5/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#ifndef NativeOSFunctions_hpp
#define NativeOSFunctions_hpp

#include <string>
#include <stack>

class NativeOSFunctions {
public:

    static int accept(char* buffer, int size);

	static char peekNextChar();
	static char nextChar();
	static void flushInput();

	static void pushInputStream(std::istream& input);
	static void popInputStream();
	static std::istream& currentInputStream();

    static void printChar(char c);
    static void printString(const char* string);
    static void printString(const std::string& string);
    static void endLine();
	static void pushOutputStream(std::ostream& output);
	static void popOutputStream();
	static std::ostream& currentOutputStream();

	class InputPatch {
	public:
		InputPatch(std::istream& input) {
			pushInputStream(input);
		}
		~InputPatch() {
			popInputStream();
		}
	};

	class OutputPatch {
	public:
		OutputPatch(std::ostream& output) {
			pushOutputStream(output);
		}
		~OutputPatch() {
			popOutputStream();
		}
	};

private:
    static std::string inputBuffer;
    static int inputPos;
	static std::stack<std::istream*> inputStreams;
	static std::stack<std::ostream*> outputStreams;
};

#endif /* NativeOSFunctions_hpp */
