cmake_minimum_required(VERSION 3.10)
project(GIForth)

set(CMAKE_CXX_STANDARD 14)

include_directories(GIForth)

add_executable(GIForth
        GIForth/ForthDictionary.cpp
        GIForth/ForthDictionaryWord.cpp
        GIForth/main.cpp
        GIForth/utils/NativeOSFunctions.cpp
        GIForth/runtime/ForthThread.cpp
        GIForth/runtime/ForthWord.cpp
        GIForth/runtime/CompositeForthWord.cpp
        GIForth/runtime/tests/CompositeForthWordTest.cpp
        GIForth/runtime/tests/CompositeForthWordTest.h
        GIForth/utils/PrimativeForthWordMemberFunction.cpp
        GIForth/utils/PrimativeForthWordMemberFunction.h
        GIForth/utils/PrimativeForthWordFunction.cpp
        GIForth/utils/PrimativeForthWordFunction.h
        GIForth/words/CoreForthWords.cpp
        GIForth/words/CoreForthWords.h
        )
