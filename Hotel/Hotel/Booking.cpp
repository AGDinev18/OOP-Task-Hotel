#include "Booking.h"

Booking::Booking(int roomNumber, const Date& f, const Date& t, const std::string& n, int g, bool available)
	: roomNumber(roomNumber), from(f), to(t), message(n), guests(g), available(available) {}

bool Booking::overlaps(const Date& start, const Date& end) const { return (to > start && from < end); }
bool Booking::isAvailable() const { return available; }
unsigned short int Booking::getRoomNumber() const { return roomNumber; }
unsigned short int Booking::getGuests() const { return guests; }
unsigned short int Booking::getDuration() const { return from.daysUntil(to); }
const Date& Booking::getStart() const { return from; } 
const Date& Booking::getEnd() const { return to; }
void Booking::setStart(const Date& f) { from = f; }
void Booking::setEnd(const Date& t) { to = t; }
void Booking::setRoomNumber(unsigned short int roomNumber) { this->roomNumber = roomNumber; }
const std::string& Booking::getMessage() const { return message; }