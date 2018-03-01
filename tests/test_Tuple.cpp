#include "catch.hpp"
#include "src\model\Tuple.h"
#include <sstream>

unsigned int parseTupleTest () {
	Tuple tuple;
	std::string inputString("das Kleid : le v�tement");
	std::istringstream ss(inputString);
	ss >> tuple;

	if (tuple.getOriginal () != "das Kleid")
		return 1;
	if (tuple.getTranslated () != "le v�tement")
		return 2;
	return 0;
}

TEST_CASE ("Tuple parsing test", "[Tuple operator>>]") {
	REQUIRE (parseTupleTest () == 0);
}