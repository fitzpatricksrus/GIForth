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
    void invoke(ForthThread& thread);
    virtual void execute(ForthThread& thread) = 0;

    virtual std::string disassemble(ForthThread &thread) = 0;
    virtual void disassemble(ForthThread &thread, std::vector<std::string>& contents);
};

inline void ForthWord::invoke(ForthThread& thread) {
    execute(thread);
}

#endif //GIFORTH_FORTHWORD_H
