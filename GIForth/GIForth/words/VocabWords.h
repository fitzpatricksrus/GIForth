//
// Created by stuff on 10/12/2019.
//

#ifndef GIFORTH_VOCABWORDS_H
#define GIFORTH_VOCABWORDS_H

#include "runtime/BasicForthVocab.h"
class ForthWord;

class VocabWords : public BasicForthVocab {
public:
	explicit VocabWords(ForthVocab* next);
	VocabWords(const VocabWords& other) = default;
	~VocabWords() override = default;

	static ForthWord& SEARCH_VOCAB;			// char* vocab -- ( word true | char* false )
	static ForthWord& CURRENT_VOCAB;		// -- vocab
	static ForthWord& ADD_WORD_TO_VOCAB;	// word vocab --
};


#endif //GIFORTH_VOCABWORDS_H
