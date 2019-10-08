//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_COMPOSITEFORTHWORD_H
#define GIFORTH_COMPOSITEFORTHWORD_H

#include <vector>
#include <string>
#include "ForthWord.h"
#include "ForthCell.h"

class ForthThread;
class CompositeForthWordProxy;

class CompositeForthWord : public ForthWord {
public:
	CompositeForthWord(const std::string& name);
	CompositeForthWord(const CompositeForthWord& other);
    virtual ~CompositeForthWord() = default;
	CompositeForthWord& operator=(const CompositeForthWord& other) = default;
    
    void execute(ForthThread& thread) override;

    int size() const;
    const ForthCell& operator[](int ndx) const;
    ForthCell& operator[](int ndx);
    int appendCell(const ForthCell& cell);
    int nextAppendNdx() const;

    std::vector<std::string> getDisassembly() const;

protected:
    void trace(const ForthThread& thread, ForthWord* word) const;
	std::string getDisassemblyName() const override;
    std::string getDisassemblyDetail(const ForthThread& thread) const override;
    int getDisassemblyParamCount() const override;

private:
    friend CompositeForthWordProxy;
    std::vector<ForthCell> body;
    std::string name;
};

inline CompositeForthWord::CompositeForthWord(const std::string& nameIn)
		: body(), name(nameIn)
{
}

inline CompositeForthWord::CompositeForthWord(const CompositeForthWord& other)
		: body(other.body), name(other.name)
{
}

inline int CompositeForthWord::size() const {
    return body.size();
}

inline const ForthCell& CompositeForthWord::operator[](int ndx) const {
    return body[ndx];
}

inline ForthCell& CompositeForthWord::operator[](int ndx) {
    return body[ndx];
}

inline int CompositeForthWord::appendCell(const ForthCell& cell) {
	int result = body.size();
    body.push_back(cell);
    return result;
}

inline int CompositeForthWord::nextAppendNdx() const {
	return body.size();
}

#endif //GIFORTH_COMPOSITEFORTHWORD_H
