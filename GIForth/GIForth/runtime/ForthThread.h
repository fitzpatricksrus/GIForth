//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHTHREAD_H
#define GIFORTH_FORTHTHREAD_H

#include <stack>
#include <vector>
#include <map>
#include "ForthCell.h"

class CompositeForthWord;

class ForthThread {
public:
	class ForthExecutionFrame {
	public:
		ForthExecutionFrame();
		ForthExecutionFrame(const CompositeForthWord* wordIn, int ndx = 0);
		ForthExecutionFrame(const ForthExecutionFrame& other) = default;
		~ForthExecutionFrame() = default;
		ForthExecutionFrame& operator=(const ForthExecutionFrame &other) = default;

		int ndx;
		const CompositeForthWord* word;
	};

    typedef union ReturnStackFrame {
        ReturnStackFrame(const ForthExecutionFrame& execIn) : execution(execIn) {}
        ReturnStackFrame(const ForthCell& cellIn) : cell(cellIn) {}

        ForthExecutionFrame execution;
        ForthCell cell;
    } ReturnStackFrame;

    static const ForthExecutionFrame DEAD_FRAME;
	class ThreadExitException : public std::exception {};

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
    void pushFrame(const ForthExecutionFrame& frame);
    void popFrame();

	void join();
	void join(const CompositeForthWord& word);
	static const ForthThread* getCurrentThread();

	void enableTrace(bool enable);
    bool isTraceEnabled() const;
    int getTraceDepth() const;
    void setTraceDepth(int depth);

private:
	void doTrace(const ForthWord* word) const;

	static thread_local ForthThread* currentThread;

    bool trace;
    int traceDepth;

    ForthExecutionFrame ip;
    std::stack<ReturnStackFrame> returnStack;
    std::vector<ForthCell> dataStack;
};

inline ForthThread::ForthExecutionFrame::ForthExecutionFrame()
		: ForthExecutionFrame(nullptr, 0) {
}

inline ForthThread::ForthExecutionFrame::ForthExecutionFrame(const CompositeForthWord* wordIn, int ndx)
		: ndx(ndx), word(wordIn) {
}

inline int ForthThread::getIndex() const {
	return ip.ndx;
}

inline void ForthThread::setIndex(int newIndex) {
	ip.ndx = newIndex;
}



#endif //GIFORTH_FORTHTHREAD_H
