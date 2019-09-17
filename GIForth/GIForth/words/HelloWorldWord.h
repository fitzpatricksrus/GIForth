//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_HELLOWORLDWORD_H
#define GIFORTH_HELLOWORLDWORD_H

#include "runtime/ForthWord.h"

class HelloWorldWord : public ForthWord {
public:
    void execute(ForthThread& thread) override;
};

#endif //GIFORTH_HELLOWORLDWORD_H
