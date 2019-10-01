//
// Created by Dad on 9/27/19.
//

#ifndef GIFORTH_COREFORTHWORDS_H
#define GIFORTH_COREFORTHWORDS_H


class CoreForthWords {
public:
    static CompositeForthWord STRLEN;               // char* -- len
    static CompositeForthWord STRCPY;               // src* dest* --
    static CompositeForthWord STRNCPY;               // src* dest* len --

	static CompositeForthWord PARSE_DIGIT;          // char -- [ value | -1 ]
	static CompositeForthWord PARSE_NUMBER;         // stringAddr -- [ value true | stringAddr false ]
	static CompositeForthWord NUMBER_TO_CHARACERS;  // value char* --
};


#endif //GIFORTH_COREFORTHWORDS_H
