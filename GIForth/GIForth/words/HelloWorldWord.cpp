//
// Created by Dad on 9/16/19.
//

#include "HelloWorldWord.h"

#include <iostream>

void HelloWorldWord::execute(ForthThread& thread) {
    std::cout << "Hello World" << std::endl;
}
