//
// Created by stuff on 10/12/2019.
//

#ifndef GIFORTH_VOCABWORDS_H
#define GIFORTH_VOCABWORDS_H

#include "runtime/ForthVocab.h"
class ForthWord;

class VocabWords : public ForthVocab {
public:
	explicit VocabWords(ForthVocab* next);
	VocabWords(const VocabWords& other) = default;
	~VocabWords() override = default;

	static ForthWord& SEARCH_VOCAB;			// char* vocab -- ( word true | char* false )
	static ForthWord& ADD_WORD_TO_VOCAB;	// word vocab --

	static ForthWord& SOURCE_VOCAB;			// -- vocab
	static ForthWord& DEST_VOCAB;			// -- vocab
};


#endif //GIFORTH_VOCABWORDS_H
