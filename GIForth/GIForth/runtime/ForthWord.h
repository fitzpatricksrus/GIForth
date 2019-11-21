//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHWORD_H
#define GIFORTH_FORTHWORD_H

class ForthThread;

#include <string>

class ForthWord {
public:
    virtual void execute(ForthThread& thread) const = 0;

    virtual std::string getNameInVocabulary() const;
    virtual std::string getDisassemblyName() const = 0;
    virtual std::string getDisassemblyDetail(const ForthThread& thread) const = 0;
};

#endif //GIFORTH_FORTHWORD_H
