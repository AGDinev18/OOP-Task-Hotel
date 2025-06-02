#pragma once
#include <vector>
#include "Room.h"
#include "Booking.h"

class Hotel
{
private:
	std::vector<Room> rooms;
	std::vector<Booking> bookings;
	std::string currentFileName;

	bool checkIfRoomExists(unsigned short int roomNumber);
	bool checkIfRoomIsTaken(unsigned short int roomNumber,const Date& from,const Date& to);
	void insertBookingSorted(const Booking& booking);

public:
	void addRoom(unsigned short int roomNumber, unsigned short int beds);
	void checkIn(unsigned short int roomNumber, const Date& from, const Date& to, const std::string& note, unsigned short int guests = 0);
	void availability(const Date& date) const;
	void checkOut(unsigned short int roomNumber);
	void report(const Date& from, const Date& to) const;
	void find(unsigned short int beds, const Date& from, const Date& to) const;
	void findSpecial(unsigned short int beds, const Date& from, const Date& to) const;
	void unavailable(unsigned short int roomNumber, const Date& from, const Date& to, const std::string& note);
	void openFile(const std::string& fileName);
	void saveFile(const std::string& fileName) const;
	void closeFile();
};