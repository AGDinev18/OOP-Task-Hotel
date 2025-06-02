#include "Room.h"

Room::Room(unsigned short int roomNumber, unsigned short int beds) : roomNumber(roomNumber), beds(beds) {}

unsigned short int Room::getNumber() const { return roomNumber; }

unsigned short int Room::getBeds() const { return beds; }

void Room::setNumber(unsigned short int roomNumber) { this->roomNumber = roomNumber; }

void Room::setBeds(unsigned short int beds) { this->beds = beds; }