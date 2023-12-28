#pragma once
#include <iostream>

class BigReal {
	char sign;
	std::string integer;
	std::string fraction;
	int pointIndex;
	bool isValid(std::string);
	int isGreaterOrSmaller(std::string&, std::string&);
public:
	BigReal();
	BigReal(std::string);
	friend std::ostream& operator << (std::ostream& , BigReal& );
	BigReal operator +(BigReal& );
	BigReal operator -(BigReal&);
	bool operator <(BigReal&);
	bool operator >(BigReal&);
	bool operator <=(BigReal&);
	bool operator >=(BigReal&);
	bool operator ==(BigReal&);
	bool operator !=(BigReal&);


};