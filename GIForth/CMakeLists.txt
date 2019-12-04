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
        GIForth/runtime/NativeOSFunctions.cpp
        GIForth/runtime/utils/PrimitiveForthWordFunction.cpp
        GIForth/words/interpreter/BootstrapInterp.cpp
        GIForth/words/interpreter/BootstrapWords.cpp
        GIForth/runtime/PrimitiveForthWords.cpp
        GIForth/main.cpp
        CMakeLists.txt
        GIForth/words/interpreter/tests/BootstrapInterpTest.cpp
        GIForth/words/CoreForthWords.cpp
        GIForth/runtime/utils/CompositeForthWordBuilder.cpp
        GIForth/words/tests/CoreForthWordsTest.cpp
        GIForth/utils/StringUtils.cpp
        GIForth/utils/testing/TestRunner.cpp
        GIForth/runtime/ForthVocab.cpp
        GIForth/runtime/BasicForthVocab.cpp
        GIForth/words/VocabWords.cpp
        GIForth/utils/tests/StringUtilsTest.cpp
        GIForth/runtime/tests/PrimitiveForthWordsTest.cpp
        GIForth/runtime/CompositeForthWordWords.cpp
        GIForth/runtime/tests/CompositeForthWordWordsTest.cpp
        GIForth/words/compiler/CompilerWords.cpp
        )
