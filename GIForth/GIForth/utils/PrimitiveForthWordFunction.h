//
// Created by Dad on 9/17/19.
//

#ifndef GIFORTH_PRIMITIVEFORTHWORDFUNCTION_H
#define GIFORTH_PRIMITIVEFORTHWORDFUNCTION_H

#include <runtime/ForthWord.h>

class PrimitiveForthWordFunction : public ForthWord {
public:
    typedef void (*Function)(ForthThread& thread);
    enum ParamType {
        BOOL,
        CHAR,
        INT,
        PTR,
        CELL,
    };

    PrimitiveForthWordFunction(Function func, const std::string& name);
    PrimitiveForthWordFunction(Function func, const std::string& name, std::initializer_list<ParamType> params);
    PrimitiveForthWordFunction(const PrimitiveForthWordFunction& other) = default;
    ~PrimitiveForthWordFunction() = default;
    PrimitiveForthWordFunction& operator=(const PrimitiveForthWordFunction& other) = default;
    void execute(ForthThread& thread) override;

protected:
	std::string getDisassemblyDetail(const ForthThread &thread) const override;
	std::string getDisassemblyName() const override;
    int getDisassemblyParamCount() const override;

private:
    Function func;
    std::string name;
    std::vector<ParamType> args;
};

#endif //GIFORTH_PRIMITIVEFORTHWORDFUNCTION_H
