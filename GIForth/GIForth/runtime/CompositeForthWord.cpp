//
// Created by Dad on 9/16/19.
//

#include "CompositeForthWord.h"
#include "ForthThread.h"

void CompositeForthWord::execute(ForthThread& thread) {
    if (thread.getCurrentWord() != this) {
        // first time called, so make a new stack frame
        thread.pushFrame(this);
    }
    int ndx = thread.getIndex();
    if (ndx < body.size()) {
        ForthWord* word = body[ndx].word;
        thread.setIndex(ndx + 1);
        word->execute(thread);
    } else {
        thread.popFrame();
    }
}

int CompositeForthWord::size() const {
    return body.size();
}

const ForthCell& CompositeForthWord::operator[](int ndx) const {
    return body[ndx];
}

ForthCell& CompositeForthWord::operator[](int ndx) {
    return body[ndx];
}

void CompositeForthWord::appendCell(const ForthCell& cell) {
    body.push_back(cell);
}

