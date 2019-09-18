//
// Created by Dad on 9/17/19.
//

#ifndef GIFORTH_PRIMATIVEFORTHWORDFUNCTION_H
#define GIFORTH_PRIMATIVEFORTHWORDFUNCTION_H

#include <runtime/ForthWord.h>

class PrimativeForthWordFunction : public ForthWord {
public:
    typedef void (*Function)(ForthThread& thread);

    PrimativeForthWordFunction(Function func);
    PrimativeForthWordFunction(const PrimativeForthWordFunction& other) = default;
    ~PrimativeForthWordFunction() = default;
    PrimativeForthWordFunction& operator=(const PrimativeForthWordFunction& other) = default;
    void execute(ForthThread& thread) override;

private:
    Function func;
};

#endif //GIFORTH_PRIMATIVEFORTHWORDFUNCTION_H
