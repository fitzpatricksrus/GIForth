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
        GIForth/utils/PrimitiveForthWordFunction.cpp
        GIForth/words/bootstrap/BootstrapInterp.cpp
        GIForth/words/bootstrap/BootstrapWords.cpp
        GIForth/words/PrimitiveForthWords.cpp
        GIForth/main.cpp
        CMakeLists.txt
        GIForth/words/bootstrap/tests/BootstrapInterpTest.cpp
        GIForth/words/CoreForthWords.cpp
        GIForth/words/CoreForthWords.h
        GIForth/words/bootstrap/CompositeForthWordBuilder.cpp
        GIForth/words/bootstrap/CompositeForthWordBuilder.h
        GIForth/words/tests/CoreForthWordsTest.cpp
        GIForth/words/tests/CoreForthWordsTest.h
        GIForth/utils/StringUtils.cpp
        GIForth/utils/StringUtils.h
        GIForth/utils/testing/TestRunner.cpp
        GIForth/utils/testing/TestRunner.h
        GIForth/compiler/ForthVocab.cpp
        GIForth/compiler/ForthVocab.h
        GIForth/compiler/BasicForthVocab.cpp
        GIForth/compiler/BasicForthVocab.h GIForth/compiler/CompilerWords.cpp GIForth/compiler/CompilerWords.h GIForth/utils/tests/StringUtilsTest.cpp GIForth/utils/tests/StringUtilsTest.h GIForth/compiler/tests/CompilerWordsTest.cpp GIForth/compiler/tests/CompilerWordsTest.h GIForth/runtime/InterpretableForthWord.cpp GIForth/runtime/InterpretableForthWord.h)
