//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHWORD_H
#define GIFORTH_FORTHWORD_H

class ForthThread;

#include <string>
#include <vector>

class ForthWord {
public:
    virtual void execute(ForthThread& thread) = 0;

    std::string getTrace(const ForthThread& thread) const;
    virtual int getDisassemblyParamCount() const = 0;

protected:
	virtual std::string getDisassemblyName() const = 0;
    virtual std::string getTraceDetail(const ForthThread& thread) const = 0;
};

#endif //GIFORTH_FORTHWORD_H
