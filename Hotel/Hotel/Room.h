#pragma once
#include "Date.h"
class Room
{
private:
	unsigned short int roomNumber;
	unsigned short int beds;

public:
    Room(unsigned short int roomNumber, unsigned short int beds); // Constructor to create an object
    unsigned short int getNumber() const; // Getter for the roomNumber
    unsigned short int getBeds() const; // Getter for the number of beds
    void setNumber(unsigned short int number); // Sets the roomNumber to other number
    void setBeds(unsigned short int beds); // Sets the number of beds to other number of beds
};