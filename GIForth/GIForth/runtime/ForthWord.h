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

    std::string getDisassembly(const ForthThread& thread) const;
    virtual int getDisassemblyParamCount() const = 0;

protected:
    virtual std::string doDisassembly(const ForthThread& thread) const = 0;
};

inline void ForthWord::invoke(ForthThread& thread) {
    execute(thread);
}

#endif //GIFORTH_FORTHWORD_H
