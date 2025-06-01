#include "Date.h"
#include <stdexcept>

bool Date::isLeapYear(const unsigned short int& y) const
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(const unsigned short int& m, const unsigned short int& y) const
{
	switch (m)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return isLeapYear(y) ? 29 : 28;
	default:
		return 0;
	}
}

bool Date::isValid(const unsigned short int& y, const unsigned short int& m, const unsigned short int& d) const
{
	if (y < 1900 || m < 1 || m > 12 || d < 1 || d>31)
		return false;
	return d >= 1 && d <= daysInMonth(m, y);
}

Date::Date() : year(0), month(0), day(0) {}

Date::Date(const unsigned short int& y, const unsigned short int& m, const unsigned short int& d)
{
	if (isValid(y, m, d))
	{
		year = y;
		month = m;
		day = d;
	}
	else
	{
		throw std::invalid_argument("Such date does not exist!");
	}
}

Date::Date(const std::string& dateStr)
{
	if (dateStr.length() != 10 || dateStr[4] != '-' || dateStr[7] != '-')
	{
		throw std::invalid_argument("Invalid date format (expected YYYY-MM-DD)");
	}
	try
	{
		year = static_cast<unsigned short int>(std::stoi(dateStr.substr(0, 4)));
		month = static_cast<unsigned short int>(std::stoi(dateStr.substr(5, 2)));
		day = static_cast<unsigned short int>(std::stoi(dateStr.substr(8, 2)));
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Invalid number for year/month/day");
	}

	if (!isValid(year, month, day))
	{
		throw std::invalid_argument("Such date does not exist!");
	}
}

Date& Date::operator=(const std::string& dateStr)
{
	if (dateStr.length() != 10 || dateStr[4] != '-' || dateStr[7] != '-')
	{
		throw std::invalid_argument("Invalid date format (expected YYYY-MM-DD)");
	}
	try
	{
		year = static_cast<unsigned short int>(std::stoi(dateStr.substr(0, 4)));
		month = static_cast<unsigned short int>(std::stoi(dateStr.substr(5, 2)));
		day = static_cast<unsigned short int>(std::stoi(dateStr.substr(8, 2)));
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Invalid number for year/month/day");
	}

	if (!isValid(year, month, day))
	{
		throw std::invalid_argument("Such date does not exist!");
	}

	return *this;
}

std::string Date::toString() const
{
	std::string result;

	std::string y = std::to_string(year);
	while (y.length() < 4) y = "0" + y;
	result += y + "-";

	std::string m = std::to_string(month);
	if (m.length() < 2) m = "0" + m;
	result += m + "-";

	std::string d = std::to_string(day);
	if (d.length() < 2) d = "0" + d;
	result += d;

	return result;
}

void Date::print() const
{
	std::cout << toString() << std::endl;
}

void Date::setDate(const unsigned short int& y, const unsigned short int& m, const unsigned short int& d)
{
	if (isValid(y, m, d))
	{
		year = y;
		month = m;
		day = d;
	}
	else
	{
		throw std::invalid_argument("Such date does not exist!");
	}
}

unsigned short int Date::getYear() const { return year; }
unsigned short int Date::getMonth() const { return month; }
unsigned short int Date::getDay() const { return day; }

bool Date::operator<(const Date& other) const
{
	if (year != other.year) return year < other.year;
	if (month != other.month) return month < other.month;
	return day < other.day;
}
bool Date::operator==(const Date& other) const
{
	return year == other.year && month == other.month && day == other.day;
}

bool Date::operator!=(const Date& other) const
{
	return !(*this == other);
}

bool Date::operator<=(const Date& other) const
{
	return *this < other || *this == other;
}

bool Date::operator>(const Date& other) const
{
	return !(*this <= other);
}

bool Date::operator>=(const Date& other) const
{
	return !(*this < other);
}