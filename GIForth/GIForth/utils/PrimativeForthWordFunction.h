//
// Created by Dad on 9/17/19.
//

#ifndef GIFORTH_PRIMATIVEFORTHWORDFUNCTION_H
#define GIFORTH_PRIMATIVEFORTHWORDFUNCTION_H

#include <runtime/ForthWord.h>

class PrimativeForthWordFunction : public ForthWord {
public:
    typedef void (*Function)(ForthThread& thread);
    enum ParamType {
        BOOL,
        CHAR,
        INT,
        PTR,
        CELL,
    };

    PrimativeForthWordFunction(Function func, const std::string& name);
    PrimativeForthWordFunction(Function func, const std::string& name, std::initializer_list<ParamType> params);
    PrimativeForthWordFunction(const PrimativeForthWordFunction& other) = default;
    ~PrimativeForthWordFunction() = default;
    PrimativeForthWordFunction& operator=(const PrimativeForthWordFunction& other) = default;
    void execute(ForthThread& thread) override;

protected:
	std::string doDisassembly(const ForthThread &thread) const override;
	std::string getName() const override;
    int getDisassemblyParamCount() const override;

private:
    Function func;
    std::string name;
    std::vector<ParamType> args;
};

#endif //GIFORTH_PRIMATIVEFORTHWORDFUNCTION_H
