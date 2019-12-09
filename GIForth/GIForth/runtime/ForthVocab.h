//
// Created by stuff on 10/8/2019.
//

#ifndef GIFORTH_FORTHVOCAB_H
#define GIFORTH_FORTHVOCAB_H

#include <map>

class ForthWord;

class ForthVocab {
public:
	explicit ForthVocab(ForthVocab* next);
	ForthVocab(const ForthVocab& other) = default;
	virtual ~ForthVocab() = default;
	const ForthWord* findWord(const char* strAddr);
	const ForthWord* findWord(const std::string& str);

	void add(ForthWord* word);
	void add(const std::string& name, ForthWord* word);
	const ForthWord*& operator[](const std::string& name);

	// str* vocab* -- word true| false

private:
	const ForthWord* findWordWithLower(const std::string& str);

	ForthVocab* next;
	std::map<std::string, const ForthWord*> words;
};


#endif //GIFORTH_FORTHVOCAB_H
