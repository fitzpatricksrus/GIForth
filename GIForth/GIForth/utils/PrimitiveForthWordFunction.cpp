//
// Created by Dad on 9/17/19.
//

#include <sstream>
#include "PrimitiveForthWordFunction.h"
#include "runtime/ForthThread.h"
#include "StringUtils.h"

PrimitiveForthWordFunction::PrimitiveForthWordFunction(Function funcIn, const std::string& nameIn)
        : PrimitiveForthWordFunction(funcIn, nameIn, splitName(nameIn))
{
}

PrimitiveForthWordFunction::PrimitiveForthWordFunction(PrimitiveForthWordFunction::Function funcIn,
	const std::string& disassemblyNameIn, const std::string& vocabNameIn)
	: func(funcIn), disassemblyName(disassemblyNameIn), vocabName(vocabNameIn), args()
{
}

PrimitiveForthWordFunction::PrimitiveForthWordFunction(Function funcIn, const std::string& nameIn, std::initializer_list<ParamType> params)
	: PrimitiveForthWordFunction(funcIn, nameIn, splitName(nameIn), params)
{
}

PrimitiveForthWordFunction::PrimitiveForthWordFunction(PrimitiveForthWordFunction::Function funcIn,
	const std::string& disassemblyNameIn, const std::string &vocabNameIn,
	std::initializer_list<ParamType> params)
	: func(funcIn), disassemblyName(disassemblyNameIn), vocabName(vocabNameIn), args()
{
	for (ParamType t : params) {
		args.push_back(t);
	}
}
void PrimitiveForthWordFunction::execute(ForthThread& thread) const {
    (*func)(thread);
}

std::string PrimitiveForthWordFunction::getName() const {
	return vocabName;
}

std::string PrimitiveForthWordFunction::getDisassemblyDetail(const ForthThread &thread) const {
    if (args.empty()) {
        return disassemblyName;
    } else {
        std::string result = disassemblyName + "( ";
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
	return disassemblyName;
}

int PrimitiveForthWordFunction::getDisassemblyParamCount() const {
    return args.size();
}

std::string PrimitiveForthWordFunction::splitName(const std::string& nameIn) {
	std::string name(nameIn);
	StringUtils::toLower(name);
	size_t pos = name.find("::");
	if (pos == std::string::npos) {
		return name;
	} else {
		return name.substr(pos);
	}
}