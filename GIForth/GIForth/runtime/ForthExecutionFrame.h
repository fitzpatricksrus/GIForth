//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHEXECUTIONFRAME_H
#define GIFORTH_FORTHEXECUTIONFRAME_H

class CompositeForthWord;

class ForthExecutionFrame {
public:
	ForthExecutionFrame();
	ForthExecutionFrame(const CompositeForthWord* wordIn, int ndx);
	ForthExecutionFrame(const ForthExecutionFrame& other) = default;
	~ForthExecutionFrame() = default;
	ForthExecutionFrame& operator=(const ForthExecutionFrame &other) = default;

	int ndx;
	const CompositeForthWord* word;
};

inline ForthExecutionFrame::ForthExecutionFrame()
		: ForthExecutionFrame(nullptr, 0) {
}

inline ForthExecutionFrame::ForthExecutionFrame(const CompositeForthWord* wordIn, int ndx = 0)
		: ndx(ndx), word(wordIn) {
}

#endif //GIFORTH_FORTHEXECUTIONFRAME_H
