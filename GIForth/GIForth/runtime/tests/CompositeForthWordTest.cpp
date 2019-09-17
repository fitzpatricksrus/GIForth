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
    helloSpace.appendCell(&hello);
    helloSpace.appendCell(&space);
    CompositeForthWord worldCr;
    worldCr.appendCell(&world);
    worldCr.appendCell(&cr);
    CompositeForthWord message;
    message.appendCell(&helloSpace);
    message.appendCell(&worldCr);
    message.appendCell(&helloSpace);
    message.appendCell(&worldCr);
    ForthThread thread(&message);
    thread.join();
}
