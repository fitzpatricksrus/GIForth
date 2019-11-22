//
// Created by Dad on 9/18/19.
//

#ifndef GIFORTH_BOOTSTRAPINTERP_H
#define GIFORTH_BOOTSTRAPINTERP_H

#include <runtime/CompositeForthWord.h>

class BootstrapInterp {
public:
    static CompositeForthWord* getInstance();
};

#endif //GIFORTH_BOOTSTRAPINTERP_H
