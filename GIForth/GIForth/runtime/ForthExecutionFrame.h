//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHEXECUTIONFRAME_H
#define GIFORTH_FORTHEXECUTIONFRAME_H

class CompositeForthWord;

class ForthExecutionFrame {
public:
    ForthExecutionFrame();
    ForthExecutionFrame(CompositeForthWord* wordIn, int ndx = 0);
    ForthExecutionFrame(const ForthExecutionFrame& other) = default;
    ~ForthExecutionFrame() = default;
    ForthExecutionFrame& operator=(const ForthExecutionFrame& other);

    bool isDeadFrame() const;

    int ndx;
    CompositeForthWord* word;
};

inline ForthExecutionFrame::ForthExecutionFrame()
: ndx(0), word(nullptr)
{
}

inline ForthExecutionFrame::ForthExecutionFrame(CompositeForthWord* wordIn, int ndxIn)
: ndx(ndxIn), word(wordIn)
{
}

inline ForthExecutionFrame& ForthExecutionFrame::operator=(const ForthExecutionFrame& other) {
    ndx = other.ndx;
    word = other.word;
}

inline bool ForthExecutionFrame::isDeadFrame() const {
    return word == nullptr;
}
#endif //GIFORTH_FORTHEXECUTIONFRAME_H
