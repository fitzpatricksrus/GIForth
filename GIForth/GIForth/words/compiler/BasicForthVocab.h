#ifndef GIFORTH_BASICFORTHVOCAB_H
#define GIFORTH_BASICFORTHVOCAB_H

#include "ForthVocab.h"
#include <string>
#include <map>

class BasicForthVocab : public ForthVocab {
public:
	BasicForthVocab(ForthVocab* next);
	BasicForthVocab(const BasicForthVocab& other) = default;
	~BasicForthVocab() override = default;

	void add(ForthWord* word);
	const ForthWord*& operator[](const std::string& name);

protected:
	virtual const ForthWord* doFindWord(const char* strAddr) override;

private:
	std::map<std::string, const ForthWord*> words;
};

#endif //GIFORTH_BASICFORTHVOCAB_H
