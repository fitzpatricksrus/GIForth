//
// Created by Dad on 11/23/19.
//

#ifndef GIFORTH_DEBUG_H
#define GIFORTH_DEBUG_H

#include <exception>

class CheckException : std::exception {
public:
	explicit CheckException(std::string file, int line, const std::string& msgIn) : std::exception(), msg(std::move(file)) {
		msg += ":";
		msg += std::to_string(line);
		msg += " ";
		msg += msgIn;
	}
	std::string msg;
};

#define checkTrue(x) if (!(x)) throw CheckException(__FILE__, __LINE__, #x)

#ifdef NDEBUG
#define assertTrue(x)
#else
#define assertTrue(x) if (!(x)) throw CheckException(__FILE__, __LINE__, #x)
#endif

#endif //GIFORTH_DEBUG_H
