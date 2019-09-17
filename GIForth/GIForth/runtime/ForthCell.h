//
// Created by Dad on 9/16/19.
//

#ifndef GIFORTH_FORTHCELL_H
#define GIFORTH_FORTHCELL_H

class ForthWord;

typedef union ForthCell {
    ForthCell() = default;
    ~ForthCell() = default;
    ForthCell(ForthWord* wordIn) : word(wordIn) {}
    explicit ForthCell(void* ptrIn) : pointer(ptrIn) {}
    explicit ForthCell(int intIn) : integer(intIn) {}
    explicit ForthCell(char charIn) : character(charIn) {}

    ForthWord* word;
    void* pointer;
    int integer;
    char character;
} ForthCell;

#endif //GIFORTH_FORTHCELL_H
