//
// Created by Dad on 9/17/19.
//

#include "CompositeForthWordTest.h"

#include <string>
#include <iostream>
#include <runtime/CompositeForthWord.h>
#include <runtime/ForthThread.h>

class PrintStringWord : public ForthWord {
public:
    PrintStringWord(const std::string &string) : msg(string) {}
    void execute(ForthThread &thread) override {
        std::cout << msg;
    }

private:
    std::string msg;
};

void CompositeForthWordTest::test() {
    PrintStringWord hello("Hello");
    PrintStringWord world("World");
    PrintStringWord space(" ");
    PrintStringWord cr("\n");

    CompositeForthWord helloSpace;
    helloSpace << &hello << &space;
    CompositeForthWord worldCr;
    worldCr << &world << &cr;
    CompositeForthWord message;
    message << &helloSpace << &worldCr << &hello << &space << &helloSpace << &worldCr;

    ForthThread thread(&message);
    thread.join();
}
