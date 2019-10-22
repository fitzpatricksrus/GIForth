//
// Created by Dad on 10/22/19.
//

#include "StringUtilsTest.h"
#include "utils/testing/catch.hpp"
#include "utils/StringUtils.h"

TEST_CASE( "Testin utils/StringUtils", "[StringUtils]" ) {
	std::string data = "UPPER CASE";
	
	StringUtils::toLower(data);
	REQUIRE(  data == "upper case");
	
	StringUtils::tabTo(data, 15);
	REQUIRE(data.size() == 14);
	
	StringUtils::rightTabTo(data, "foo", 20);
	REQUIRE(data.size() == 20);
	REQUIRE(data == "upper case       foo");
}
