cmake_minimum_required(VERSION 3.10)
project(GIForth)

set(CMAKE_CXX_STANDARD 14)

include_directories(GIForth)

add_executable(GIForth
        GIForth/ExecutionContext.cpp
        GIForth/ExecutionContext.hpp
        GIForth/FMemory.cpp
        GIForth/FMemory.hpp
        GIForth/ForthArchitecture.cpp
        GIForth/ForthArchitecture.hpp
        GIForth/ForthDictionary.cpp
        GIForth/ForthDictionary.hpp
        GIForth/ForthExecutionContext.cpp
        GIForth/ForthExecutionContext.hpp
        GIForth/ForthInstruction.cpp
        GIForth/ForthInstruction.hpp
        GIForth/ForthInterpreter.cpp
        GIForth/ForthInterpreter.hpp
        GIForth/ForthMemory.cpp
        GIForth/ForthMemory.hpp
        GIForth/ForthWord.cpp
        GIForth/ForthWord.hpp
        GIForth/Interpreter.cpp
        GIForth/Interpreter.hpp
        GIForth/main.cpp
        GIForth/NativeOSFunctions.cpp
        GIForth/NativeOSFunctions.hpp)
