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

class CompositeForthWord : public ForthWord {
public:
	CompositeForthWord(const std::string &name, const std::vector<ForthCell>& cells);
    virtual ~CompositeForthWord() = default;

    void execute(ForthThread& thread) const override;

    int size() const;
    const ForthCell& operator[](int ndx) const;

    std::vector<std::string> getDisassembly() const;

protected:
	friend ForthThread;
	CompositeForthWord(const std::string &name, const std::shared_ptr<const std::vector<ForthCell>>& cells);
    void trace(const ForthThread& thread, ForthWord* word) const override;
	std::string getDisassemblyName() const override;
    std::string getDisassemblyDetail(const ForthThread& thread) const override;
    int getDisassemblyParamCount() const override;

    std::shared_ptr<const std::vector<ForthCell>> body;
    std::string name;
};

inline int CompositeForthWord::size() const {
    return body->size();
}

inline const ForthCell& CompositeForthWord::operator[](int ndx) const {
    return (*body)[ndx];
}

#endif //GIFORTH_COMPOSITEFORTHWORD_H
