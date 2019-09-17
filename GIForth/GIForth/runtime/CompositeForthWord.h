//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_COMPOSITEFORTHWORD_H
#define GIFORTH_COMPOSITEFORTHWORD_H

#include <vector>
#include "ForthWord.h"
#include "ForthCell.h"

class ForthThread;

class CompositeForthWord : public ForthWord {
public:
    void execute(ForthThread& thread) override;

    int size() const;
    const ForthCell& operator[](int ndx) const;
    ForthCell& operator[](int ndx);
    void appendCell(const ForthCell& cell);

private:
    std::vector<ForthCell> body;
};

#endif //GIFORTH_COMPOSITEFORTHWORD_H
