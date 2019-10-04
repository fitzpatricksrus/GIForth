//
// Created by Dad on 9/17/19.
//

#include <sstream>
#include "PrimitiveForthWordFunction.h"
#include "runtime/ForthThread.h"

PrimitiveForthWordFunction::PrimitiveForthWordFunction(Function funcIn, const std::string& nameIn)
        : func(funcIn), name(nameIn), args()
{
}

PrimitiveForthWordFunction::PrimitiveForthWordFunction(Function funcIn, const std::string& nameIn, std::initializer_list<ParamType> params)
        : func(funcIn), name(nameIn), args()
{
    for (ParamType t : params) {
        args.push_back(t);
    }
}

void PrimitiveForthWordFunction::execute(ForthThread& thread) {
    (*func)(thread);
}

std::string PrimitiveForthWordFunction::getTraceDetail(const ForthThread &thread) const {
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
                    result += cell.word->getTrace(thread);
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

std::string PrimitiveForthWordFunction::getDisassemblyName() const {
	return name;
}

int PrimitiveForthWordFunction::getDisassemblyParamCount() const {
    return args.size();
}
