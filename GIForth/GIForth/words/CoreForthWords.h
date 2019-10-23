//
// Created by Dad on 9/27/19.
//

#ifndef GIFORTH_COREFORTHWORDS_H
#define GIFORTH_COREFORTHWORDS_H


#include "compiler/BasicForthVocab.h"
#include "runtime/CompositeForthWord.h"

class CoreForthWords : public BasicForthVocab {
public:
	CoreForthWords(ForthVocab* next);
	CoreForthWords(const CoreForthWords& other) = default;
	~CoreForthWords() = default;

    static CompositeForthWord STRLEN;               // char* -- len
    static CompositeForthWord STRCPY;               // src* dest* --
    static CompositeForthWord STRREVERSE;           // src*

	static CompositeForthWord PARSE_DIGIT;          // char -- [ value | -1 ]
	static CompositeForthWord PARSE_NUMBER;         // stringAddr -- [ value true | stringAddr false ]
	static CompositeForthWord NUMBER_TO_CHARACERS;  // value char* --
};


#endif //GIFORTH_COREFORTHWORDS_H
