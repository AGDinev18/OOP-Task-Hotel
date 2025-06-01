#pragma once
#include <vector>
#include "Room.h"
#include "Booking.h"

class Hotel
{
private:
	std::vector<Room> rooms;
	std::vector<Booking> bookings;

public:
	void addRoom(const unsigned short int& number, const unsigned short int& beds);
	void checkIn(const unsigned short int& room, const Date& from, const Date& to, const std::string& note, unsigned short int guests = 0);
	void availability(const Date& date) const;
	void checkOut(const unsigned short int& room);
	void report(const Date& from, const Date& to) const;
	void find(const unsigned short int& beds, const Date& from, const Date& to) const;
	void findSpecial(const unsigned short int& beds, const Date& from, const Date& to) const;
	void unavailable(const unsigned short int& room, const Date& from, const Date& to, const std::string& note);
	void openFile(const std::string& fileName);
	void saveFile(const std::string& fileName) const;
};