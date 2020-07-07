#include "chrono.h"

namespace Chrono {

	// member function definitions

	Date::Date(int yy, Month mm, int dd)
		: y{ yy }, m{ mm }, d{ dd }
	{
		if (!is_date(yy, mm, dd)) throw Invalid{};
	}

	const Date& default_date()
	{
		static Date dd{ 2001, Month::jan, 1 };
		return dd;
	}

	Date::Date()
		: y{ default_date().year() },
		m{ default_date().month() },
		d{ default_date().day() }
	{}

	void Date::add_day(int n)
	{
		int days_in_month{ 31 };

		switch (m) {

		case Month::feb:
		case Month::apr:
		case Month::jun:
		case Month::sep:
		case Month::nov:
			days_in_month = 30;
			break;
		}

		d = d + n;

		if (d > days_in_month)
		{
			d = d - days_in_month;
			add_month(1);
		}
	}

	void Date::add_month(int n)
	{
		if (m == Month::dec)
		{
			m = Month::jan;
			++y;
		}
		else
			m = static_cast<Month>(static_cast<int>(m) + 1);
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n)) {
			m = Month::mar;
			d = 1;
		}
		y += n;
	}

	// helper functions:

	bool is_date(int y, Month m, int d)
	{
		// assume that y is valid

		if (d <= 0) return false;

		if (m < Month::jan || Month::dec < m) return false;

		int days_in_month{ 31 };

		switch (m) {

		case Month::feb:
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;

		case Month::apr:
		case Month::jun:
		case Month::sep:
		case Month::nov:
			days_in_month = 30;
			break;
		}

		if (days_in_month < d) return false;

		return true;
	}

	bool leapyear(int y)
	{
		// exc 10 ...
		return 0;
	}

	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	std::ostream& operator<<(std::ostream& os, const Month m)
	{
		return os << static_cast<int>(m);
	}

	std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
	}

	std::istream& operator>>(std::istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;

		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;

		if (!is) return is;

		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')
		{
			is.clear(std::ios_base::failbit);
			return is;
		}

		dd = Date(y, static_cast<Month>(m), d);

		return is;
	}

	enum class Day {
		sunday, monday, tuesday, wednesday, thursday, friday, saturday
	};

	/*
	Day day_of_week(const Date& d)
	{
		// ...
	}

	Date next_Sunday(const Date& d)
	{
		// ...
	}

	Date next_weekday(const Date& d)
	{
		// ...
	}
	*/

}	// Chrono