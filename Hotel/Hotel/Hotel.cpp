#include "Hotel.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

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

void Hotel::insertRoomSorted(const Room& room)
{
	auto it = rooms.begin();
	while (it != rooms.end() && it->getBeds() <= room.getBeds())
	{
		++it;
	}
	rooms.insert(it, room);
}

void Hotel::insertBookingSorted(const Booking& booking) {
	auto it = bookings.begin();
	while (it != bookings.end() && it->getEnd() > booking.getEnd())
	{
		++it;
	}
	bookings.insert(it, booking);
}

Hotel::~Hotel()
{
	rooms.clear();
	bookings.clear();
}

void Hotel::addRoom(unsigned short int roomNumber, unsigned short int beds)
{
	if (checkIfRoomExists(roomNumber))
	{
		std::cout << "Room already exists!\n";
		return;
	}
	Room room(roomNumber, beds);
	insertRoomSorted(room);
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
	for (const auto& room : rooms)
	{
		if (room.getNumber() == roomNumber)
		{
			if (guests > room.getBeds())
			{
				std::cout << "Not enough beds!\n";
				return;
			}
			else if (guests == 0)
			{
				guests = room.getBeds();
			}
		}
	}
	if (guests==0)
	{ 
		for (const auto& room : rooms)
		{
			if (room.getNumber() == roomNumber)
			{
				guests = room.getBeds();
				break;
			}
		}
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

void Hotel::report(const Date& from, const Date& to) const
{
	for (const auto& room : rooms)
	{
		unsigned short int usedDays = 0;
		for (const auto& b : bookings)
		{
			if (b.getEnd() < from)
			{
				break;
			}
			if (b.getRoomNumber() == room.getNumber() && b.isAvailable() != false)
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
				if (booking.getEnd() <= from)
				{
					break;
				}
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
	for (const auto& targetRoom : rooms)
	{
		if (targetRoom.getBeds() >= beds)
		{
			std::vector<const Booking*> conflicts;

			for (const auto& booking : bookings)
			{
				if (booking.getEnd() <= from)
				{
					break;
				}
				if (booking.getRoomNumber() == targetRoom.getNumber() && booking.isAvailable() != false)
				{
					if (booking.overlaps(from, to))
					{
						conflicts.push_back(&booking);
					}
				}
			}

			if (conflicts.size() != 0 && conflicts.size() <= 2)
			{

				std::vector<std::pair<const Booking*, const Room*>> relocations;
				bool canRelocate = true;

				for (const auto conflict : conflicts) {
					const Room* relocationTarget = nullptr;

					for (const auto& otherRoom : rooms) {
						if (otherRoom.getNumber() != targetRoom.getNumber())
						{
							if (otherRoom.getBeds() >= conflict->getGuests())
							{
								bool available = true;
								for (const auto& booking : bookings)
								{
									if (booking.getEnd() < from)
									{
										break;
									}
									if (booking.getRoomNumber() == otherRoom.getNumber() && booking.isAvailable()!=false)
									{
										if (booking.overlaps(conflict->getStart(), conflict->getEnd()))
										{
											available = false;
											break;
										}
									}
								}

								if (available)
								{
									relocationTarget = &otherRoom;
									break;
								}
							}
						}
					}

					if (!relocationTarget)
					{
						canRelocate = false;
						break;
					}

					relocations.emplace_back(conflict, relocationTarget);
				}

				if (canRelocate)
				{
					std::cout << "Special guest can be placed in Room " << targetRoom.getNumber() << " by relocating:\n";
					for (const auto& move : relocations)
					{
						std::cout << "- Booking from Room " << move.first->getRoomNumber()
							<< " (Guests: " << move.first->getGuests()
							<< ", " << move.first->getStart().toString()
							<< " to " << move.first->getEnd().toString() << ") "
							<< "-> move to Room " << move.second->getNumber() << "\n";
					}
					return;
				}
			}
		}
	}

	std::cout << "No solution found. Cannot relocate guests within constraints.\n";
}

void Hotel::unavailable(unsigned short int roomNumber, const Date& from, const Date& to, const std::string& note)
{
	if (!checkIfRoomExists(roomNumber))
	{
		std::cout << "Room does not exist!\n";
		return;
	}
	if (checkIfRoomIsTaken(roomNumber, from, to))
	{
		std::cout << "Room is not available in that period!\n";
		return;
	}

	Booking newBooking(roomNumber, from, to, note, 0, false);

	insertBookingSorted(newBooking);
	std::cout << "The room will be unavailable for this period!\n";
}

void Hotel::openFile(const std::string& fileName)
{
	try
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
			rooms.clear();
			bookings.clear();
			return;
		}

		rooms.clear();
		bookings.clear();

		std::string line;
		while (std::getline(file, line))
		{
			if (line == "#BOOKINGS#")
				break;

			std::istringstream iss(line);
			unsigned short int roomNumber, beds;

			if (!(iss >> roomNumber >> beds))
			{
				std::cout << "Error reading room data!\n";
				file.close();
				exit(1);
			}
			rooms.emplace_back(roomNumber, beds);
		}

		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			unsigned short int roomNumber, guests;
			std::string fromStr, toStr, message;
			bool availability;

			if (!(iss >> roomNumber >> fromStr >> toStr >> guests >> availability))
			{
				std::cout << "Error reading booking data!\n";
				file.close();
				exit(1);
			}
			std::getline(iss, message);
			if (!message.empty() && message[0] == ' ') message.erase(0, 1);

			bookings.emplace_back(roomNumber, Date(fromStr), Date(toStr), message, guests, availability);
		}

		file.close();
	}
	catch (...)
	{
		std::cout << "Error reading data!\n";
		exit(1);
	}
}

void Hotel::saveFile(const std::string& fileName) const
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cout << "Cannot save to file " << fileName << "\n";
		return;
	}

	for (const auto& room : rooms)
	{
		file << room.getNumber() << " " << room.getBeds() << "\n";
	}

	file << "#BOOKINGS#\n";

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
}

void Hotel::changeRoom(const unsigned short int roomNumber, const Date& from, const Date& to, const unsigned short int newRoomNumber)
{
	for (auto& booking : bookings)
	{
		if (booking.getEnd() < from)
		{
			break;
		}
		if (booking.getRoomNumber() == roomNumber && booking.getStart()==from && booking.getEnd()==to)
		{
			if (checkIfRoomIsTaken(newRoomNumber, from, to))
			{
				std::cout << "The room is already taken in that period!\n";
				return;
			}
			else
			{
				booking.setRoomNumber(newRoomNumber);
			}
		}
	}
}

void Hotel::checkins() const
{
	for (auto& booking : bookings)
	{
		if (booking.getEnd() < Date::today())
		{
			break;
		}
		std::cout << "Room " << booking.getRoomNumber() << " From " << booking.getStart().toString() << " to " << booking.getEnd().toString() << " note: " << booking.getMessage() << " has " << booking.getGuests() << " guests\n";
	}
}