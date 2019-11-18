//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHTHREAD_H
#define GIFORTH_FORTHTHREAD_H

#include <stack>
#include <vector>
#include <map>
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

	ForthThread();
    ~ForthThread() = default;

    // data stack operations
    ForthCell peekDataStack(int ndx) const;
    ForthCell& operator[](int ndx);
    void pokeDataStack(int ndx, const ForthCell& value);
    void rollDataStack(int count);
    ForthCell popDataStack();
    void pushDataStack(const ForthCell& value);
    const ForthCell& operator[](int ndx) const;
    int getDataStackSize() const;

    // return stack operation
    ReturnStackFrame fromReturnStack();
    void toReturnStack(const ReturnStackFrame& value);
    const ReturnStackFrame& topOfReturnStack() const;
    int returnStackDepth() const;

    // execution operations
    const CompositeForthWord* getCurrentWord() const;
    int getIndex() const;
    void setIndex(int ndx);
    void offsetIndex(int offset);
    const ForthCell& getCellAt(int ndx) const;
    const ForthCell& getNextCell();
    bool currentWordComplete() const;
    void pushFrame(const CompositeForthWord* word, int ndx = 0);
    void popFrame();

	void join();
	void join(CompositeForthWord& word);
	static const ForthThread* getCurrentThread();

	void enableTrace(bool enable);
    bool isTraceEnabled() const;
    int getTraceDepth() const;
    void setTraceDepth(int depth);

private:
	static thread_local ForthThread* currentThread;

    bool trace;
    int traceDepth;

    ForthExecutionFrame ip;
    std::stack<ReturnStackFrame> returnStack;
    std::vector<ForthCell> dataStack;
};

#endif //GIFORTH_FORTHTHREAD_H
