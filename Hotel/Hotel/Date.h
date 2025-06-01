#pragma once
#include <string>
#include <iostream>

class Date
{
private:
	int year;
	int month;
	int day;

	bool isLeapYear(const unsigned short int& y) const;
	int daysInMonth(const unsigned short int& m, const unsigned short int& y) const;
	bool isValid(const unsigned short int& y, const unsigned short int& m, const unsigned short int& d) const;

public:
	Date();
	Date(const unsigned short int& y,const unsigned short int& m, const unsigned short int& d);
	Date(const std::string& dateStr);
	Date& operator=(const std::string& dateStr);
	std::string toString() const;
	void print() const;
	void setDate(const unsigned short int& y, const unsigned short int& m, const unsigned short int& d);
	unsigned short int getYear() const;
	unsigned short int getMonth() const;
	unsigned short int getDay() const;
	bool operator<(const Date& other) const;

	bool operator==(const Date& other) const;

	bool operator!=(const Date& other) const;

	bool operator<=(const Date& other) const;

	bool operator>(const Date& other) const;

	bool operator>=(const Date& other) const;
};