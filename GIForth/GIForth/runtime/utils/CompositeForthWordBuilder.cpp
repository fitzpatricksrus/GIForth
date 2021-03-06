#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-use-emplace"
//
// Created by Dad on 9/28/19.
//

#include <runtime/PrimitiveForthWords.h>
#include "CompositeForthWordBuilder.h"

CompositeForthWordBuilder::CompositeForthWordBuilder(const std::string &nameIn)
		: name(nameIn), word(), ifStack()
{
}

CompositeForthWordBuilder& CompositeForthWordBuilder::operator+=(const ForthCell& cell) {
	word.push_back(cell);
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileCell(const ForthCell& cell) {
	word.push_back(cell);
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileConstant(const ForthCell& cell) {
	word.push_back(&PrimitiveForthWords::PUSH_NEXT_CELL());
	word.push_back(cell);
	return *this;
}

CompositeForthWordBuilder &CompositeForthWordBuilder::compileWord(const ForthCell::WORD_TYPE wordIn) {
	word.push_back(wordIn);
	return *this;
}

CompositeForthWordBuilder &CompositeForthWordBuilder::compileInt(const ForthCell::INT_TYPE intIn) {
	word.push_back(&PrimitiveForthWords::PUSH_NEXT_CELL());
	word.push_back(intIn);
	return *this;
}

CompositeForthWordBuilder &CompositeForthWordBuilder::compilePtr(const ForthCell::PTR_TYPE ptrIn) {
	word.push_back(&PrimitiveForthWords::PUSH_NEXT_CELL());
	word.push_back(ptrIn);
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileIf() {
	word.push_back(&PrimitiveForthWords::JUMP_IF_FALSE());
	ifStack.push(word.size());
	word.push_back(static_cast<ForthCell::INT_TYPE>(0));
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileElse() {
	word.push_back(&PrimitiveForthWords::JUMP());
	int nextPatch = word.size();
	word.push_back(static_cast<ForthCell::INT_TYPE>(0));
	int ifNdx = ifStack.top();
	ifStack.pop();
	word[ifNdx] = static_cast<ForthCell::INT_TYPE>(word.size());
	ifStack.push(nextPatch);
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileEndIf() {
	int ifElseNdx = ifStack.top();
	ifStack.pop();
	word[ifElseNdx] = static_cast<ForthCell::INT_TYPE>(word.size());
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileWhile() {
	ifStack.push(word.size());
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileDo() {
	word.push_back(&PrimitiveForthWords::JUMP_IF_FALSE());
	ifStack.push(word.size());
	word.push_back(static_cast<ForthCell::INT_TYPE>(0));
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileEndWhile() {
	int doNdx = ifStack.top();
	ifStack.pop();
	int whileNdx = ifStack.top();
	ifStack.pop();

	word.push_back(&PrimitiveForthWords::JUMP());
	word.push_back(static_cast<ForthCell::INT_TYPE>(whileNdx));
	word[doNdx] = static_cast<ForthCell::INT_TYPE>(word.size());
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileRepeat() {
	ifStack.push(word.size());
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileForever() {
	word.push_back(&PrimitiveForthWords::JUMP());
	word.push_back(static_cast<ForthCell::INT_TYPE>(ifStack.top()));
	ifStack.pop();
	return *this;
}

CompositeForthWordBuilder& CompositeForthWordBuilder::compileUntil() {
	word.push_back(&PrimitiveForthWords::JUMP_IF_FALSE());
	word.push_back(static_cast<ForthCell::INT_TYPE>(ifStack.top()));
	ifStack.pop();
	return *this;
}

CompositeForthWord CompositeForthWordBuilder::build() {
	compileCell(&PrimitiveForthWords::RETURN());
	return CompositeForthWord(name, word);
}
CompositeForthWordBuilder &CompositeForthWordBuilder::forwardMark() {
	ifStack.push(word.size());
	word.push_back(static_cast<ForthCell::INT_TYPE>(0));
	return *this;
}
CompositeForthWordBuilder &CompositeForthWordBuilder::forwardResolve() {
	int markNdx = ifStack.top();
	ifStack.pop();
	word[markNdx] = static_cast<ForthCell::INT_TYPE>(word.size());
	return *this;
}
CompositeForthWordBuilder &CompositeForthWordBuilder::forwardMarkResolve() {
	int nextPatch = word.size();
	word.push_back(static_cast<ForthCell::INT_TYPE>(0));
	int ifNdx = ifStack.top();
	ifStack.pop();
	word[ifNdx] = static_cast<ForthCell::INT_TYPE>(word.size());
	ifStack.push(nextPatch);
	return *this;
}
CompositeForthWordBuilder &CompositeForthWordBuilder::backwardMark() {
	ifStack.push(word.size());
	return *this;
}
CompositeForthWordBuilder &CompositeForthWordBuilder::backwardResolve() {
	int markNdx = ifStack.top();
	ifStack.pop();
	word.push_back(static_cast<ForthCell::INT_TYPE>(markNdx));
	return *this;
}

#pragma clang diagnostic pop