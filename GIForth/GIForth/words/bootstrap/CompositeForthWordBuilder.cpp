//
// Created by Dad on 9/28/19.
//

#include <words/PrimitiveForthWords.h>
#include "CompositeForthWordBuilder.h"

CompositeForthWordBuilder::CompositeForthWordBuilder(const std::string& name)
: word(name), ifStack()
{
}

CompositeForthWordBuilder& CompositeForthWordBuilder::operator+=(const ForthCell& cell) {
	word.appendCell(cell);
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::append(const ForthCell& cell) {
	word.appendCell(cell);
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileConstant(const ForthCell& cell) {
	word.appendCell(&PrimitiveForthWords::PUSH_NEXT_CELL);
	word.appendCell(cell);
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileIf() {
	word.appendCell(&PrimitiveForthWords::JUMP_IF_FALSE);
	ifStack.push(word.appendCell(static_cast<ForthCell::INT_TYPE>(0)));
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileElse() {
	word.appendCell(&PrimitiveForthWords::JUMP);
	int nextPatch = word.appendCell(static_cast<ForthCell::INT_TYPE>(0));
	int ifNdx = ifStack.top();
	ifStack.pop();
	word[ifNdx] = static_cast<ForthCell::INT_TYPE>(word.nextAppendNdx());
	ifStack.push(nextPatch);
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileEndIf() {
	int ifElseNdx = ifStack.top();
	ifStack.pop();
	word[ifElseNdx] = static_cast<ForthCell::INT_TYPE>(word.nextAppendNdx());
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileWhile() {
	ifStack.push(word.nextAppendNdx());
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileDo() {
	word.appendCell(&PrimitiveForthWords::JUMP_IF_FALSE);
	ifStack.push(word.appendCell(static_cast<ForthCell::INT_TYPE>(0)));
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileEndWhile() {
    int doNdx = ifStack.top();
    ifStack.pop();
    int whileNdx = ifStack.top();
    ifStack.pop();

    word.appendCell(&PrimitiveForthWords::JUMP);
    word.appendCell(static_cast<ForthCell::INT_TYPE>(whileNdx));
    word[doNdx] = static_cast<ForthCell::INT_TYPE>(word.nextAppendNdx());
    return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileRepeat() {
    ifStack.push(word.nextAppendNdx());
    return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileForever() {
    word.appendCell(&PrimitiveForthWords::JUMP);
    word.appendCell(static_cast<ForthCell::INT_TYPE>(ifStack.top()));
    ifStack.pop();
    return *this;
}

CompositeForthWord CompositeForthWordBuilder::build() {
    append(&PrimitiveForthWords::RETURN);
	return word;
}
