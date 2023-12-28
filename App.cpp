#include "BigReal.h"

int main() {
	BigReal x("5.5"), y("5.06");
	BigReal z;
	z = x + y;
	std::cout << z;
	return 0;
}