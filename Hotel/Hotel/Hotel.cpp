#include "Hotel.h"
#include <iostream>
#include <fstream>
#include <algorithm>

bool Hotel::checkIfRoomExists(unsigned short int roomNumber)
{
	for (const auto& room : rooms)
	{
		if (room.getNumber() == roomNumber)
			return true;
	}
	return false;
}

bool Hotel::checkIfRoomIsTaken(unsigned short int roomNumber, const Date& from, const Date& to)
{
	for (const auto& booking : bookings)
	{
		if (booking.getEnd() <= from)
			break;
		if (booking.getRoomNumber() == roomNumber)
		{
			if (booking.overlaps(from, to))
				return true;
		}
	}
	return false;
}

void Hotel::insertBookingSorted(const Booking& booking) {
	auto it = bookings.begin();
	while (it != bookings.end() && it->getEnd() > booking.getEnd())
	{
		++it;
	}
	bookings.insert(it, booking);
}

void Hotel::addRoom(unsigned short int roomNumber, unsigned short int beds)
{
	if (checkIfRoomExists(roomNumber))
	{
		std::cout << "Room already exists!\n";
		return;
	}
	rooms.emplace_back(roomNumber, beds);
	std::cout << "Room added successfully!\n";
}

void Hotel::checkIn(unsigned short int roomNumber, const Date& from, const Date& to, const std::string& note, unsigned short int guests)
{
	if (!checkIfRoomExists(roomNumber))
	{
		std::cout << "Room does not exist!\n";
		return;
	}
	if (checkIfRoomIsTaken(roomNumber, from, to))
	{
		std::cout << "Room is already taken in that period!\n";
		return;
	}

	Booking booking(roomNumber, from, to, note, guests, true);
	insertBookingSorted(booking);
	std::cout << "Checked in successfully!\n";
}

void Hotel::availability(const Date& date) const
{
	for (const auto& room : rooms)
	{
		bool taken = false;

		for (const auto& b : bookings)
		{
			if (b.getEnd() <= date)
				break;
			if (b.getRoomNumber() == room.getNumber())
			{
				if (b.getStart() <= date && b.getEnd() > date) {
					taken = true;
					break;
				}
			}
		}
		if (!taken)
		{
			std::cout << "Room " << room.getNumber() << " is available!\n";
		}
	}
}

void Hotel::checkOut(unsigned short int roomNumber)
{
	Date today = Date::today();

	for (auto& booking : bookings)
	{
		if (booking.getEnd() <= today)
			break;
		if (booking.getRoomNumber() == roomNumber)
		{
			if (booking.getStart() <= today && booking.getEnd() > today)
			{
				booking.setEnd(today);
				std::cout << "Checked out successfully!\n";
				return;
			}
		}
	}
	std::cout << "No active booking found to check out!\n";
}

void Hotel::report(const Date& from, const Date& to) const {
	for (const auto& room : rooms) {
		unsigned short int usedDays = 0;
		for (const auto& b : bookings)
		{
			if (b.getEnd() < from) {
				break;
			}
			if (b.getRoomNumber() == room.getNumber())
			{
				if (b.getStart() < to)
				{
					Date start = std::max(b.getStart(), from);
					Date end = std::min(b.getEnd(), to);

					usedDays += start.daysUntil(end);
					if (b.getEnd() > to)
					{
						usedDays += 1;
					}
				}
				if (b.getStart() == to)
				{
					usedDays = 1;
				}
			}
		}
		if (usedDays > 0)
		{
			std::cout << "Room " << room.getNumber() << " used for " << usedDays << " days!\n";
		}
	}
}

