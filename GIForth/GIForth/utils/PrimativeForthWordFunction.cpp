//
// Created by Dad on 9/17/19.
//

#include "PrimativeForthWordFunction.h"
#include "runtime/ForthThread.h"

PrimativeForthWordFunction::PrimativeForthWordFunction(Function funcIn, const std::string& nameIn)
        : func(funcIn), name(nameIn), args()
{
}

PrimativeForthWordFunction::PrimativeForthWordFunction(Function funcIn, const std::string& nameIn, std::initializer_list<ParamType> params)
        : func(funcIn), name(nameIn), args()
{
    for (ParamType t : params) {
        args.push_back(t);
    }
}

void PrimativeForthWordFunction::execute(ForthThread& thread) {
    (*func)(thread);
}

std::string PrimativeForthWordFunction::disassemble(ForthThread &thread) {
    std::string result = name + "( ";
    for (ParamType t : args) {
        ForthCell cell = thread.getNextCell();
        switch (t) {
            case ParamType::INT:
                result += cell.integer;
                break;
            case ParamType::BOOL:
                result += cell.boolean;
                break;
            case ParamType::CELL:
                result += cell.word->disassemble(thread);
                break;
            case ParamType::CHAR:
                result += cell.character;
                break;
            case ParamType::PTR:
                result += (long)cell.pointer;
                break;
            default:
                break;
        }
        result += " ";
    }
    return result + ")";
}
