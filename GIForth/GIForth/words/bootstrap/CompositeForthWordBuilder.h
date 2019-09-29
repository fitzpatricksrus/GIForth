//
// Created by Dad on 9/28/19.
//

#ifndef GIFORTH_COMPOSITEFORTHWORDBUILDER_H
#define GIFORTH_COMPOSITEFORTHWORDBUILDER_H

#include <stack>
#include "runtime/CompositeForthWord.h"

class CompositeForthWordBuilder {
public:
	CompositeForthWordBuilder(const std::string& name);
	CompositeForthWordBuilder& operator+=(const ForthCell& cell);
	CompositeForthWordBuilder& append(const ForthCell& cell);
	CompositeForthWordBuilder& compileConstant(const ForthCell& cell);
	CompositeForthWordBuilder& compileIfLink();
	CompositeForthWordBuilder& compileElseLink();
	CompositeForthWordBuilder& compileEndIfLink();
	CompositeForthWordBuilder& compileWhileLink();
	CompositeForthWordBuilder& compileDoLink();
	CompositeForthWordBuilder& compileEndWhileLink();
	
	CompositeForthWord build();
	
private:
	CompositeForthWord word;
	std::stack<int> ifStack;
};

#endif //GIFORTH_COMPOSITEFORTHWORDBUILDER_H
