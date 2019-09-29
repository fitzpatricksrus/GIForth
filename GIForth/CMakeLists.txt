cmake_minimum_required(VERSION 3.10)
project(GIForth)

set(CMAKE_CXX_STANDARD 14)

include_directories(GIForth)

add_executable(GIForth
        GIForth/words/bootstrap/tests/BootstrapWordsTest.cpp
        GIForth/runtime/tests/CompositeForthWordTest.cpp
        GIForth/runtime/CompositeForthWord.cpp
        GIForth/runtime/ForthThread.cpp
        GIForth/runtime/ForthWord.cpp
        GIForth/utils/NativeOSFunctions.cpp
        GIForth/utils/PrimativeForthWordFunction.cpp
        GIForth/utils/PrimativeForthWordMemberFunction.cpp
        GIForth/words/bootstrap/BootstrapInterp.cpp
        GIForth/words/bootstrap/BootstrapWords.cpp
        GIForth/words/PrimitiveForthWords.cpp
        GIForth/main.cpp
        CMakeLists.txt
        GIForth/words/bootstrap/tests/BootstrapInterpTest.cpp
        GIForth/words/CoreForthWords.cpp GIForth/words/CoreForthWords.h GIForth/words/bootstrap/CompositeForthWordBuilder.cpp GIForth/words/bootstrap/CompositeForthWordBuilder.h GIForth/words/tests/CoreForthWordsTest.cpp GIForth/words/tests/CoreForthWordsTest.h)
