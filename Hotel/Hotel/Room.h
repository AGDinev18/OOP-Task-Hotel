#pragma once
#include "Date.h"
class Room
{
private:
	unsigned short int roomNumber;
	unsigned short int beds;

public:
    Room(unsigned short int roomNumber, unsigned short int beds);
    unsigned short int getNumber() const;
    unsigned short int getBeds() const;
    void setNumber(unsigned short int number);
    void setBeds(unsigned short int beds);
};