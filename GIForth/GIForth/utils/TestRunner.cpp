//
// Created by stuff on 9/29/2019.
//

#include "TestRunner.h"

//
// Created by stuff on 9/29/2019.
//

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int TestRunner::run( int argc, char* argv[] ) {
    // global setup...

    int result = Catch::Session().run( argc, argv );

    // global clean-up...

    return result;
}