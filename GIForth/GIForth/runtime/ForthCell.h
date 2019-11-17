//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHCELL_H
#define GIFORTH_FORTHCELL_H

class ForthWord;

typedef union ForthCell {
    typedef bool BOOL_TYPE;
    typedef char CHAR_TYPE;
    typedef long INT_TYPE;
    // typedef float FLOAT_TYPE;
    typedef void* PTR_TYPE;
    typedef ForthWord* CELL_TYPE;
	
	ForthCell() = default;
	ForthCell(const ForthCell& other) = default;
    ~ForthCell() = default;
	ForthCell& operator=(const ForthCell& other) = default;
	
	ForthCell(const CELL_TYPE& wordIn) : word(wordIn) {}
    ForthCell(const INT_TYPE& intIn) : integer(intIn) {}
    ForthCell(const PTR_TYPE& ptrIn) : pointer(ptrIn) {}

    CELL_TYPE word;
    PTR_TYPE pointer;
    INT_TYPE integer;
} ForthCell;

#endif //GIFORTH_FORTHCELL_H
