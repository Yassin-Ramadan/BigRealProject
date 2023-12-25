#pragma once
#include <iostream>

class BigReal {
	char sign;
	std::string integer;
	std::string fraction;
	int pointIndex;
	bool isValid(std::string);
public:
	BigReal();
	BigReal(std::string);
	friend std::ostream& operator << (std::ostream& out, BigReal& b);


};