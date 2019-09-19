cmake_minimum_required(VERSION 3.10)
project(GIForth)

set(CMAKE_CXX_STANDARD 14)

include_directories(GIForth)
include_directories(GIForth/runtime)
include_directories(GIForth/runtime/tests)
include_directories(GIForth/utils)
include_directories(GIForth/words)
include_directories(GIForth/words/bootstrap)

add_executable(GIForth
    GIForth/runtime/tests/BootstrapWordsTest.cpp
    GIForth/runtime/tests/BootstrapWordsTest.h
    GIForth/runtime/tests/CompositeForthWordTest.cpp
    GIForth/runtime/tests/CompositeForthWordTest.h
    GIForth/runtime/CompositeForthWord.cpp
    GIForth/runtime/CompositeForthWord.h
    GIForth/runtime/ForthCell.h
    GIForth/runtime/ForthExecutionFrame.h
    GIForth/runtime/ForthThread.cpp
    GIForth/runtime/ForthThread.h
    GIForth/runtime/ForthWord.cpp
    GIForth/runtime/ForthWord.h
    GIForth/utils/NativeOSFunctions.cpp
    GIForth/utils/NativeOSFunctions.hpp
    GIForth/utils/PrimativeForthWordFunction.cpp
    GIForth/utils/PrimativeForthWordFunction.h
    GIForth/utils/PrimativeForthWordMemberFunction.cpp
    GIForth/utils/PrimativeForthWordMemberFunction.h
    GIForth/words/bootstrap/BootstrapInterp.cpp
    GIForth/words/bootstrap/BootstrapInterp.h
    GIForth/words/bootstrap/BootstrapWords.cpp
    GIForth/words/bootstrap/BootstrapWords.h
    GIForth/words/CoreForthWords.cpp
    GIForth/words/CoreForthWords.h
    GIForth/main.cpp
    CMakeLists.txt)
