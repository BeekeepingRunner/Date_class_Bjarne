#include <iostream>
#include <vector>
#include <algorithm>

#include "chrono.h"

int main()
{
	Chrono::Date today{ 1978, Chrono::Month::dec, 31 };
	std::cout << today << '\n';

	Chrono::Date tomorrow{ today };
	tomorrow.add_day(1);
	std::cout << tomorrow << '\n';

	return 0;
}