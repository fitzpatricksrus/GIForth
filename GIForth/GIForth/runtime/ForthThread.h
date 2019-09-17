//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHTHREAD_H
#define GIFORTH_FORTHTHREAD_H

#include <stack>
#include <vector>
#include "ForthCell.h"
#include "ForthExecutionFrame.h"

class ForthThread {
public:
    typedef union ReturnStackFrame {
        ReturnStackFrame(const ForthExecutionFrame& execIn) : execution(execIn) {}
        ReturnStackFrame(const ForthCell& cellIn) : cell(cellIn) {}

        ForthExecutionFrame execution;
        ForthCell cell;
    } ReturnStackFrame;

    static const ReturnStackFrame DEAD_FRAME;

    ForthThread(const ForthExecutionFrame& start);
    ~ForthThread() = default;

    // data stack operations
    ForthCell peekDataStack(int ndx) const;
    void pokeDataStack(int ndx, const ForthCell& value);
    void rollDataStack(int count);
    ForthCell popDataStack();
    void pushDataStack(const ForthCell& value);
    const ForthCell& operator[](int ndx) const;
    ForthCell& operator[](int ndx);
    int getDataStackSize() const;

    // return stack operation
    ReturnStackFrame fromReturnStack();
    void toReturnStack(const ReturnStackFrame& value);
    int returnStackDepth() const;

    // execution operations
    CompositeForthWord* getCurrentWord() const;
    int getIndex() const;
    void setIndex(int ndx);
    void pushFrame(CompositeForthWord* word, int ndx = 0);
    void popFrame();

    bool execute();
    void join();

private:
    ForthExecutionFrame ip;
    std::stack<ReturnStackFrame> returnStack;
    std::vector<ForthCell> dataStack;
};

#endif //GIFORTH_FORTHTHREAD_H
