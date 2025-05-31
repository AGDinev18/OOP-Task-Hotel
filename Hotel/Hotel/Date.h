#pragma once
#include <string>
#include <iostream>

class Date
{
private:
	int year;
	int month;
	int day;

	bool isLeapYear(const int y) const;
	int daysInMonth(const int m, const int y) const;
	bool isValid(const int y, const int m, const int d) const;

public:
	Date();
	Date(int y, int m, int d);
	Date(const std::string& dateStr);
	Date& operator=(const std::string& dateStr);
	std::string toString() const;
	void print() const;
	void setDate(int y, int m, int d);
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
};