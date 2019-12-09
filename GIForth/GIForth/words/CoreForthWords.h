//
// Created by Dad on 9/27/19.
//

#ifndef GIFORTH_COREFORTHWORDS_H
#define GIFORTH_COREFORTHWORDS_H


#include "runtime/ForthVocab.h"
#include "runtime/CompositeForthWord.h"

class CoreForthWords : public ForthVocab {
public:
	explicit CoreForthWords(ForthVocab* next);
	CoreForthWords(const CoreForthWords& other) = default;
	~CoreForthWords() override = default;

	static ForthWord& CURRENT_THREAD();

    static ForthWord& STRLEN();               // char* -- len
    static ForthWord& STRCPY();               // src* dest* --
    static ForthWord& STRREVERSE();           // src*

	static ForthWord& PARSE_DIGIT();          // char -- [ value | -1 ]
	static ForthWord& PARSE_NUMBER();         // stringAddr -- [ value true | stringAddr false ]
	static ForthWord& NUMBER_TO_CHARACERS();  // value char* --
};


#endif //GIFORTH_COREFORTHWORDS_H
