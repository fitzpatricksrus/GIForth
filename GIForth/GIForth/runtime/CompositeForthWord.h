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
    CompositeForthWord& appendCell(const ForthCell& cell);

private:
    std::vector<ForthCell> body;
};

inline int CompositeForthWord::size() const {
    return body.size();
}

inline const ForthCell& CompositeForthWord::operator[](int ndx) const {
    return body[ndx];
}

inline ForthCell& CompositeForthWord::operator[](int ndx) {
    return body[ndx];
}

inline CompositeForthWord& CompositeForthWord::appendCell(const ForthCell& cell) {
    body.push_back(cell);
    return *this;
}

inline CompositeForthWord& operator<<(CompositeForthWord& us, ForthCell const& cell) {
    return us.appendCell(cell);
}

#endif //GIFORTH_COMPOSITEFORTHWORD_H
