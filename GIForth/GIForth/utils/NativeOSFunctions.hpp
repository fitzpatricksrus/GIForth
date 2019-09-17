//
//  NativeOSFunctions.hpp
//  GIForth
//
//  Created by Dad on 8/5/18.
//  Copyright © 2018 Dad. All rights reserved.
//

#ifndef NativeOSFunctions_hpp
#define NativeOSFunctions_hpp

class NativeOSFunctions {
public:
	static char peekNextChar();
	static char nextChar();

    static void printChar(char c);
};

#endif /* NativeOSFunctions_hpp */
