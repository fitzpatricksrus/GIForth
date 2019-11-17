//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHEXECUTIONFRAME_H
#define GIFORTH_FORTHEXECUTIONFRAME_H

class CompositeForthWord;

class ForthExecutionFrame {
public:
	ForthExecutionFrame();
	ForthExecutionFrame(const CompositeForthWord *wordIn);
	ForthExecutionFrame(const CompositeForthWord *wordIn, int ndx);
	ForthExecutionFrame(const ForthExecutionFrame &other) = default;
	~ForthExecutionFrame() = default;
	ForthExecutionFrame &operator=(const ForthExecutionFrame &other);

	bool isDeadFrame() const;

	int ndx;
	const CompositeForthWord *word;
};

inline ForthExecutionFrame::ForthExecutionFrame()
		: ForthExecutionFrame(nullptr, 0) {
}

inline ForthExecutionFrame::ForthExecutionFrame(const CompositeForthWord *wordIn)
		: ForthExecutionFrame(wordIn, 0) {
}

inline ForthExecutionFrame::ForthExecutionFrame(const CompositeForthWord *wordIn, int ndx)
		: ndx(ndx), word(wordIn) {
}

inline ForthExecutionFrame &ForthExecutionFrame::operator=(const ForthExecutionFrame &other) {
	ndx = other.ndx;
	word = other.word;
	return *this;
}

inline bool ForthExecutionFrame::isDeadFrame() const {
	return word == nullptr;
}
#endif //GIFORTH_FORTHEXECUTIONFRAME_H
