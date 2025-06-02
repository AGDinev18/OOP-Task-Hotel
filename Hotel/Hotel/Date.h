#pragma once
#include <string>
#include <iostream>

class Date
{
private:
	unsigned short int year;
	unsigned short int month;
	unsigned short int day;

	bool isLeapYear(unsigned short int y) const;
	unsigned short int daysInMonth(unsigned short int m, unsigned short int y) const;
	bool isValid(unsigned short int y, unsigned short int m, unsigned short int d) const;

public:
	Date(unsigned short int y,unsigned short int m, unsigned short int d);
	Date(const std::string& dateStr);
	Date& operator=(const std::string& dateStr);
	std::string toString() const;
	void print() const;
	void setDate(unsigned short int y, unsigned short int m, unsigned short int d);
	unsigned short int getYear() const;
	unsigned short int getMonth() const;
	unsigned short int getDay() const;
	bool operator<(const Date& other) const;
	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	bool operator<=(const Date& other) const;
	bool operator>(const Date& other) const;
	bool operator>=(const Date& other) const;
	static Date today();
	int daysSinceMarchFirst() const;
	unsigned short int daysUntil(const Date& other) const;
};