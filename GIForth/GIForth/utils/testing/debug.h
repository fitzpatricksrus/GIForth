//
// Created by Dad on 11/23/19.
//

#ifndef GIFORTH_DEBUG_H
#define GIFORTH_DEBUG_H

#include <exception>

class DebugException : std::exception {
public:
	DebugException(const std::string& msgIn) : std::exception(), msg(msgIn) {}
	const std::string msg;
};

#ifdef NDEBUG
#define assertTrue(x)
#else
#define assertTrue(x)				\
	if (!(x)) { 					\
		std::string f(__FILE__);	\
		std::string l(std::to_string(__LINE__));	\
		std::string m(#x);			\
		throw DebugException(f+":"+l+" "+m); \
	}
#endif

#endif //GIFORTH_DEBUG_H