void Hotel::find(unsigned short int beds, const Date& from, const Date& to) const
{
	std::vector<Room> suitableRooms;

	for (const auto& room : rooms)
	{
		if (room.getBeds() >= beds)
		{
			bool available = true;

			for (const auto& booking : bookings)
			{
				if (booking.getRoomNumber() == room.getNumber())
				{
					if (booking.overlaps(from, to))
					{
						available = false;
						break;
					}
				}
			}
			if (available)
			{
				suitableRooms.push_back(room);
			}
		}
	}

	// Insertion sort by number of beds (ascending)
	for (size_t i = 1; i < suitableRooms.size(); i++)
	{
		Room key = suitableRooms[i];
		int j = i - 1;

		while (j >= 0 && suitableRooms[j].getBeds() > key.getBeds())
		{
			suitableRooms[j + 1] = suitableRooms[j];
			--j;
		}
		suitableRooms[j + 1] = key;
	}

	if (suitableRooms.empty())
	{
		std::cout << "No available room found!\n";
	}
	else
	{
		for (const auto& room : suitableRooms)
		{
			std::cout << "Room " << room.getNumber() << " with " << room.getBeds() << " beds is available!\n";
		}
	}
}

void Hotel::findSpecial(unsigned short int beds, const Date& from, const Date& to) const
{

}

void Hotel::unavailable(unsigned short int roomNumber, const Date& from, const Date& to, const std::string& note)
{
	if (!checkIfRoomExists(roomNumber))
	{
		std::cout << "Room does not exist!\n";
		return;
	}

	Booking newBooking(roomNumber, from, to, note, 0, false);

	insertBookingSorted(newBooking);

	std::cout << "Room marked as unavailable!\n";
}

void Hotel::openFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::ofstream createFile(fileName);
		if (!createFile)
		{
			std::cout << "Could not create file!\n";
			return;
		}
		createFile.close();
		std::cout << "Successfully created " << fileName << "\n";
		rooms.clear();
		bookings.clear();
		return;
	}

	rooms.clear();
	bookings.clear();

	unsigned int roomCount = 0;
	file >> roomCount;
	for (unsigned int i = 0; i < roomCount; ++i)
	{
		unsigned short int roomNumber, beds;
		file >> roomNumber >> beds;
		rooms.emplace_back(roomNumber, beds);
	}

	unsigned int bookingCount = 0;
	file >> bookingCount;
	for (unsigned int i = 0; i < bookingCount; ++i)
	{
		unsigned short int roomNumber, guests;
		std::string fromStr, toStr, note;
		bool active;

		file >> roomNumber >> fromStr >> toStr >> guests >> active;
		std::getline(file, note);
		if (!note.empty() && note[0] == ' ') note.erase(0, 1);

		Date from(fromStr);
		Date to(toStr);
		bookings.emplace_back(roomNumber, from, to, note, guests, active);
	}

	file.close();
	std::cout << "Successfully opened " << currentFileName << "\n";
}

void Hotel::saveFile(const std::string& fileName) const
{
	std::string targetFile = fileName;

	if (targetFile.empty())
	{
		if (currentFileName.empty())
		{
			std::cout << "No file opened or specified to save!\n";
			return;
		}
		targetFile = currentFileName;
	}

	std::ofstream file(targetFile);
	if (!file.is_open())
	{
		std::cout << "Could not save to file " << targetFile << "\n";
		return;
	}

	file << rooms.size() << "\n";
	for (const auto& room : rooms)
	{
		file << room.getNumber() << " " << room.getBeds() << "\n";
	}

	file << bookings.size() << "\n";

	for (const auto& booking : bookings)
	{
		file << booking.getRoomNumber() << " "
			<< booking.getStart().toString() << " "
			<< booking.getEnd().toString() << " "
			<< booking.getGuests() << " "
			<< booking.isAvailable() << " "
			<< booking.getMessage() << "\n";
	}

	file.close();
	std::cout << "Successfully saved " << targetFile << "\n";
}

void Hotel::closeFile()
{
	rooms.clear();
	bookings.clear();
	currentFileName.clear();
	std::cout << "Data cleared and file closed.\n";
}
