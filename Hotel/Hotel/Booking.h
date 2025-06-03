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
    Booking(int roomNumber, const Date& from, const Date& to, const std::string& note, int guests = 0, bool available = 1);
    bool overlaps(const Date& start, const Date& end) const;
    bool isAvailable() const;
    unsigned short int getRoomNumber() const;
    unsigned short int getGuests() const;
    unsigned short int getDuration() const;
    const Date& getStart() const;
    const Date& getEnd() const;
    void setStart(const Date& from);
    void setEnd(const Date& to);
    void setRoomNumber(unsigned short int roomNumber);
    const std::string& getMessage() const;
};