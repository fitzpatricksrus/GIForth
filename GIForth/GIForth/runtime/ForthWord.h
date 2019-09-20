//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHWORD_H
#define GIFORTH_FORTHWORD_H

class ForthThread;

class ForthWord {
public:
    virtual void execute(ForthThread& thread) = 0;
	// virtual void trace(ForthThread& thread, string& msgOut) = 0;
	// virtual int disassemble(ForthThread& thread, std::vector<string>& msgOut) = 0;
};

#endif //GIFORTH_FORTHWORD_H
