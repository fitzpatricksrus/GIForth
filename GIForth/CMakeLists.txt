cmake_minimum_required(VERSION 3.10)
project(GIForth)

set(CMAKE_CXX_STANDARD 14)

include_directories(GIForth)

add_executable(GIForth
        GIForth/words/interpreter/tests/BootstrapWordsTest.cpp
        GIForth/runtime/tests/CompositeForthWordTest.cpp
        GIForth/runtime/CompositeForthWord.cpp
        GIForth/runtime/ForthThread.cpp
        GIForth/runtime/ForthWord.cpp
        GIForth/utils/NativeOSFunctions.cpp
        GIForth/utils/PrimitiveForthWordFunction.cpp
        GIForth/words/interpreter/BootstrapInterp.cpp
        GIForth/words/interpreter/BootstrapWords.cpp
        GIForth/words/PrimitiveForthWords.cpp
        GIForth/main.cpp
        CMakeLists.txt
        GIForth/words/interpreter/tests/BootstrapInterpTest.cpp
        GIForth/words/CoreForthWords.cpp
        GIForth/words/CoreForthWords.h
        GIForth/utils/CompositeForthWordBuilder.cpp
        GIForth/utils/CompositeForthWordBuilder.h
        GIForth/words/tests/CoreForthWordsTest.cpp
        GIForth/words/tests/CoreForthWordsTest.h
        GIForth/utils/StringUtils.cpp
        GIForth/utils/StringUtils.h
        GIForth/utils/testing/TestRunner.cpp
        GIForth/utils/testing/TestRunner.h
        GIForth/words/compiler/ForthVocab.cpp
        GIForth/words/compiler/ForthVocab.h
        GIForth/words/compiler/BasicForthVocab.cpp
        GIForth/words/compiler/BasicForthVocab.h
        GIForth/words/compiler/CompilerWords.cpp
        GIForth/words/compiler/CompilerWords.h
        GIForth/utils/tests/StringUtilsTest.cpp
        GIForth/utils/tests/StringUtilsTest.h
        GIForth/words/compiler/tests/CompilerWordsTest.cpp
        GIForth/words/compiler/tests/CompilerWordsTest.h GIForth/words/tests/PrimitiveForthWordsTest.cpp)
