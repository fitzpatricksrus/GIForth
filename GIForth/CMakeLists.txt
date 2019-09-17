cmake_minimum_required(VERSION 3.10)
project(GIForth)

set(CMAKE_CXX_STANDARD 14)

include_directories(GIForth)

add_executable(GIForth
        GIForth/ForthDictionary.cpp
        GIForth/ForthDictionaryWord.cpp
        GIForth/oldruntime/Interpreter.cpp
        GIForth/main.cpp
        GIForth/utils/NativeOSFunctions.cpp
        GIForth/runtime/ForthThread.cpp
        GIForth/runtime/ForthWord.cpp
        GIForth/runtime/CompositeForthWord.cpp
        GIForth/words/HelloWorldWord.cpp
        )
