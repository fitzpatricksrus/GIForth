//
// Created by Dad on 9/17/19.
//

#ifndef GIFORTH_PRIMATIVEFORTHWORDMEMBERFUNCTION_H
#define GIFORTH_PRIMATIVEFORTHWORDMEMBERFUNCTION_H

#include <runtime/ForthWord.h>

template <class T>
class PrimativeForthWordMemberFunction : public ForthWord {
public:
    typedef void (T::*MemberFunction)(ForthThread& thread);

    PrimativeForthWordMemberFunction(T* instance, MemberFunction func);
    PrimativeForthWordMemberFunction(const PrimativeForthWordMemberFunction& other) = default;
    ~PrimativeForthWordMemberFunction() = default;
    PrimativeForthWordMemberFunction& operator=(const PrimativeForthWordMemberFunction& other) = default;

    void execute(ForthThread& thread) override;

private:
    T* instance;
    MemberFunction func;
};

template <class T>
PrimativeForthWordMemberFunction<T>::PrimativeForthWordMemberFunction(T* instanceIn, MemberFunction funcIn)
: instance(instanceIn), func(funcIn)
{
}

template <class T>
void PrimativeForthWordMemberFunction<T>:: execute(ForthThread& thread) {
    instance->*func(thread);
}

#endif //GIFORTH_PRIMATIVEFORTHWORDMEMBERFUNCTION_H
