#pragma once
#include <string>
#include <iostream>

class Date
{
private:
	unsigned short int year;
	unsigned short int month;
	unsigned short int day;

	bool isLeapYear(unsigned short int y) const; // Returns if the year is leap or not
	unsigned short int daysInMonth(unsigned short int m, unsigned short int y) const; // For a given month of a given year the function checks how many days this month has
	bool isValid(unsigned short int y, unsigned short int m, unsigned short int d) const; // Returns wether such date exists or not
	int daysSinceMarchFirst() const; // Needed to calculate the duration of bookings and return how many days have passed since March first of 0000 year

public:
	Date(unsigned short int y,unsigned short int m, unsigned short int d); // Constructor using integers
	Date(const std::string& dateStr); // Constructor using string format
	Date& operator=(const std::string& dateStr); // Redefines operator = for Date to work with a given string
	std::string toString() const; // Returns the date in string format
	void print() const; // Prints the date
	void setDate(unsigned short int y, unsigned short int m, unsigned short int d); // Sets the date to other date with the given year, month, day

	unsigned short int getYear() const; // Getter for the value of year
	unsigned short int getMonth() const; // Getter for the value of month
	unsigned short int getDay() const; // Getter for the value of day

	bool operator<(const Date& other) const; // Redefines the operator to work properly with other given Date
	bool operator==(const Date& other) const; // Redefines the operator to work properly with other given Date
	bool operator!=(const Date& other) const; // Redefines the operator to work properly with other given Date
	bool operator<=(const Date& other) const; // Redefines the operator to work properly with other given Date
	bool operator>(const Date& other) const; // Redefines the operator to work properly with other given Date
	bool operator>=(const Date& other) const; // Redefines the operator to work properly with other given Date

	static Date today(); // Returns today
	unsigned int daysUntil(const Date& other) const; // Calculates how many days are there between the two dates
};