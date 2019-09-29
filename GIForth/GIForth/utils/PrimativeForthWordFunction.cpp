//
// Created by Dad on 9/17/19.
//

#include <sstream>
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

std::string PrimativeForthWordFunction::doDisassembly(const ForthThread &thread) const {
    if (args.empty()) {
        return name;
    } else {
        std::string result = name + "( ";
        int argNumber = 0;
        for (ParamType t : args) {
            ForthCell cell = thread.getCellAt(thread.getIndex() + argNumber);
            switch (t) {
                case ParamType::INT:
                    result += std::to_string(cell.integer);
                    break;
                case ParamType::BOOL:
                    result += std::to_string(static_cast<bool>(cell.integer));
                    break;
                case ParamType::CELL:
                    result += cell.word->getDisassembly(thread);
                    break;
                case ParamType::CHAR:
                    result += std::to_string(static_cast<char>(cell.integer));
                    break;
                case ParamType::PTR: {
                    std::stringstream ss;
                    ss << cell.pointer;
                    result += ss.str();
                    break;
                }
                default:
                    break;
            }
            result += " ";
            argNumber++;
        }
        return result + ")";
    }
}

int PrimativeForthWordFunction::getDisassemblyParamCount() const {
    return args.size();
}
