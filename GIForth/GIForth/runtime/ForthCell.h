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
    ~ForthCell() = default;
    ForthCell(CELL_TYPE wordIn) : word(wordIn) {}
    ForthCell(INT_TYPE intIn) : integer(intIn) {}
    ForthCell(PTR_TYPE ptrIn) : pointer(ptrIn) {}
    ForthCell(CHAR_TYPE charIn) : character(charIn) {}
    ForthCell(BOOL_TYPE boolIn) : boolean(boolIn) {}

    CELL_TYPE word;
    PTR_TYPE pointer;
    INT_TYPE integer;
    CHAR_TYPE character;
    BOOL_TYPE boolean;
} ForthCell;

#endif //GIFORTH_FORTHCELL_H
