#pragma once
#include <vector>
#include "Room.h"
#include "Booking.h"

class Hotel
{
private:
	std::vector<Room> rooms;
	std::vector<Booking> bookings;

	bool checkIfRoomExists(unsigned short int roomNumber); // Checks if the room with the given roomNumber already exists
	bool checkIfRoomIsTaken(unsigned short int roomNumber,const Date& from,const Date& to); // Checks if the room is taken in a given period Date from to Date to
	void insertRoomSorted(const Room& room); // Sorts the new room into the vector of rooms
	void insertBookingSorted(const Booking& booking); // Sorts the new booking into the vector of bookings
public:
	~Hotel(); // Destructor which clears rooms and bookings
	void addRoom(unsigned short int roomNumber, unsigned short int beds); // Adds a room
	void checkIn(unsigned short int roomNumber, const Date& from, const Date& to, const std::string& note, unsigned short int guests = 0); // Used to create a booking
	void availability(const Date& date) const; // Prints a list of the free rooms in the given date
	void checkOut(unsigned short int roomNumber); // Checks if there is an active booking with the given roomNumber and if there is it sets the ending date of the booking to today
	void report(const Date& from, const Date& to) const; // Prints a list of the used rooms during this period and how many days was each room used
	void find(unsigned short int beds, const Date& from, const Date& to) const; // Prints the options of free rooms with minimun given beds for a period from to to
	void findSpecial(unsigned short int beds, const Date& from, const Date& to) const; // Suggests switching rooms of maximum 2 bookings in order to free a room for a special guest
	void unavailable(unsigned short int roomNumber, const Date& from, const Date& to, const std::string& note); // Makes a room unavailable to use for a period of time
	void openFile(const std::string& fileName); // Loads the data of a given file into the memory or creates a file if the fileName is not existing
	void saveFile(const std::string& fileName) const; // Saves the memory into file with the given fileName
	void changeRoom(const unsigned short int roomNumber, const Date& from, const Date& to, const unsigned short int newRoomNumber); // Sets roomNumber = newRoomNumber for the booking with roomNumber from a period of Date from to Date to 
};