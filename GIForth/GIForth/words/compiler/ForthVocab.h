//
// Created by stuff on 10/8/2019.
//

#ifndef GIFORTH_FORTHVOCAB_H
#define GIFORTH_FORTHVOCAB_H

class ForthWord;

class ForthVocab {
public:
	ForthVocab(ForthVocab* next);
	ForthVocab(const ForthVocab& other) = default;
	virtual ~ForthVocab() = default;
	const ForthWord* findWord(const char* strAddr);

	// str* vocab* -- word true| false

protected:
	virtual const ForthWord* doFindWord(const char* strAddr) = 0;

private:
	ForthVocab* next;
};


#endif //GIFORTH_FORTHVOCAB_H
