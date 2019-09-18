//
// Created by Dad on 9/17/19.
//

#include "PrimativeForthWordFunction.h"

PrimativeForthWordFunction::PrimativeForthWordFunction(Function funcIn)
: func(funcIn)
{
}

void PrimativeForthWordFunction::execute(ForthThread& thread) {
    (*func)(thread);
}
