//
// Created by Dad on 9/18/19.
//

#include "BootstrapWordsTest.h"
#include <iostream>
#include <string>
#include "words/bootstrap/BootstrapWords.h"
#include "runtime/ForthThread.h"

void BootstrapWordsTest::testNextToken() {
    std::string endToken = "exit";
    ForthThread thread;
    std::string token;
    do {
        BootstrapWords::NEXT_TOKEN.execute(thread);
        token = static_cast<char*>(thread.popDataStack().pointer);
        std::cout << token << std::endl;
    } while (endToken != token);
}
