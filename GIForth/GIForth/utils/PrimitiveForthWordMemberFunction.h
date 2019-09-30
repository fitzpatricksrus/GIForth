//
// Created by Dad on 9/17/19.
//

#ifndef GIFORTH_PRIMITIVEFORTHWORDMEMBERFUNCTION_H
#define GIFORTH_PRIMITIVEFORTHWORDMEMBERFUNCTION_H

#include <runtime/ForthWord.h>

template <class T>
class PrimitiveForthWordMemberFunction : public ForthWord {
public:
    typedef void (T::*MemberFunction)(ForthThread& thread);

    PrimitiveForthWordMemberFunction(T* instance, MemberFunction func);
    PrimitiveForthWordMemberFunction(const PrimitiveForthWordMemberFunction& other) = default;
    ~PrimitiveForthWordMemberFunction() = default;
    PrimitiveForthWordMemberFunction& operator=(const PrimitiveForthWordMemberFunction& other) = default;

    void execute(ForthThread& thread) override;

private:
    T* instance;
    MemberFunction func;
};

template <class T>
PrimitiveForthWordMemberFunction<T>::PrimitiveForthWordMemberFunction(T* instanceIn, MemberFunction funcIn)
: instance(instanceIn), func(funcIn)
{
}

template <class T>
void PrimitiveForthWordMemberFunction<T>:: execute(ForthThread& thread) {
    instance->*func(thread);
}

#endif //GIFORTH_PRIMITIVEFORTHWORDMEMBERFUNCTION_H
