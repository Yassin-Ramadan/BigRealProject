#include "BigReal.h"

bool BigReal::isValid(std::string input) {
	bool isPoint = 0;
	int i{ 0 };
	if (input[i] == '-' || input[i] == '+')
		i++;
	for (; i < input.size(); i++) {
		if (!(input[i] >= '0' && input[i] <= '9')) {
			if (input[i] == '.' && !isPoint)
				isPoint = 1;
			else
				return false;
		}
	}
	return true;
}

BigReal::BigReal() {
	integer = fraction = "0", pointIndex = 1, sign = '+';
}

BigReal::BigReal(std::string input) {
	if (!isValid(input)) {
		std::cout << "Invalid Number\n";
		integer = fraction = "0", pointIndex = 1, sign = '+';
		return;
	}
	int i{ 0 };
	if (input[i] == '-' || input[i] == '+')
		sign = input[i++];
	else
		sign = '+'; //000009.18000
	for (bool reverse = 0, isZero = 0; i < input.size(); i++) {
		if (input[i] == '.') {
			reverse = 1;
			continue;
		}
		if (reverse)
			fraction.push_back(input[i]);
		else {
			if (input[i] != '0')
				isZero = 1;
			if (isZero)
				integer.push_back(input[i]);
		}
	}
	if (integer == "")
		integer.push_back('0');
	pointIndex = integer.size();
	for (i = fraction.size() - 1; i; i--) {
		if (fraction[i] != '0')
			break;
	}
	fraction = fraction.substr(0, i + 1);
	if (fraction == "")
		fraction.push_back('0');
	if (fraction == integer && integer == "0")
		sign = '+';
}

std::ostream& operator << (std::ostream& out, BigReal& b) {
	if (b.sign != '+')
		out << b.sign;
	out << b.integer << '.' << b.fraction;
	return out;
}

// '-' > '+' ---> 45 > 43
// 1 --> integer > b.integer, -1 --> integer < b.integer, 0 --> integer == b.integer

int BigReal::isGreaterOrSmaller(std::string& a, std::string& b){
	if (a.size() > b.size())
		return 1;
	else if (a.size() == b.size()) {
		if (a > b)
			return 1;
		else if (a == b)
			return 0;
		else
			return -1;
	}
	else
		return -1;
}

bool BigReal::operator <(BigReal& b) {
	if(operator ==(b))
		return false;
	if (sign > b.sign)
		return true;
	else if (sign < b.sign)
		return false;
	else {
		if (sign == '+') {
			int state = isGreaterOrSmaller(integer, b.integer);
			if (state == 1)
				return false;
			else if (state == -1)
				return true;
			else {
				state = isGreaterOrSmaller(fraction, b.fraction); // 1, -1 only!
				if (state == 1)
					return false;
				else
					return true;
			}
		}
		else{
			int state = isGreaterOrSmaller(integer, b.integer);
			if (state == 1)
				return true;
			else if (state == -1)
				return false;
			else {
				state = isGreaterOrSmaller(fraction, b.fraction); // 1, -1 only!
				if (state == 1)
					return true;
				else
					return false;
			}
		}
	}
}

bool BigReal::operator >(BigReal& b) {
	return (operator !=(b) && !operator <(b));
}

bool BigReal::operator <=(BigReal& b) { 
	return (operator ==(b) || operator <(b));
}

bool BigReal::operator >=(BigReal& b) {
	return (operator ==(b) || operator >(b)); 
}

bool BigReal::operator ==(BigReal& b) {
	if (sign == b.sign && integer == b.integer && fraction == b.fraction && pointIndex == b.pointIndex) 
		return true;
	return false;
}

bool BigReal::operator !=(BigReal& b) {	
	return !(operator ==(b));
}