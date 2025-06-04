#pragma once
#include "Room.h"
class Booking
{
private:
	unsigned short int roomNumber;
	Date from;
	Date to;
	std::string message;
	unsigned short int guests;
	bool available;

public:
    Booking(int roomNumber, const Date& from, const Date& to, const std::string& note, int guests = 0, bool available = 1); // Constructor needed to create the object
    bool overlaps(const Date& start, const Date& end) const; // Checks if the booking is in conflict with other period of time
    bool isAvailable() const; // Returns if the booking is under construction or available
    unsigned short int getRoomNumber() const; // Getter for roomNumber
    unsigned short int getGuests() const; // Getter for guests
    unsigned short int getDuration() const; // Returns how many days is the booking
    const Date& getStart() const; // Getter for the beginning date of the booking
    const Date& getEnd() const; // Getter for the ending date of the booking
    void setStart(const Date& from); // Setting other beginning date for the booking
    void setEnd(const Date& to); // Setting other ending date for the booking
    void setRoomNumber(unsigned short int roomNumber); // Setting other room to be the room of the booking
    const std::string& getMessage() const; // Getter for the note of the booking
};