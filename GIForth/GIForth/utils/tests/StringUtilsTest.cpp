//
// Created by Dad on 10/22/19.
//

#include "StringUtilsTest.h"
#include "utils/testing/catch.hpp"
#include "utils/StringUtils.h"

TEST_CASE( "Testin utils/StringUtils", "[StringUtilsTest]" ) {
	std::string data = "UPPER CASE";
	
	StringUtils::toLower(data);
	CHECK(  data == "upper case");
	
	StringUtils::tabTo(data, 15);
	CHECK(data.size() == 14);
	
	StringUtils::rightTabTo(data, "foo", 20);
	CHECK(data.size() == 20);
	CHECK(data == "upper case       foo");
}
