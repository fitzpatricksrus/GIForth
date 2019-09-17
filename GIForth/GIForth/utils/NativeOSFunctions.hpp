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

class NativeOSFunctions {
public:
	static char peekNextChar();
	static char nextChar();

    static void printChar(char c);

private:
    static std::string inputBuffer;
    static int inputPos;
};

#endif /* NativeOSFunctions_hpp */