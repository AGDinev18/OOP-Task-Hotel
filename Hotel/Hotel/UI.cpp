#include "UI.h"
#include <iostream>
#include <sstream>
#include <cctype>

UI::UI() : running(true), fileOpened(false) {}

void UI::requireFileOpened() const
{
	if (!fileOpened)
		throw std::runtime_error("No file opened! Use \"open <filename>\" first!");
}

void UI::showHelp() const
{
	std::cout
		<< "\n |                    COMMANDS                    |\n"
		<< " |------------------------------------------------|\n"
		<< " |  open <filename>                               |\n"
		<< " |  close                                         |\n"
		<< " |  save                                          |\n"
		<< " |  saveas <filename>                             |\n"
		<< " |  addroom <room> <beds>                         |\n"
		<< " |  changeroom <room> <newRoomNumber> <from> <to>  |\n"
		<< " |  checkin <room> <from> <to> <note> [<guests>]  |\n"
		<< " |  checkout <room>                               |\n"
		<< " |  availability [<date>]                         |\n"
		<< " |  report <from> <to>                            |\n"
		<< " |  find <beds> <from> <to>                       |\n"
		<< " |  find! <beds> <from> <to>                      |\n"
		<< " |  unavailable <room> <from> <to> <note>         |\n"
		<< " |  help                                          |\n"
		<< " |  exit                                          |\n"
		<< " | Dates must be in format: YYYY-MM-DD            |\n";
}

void UI::processCommand(const std::string& commandLine)
{
	std::istringstream stream(commandLine);
	std::string command;
	stream >> command;

	try
	{
		if (command == "open")
		{
			if (fileOpened)
			{
				std::cout << "Close the current file first before opening a new file!\n";
				return;
			}
			std::string fileName;
			std::getline(stream, fileName);
			size_t pos = fileName.find_first_not_of(' ');
			if (pos != std::string::npos)
				fileName = fileName.substr(pos);
			if (!fileName.empty())
			{
				hotel.openFile(fileName);
				currentFileName = fileName;
				fileOpened = true;
				std::cout << "Successfully opened " << fileName << "\n";
			}
			else
			{
				std::cout << "Usage: open <filename>\n";
			}
		}
		else if (command == "help")
		{
			showHelp();
		}
		else if (command == "exit")
		{
			running = false;
		}
		else {
			requireFileOpened();

			if (command == "save")
			{
				hotel.saveFile(currentFileName);
				std::cout << "Successfully saved " << currentFileName << "\n";
			}
			else if (command == "saveas")
			{
				std::string fileName;
				std::getline(stream, fileName);
				size_t pos = fileName.find_first_not_of(' ');
				if (pos != std::string::npos)
					fileName = fileName.substr(pos);

				if (!fileName.empty())
				{
					hotel.saveFile(fileName);
					std::cout << "Successfully saved " << fileName << "\n";
				}
				else
				{
					std::cout << "Usage: saveas <filename>\n";
				}
			}
			else if (command == "close")
			{
				hotel.~Hotel();
				fileOpened = false;
				std::cout << "Successfully closed " << currentFileName << "\n";
				currentFileName.clear();
			}
			else if (command == "addroom")
			{
				short int room, beds;
				if (stream >> room >> beds)
				{
					if (room < 0)
					{
						std::cout << "Room has to be positive number!\n";
						return;
					}
					if (beds < 0)
					{
						std::cout << "Beds have to be positive number!\n";
						return;
					}
					hotel.addRoom(room, beds);
				}
				else
					std::cout << "Usage: addroom <room> <beds>\n";

			}
			else if (command == "changeroom")
			{
				unsigned short int roomNumber, newRoomNumber;
				std::string fromStr, toStr;

				if (stream >> roomNumber >> newRoomNumber >> fromStr >> toStr)
				{
					if (fromStr >= toStr)
					{
						std::cout << "Invalid dates!\n";
						return;
					}
					try
					{
						hotel.changeRoom(roomNumber, Date(fromStr), Date(toStr), newRoomNumber);
					}
					catch (...)
					{
						std::cout << "Invalid date format!\n";
					}
				}
				else
				{
					std::cout << "Usage: changeroom <roomNumber> <newRoomNumber> <from> <to>\n";
				}
			}
			else if (command == "checkin")
			{
				unsigned short int room, guests = 0;
				std::string fromStr, toStr;
				std::string lineAfterDates;

				if (!(stream >> room >> fromStr >> toStr))
				{
					std::cout << "Usage: checkin <room> <from> <to> <note> [<guests>]\n";
					return;
				}

				if (fromStr >= toStr)
				{
					std::cout << "Invalid dates!\n";
					return;
				}

				if (Date(fromStr) < Date::today())
				{
					std::cout << "Cannot make booking with outdated date!\nEarliest possible date to book is: " << Date::today().toString() << std::endl;
					return;
				}

				std::getline(stream, lineAfterDates);

				size_t pos = lineAfterDates.find_first_not_of(' ');
				if (pos != std::string::npos)
					lineAfterDates = lineAfterDates.substr(pos);
				else
					lineAfterDates.clear();

				if (lineAfterDates.empty())
				{
					std::cout << "There is no message!\n";
					return;
				}

				std::istringstream iss(lineAfterDates);
				std::vector<std::string> tokens;
				std::string token;

				while (iss >> token)
					tokens.push_back(token);

				bool hasGuests = false;
				if (!tokens.empty())
				{
					try
					{
						guests = static_cast<unsigned short>(std::stoi(tokens.back()));
						hasGuests = true;
						tokens.pop_back();
					}
					catch (...) {}
				}

				std::string note;
				for (size_t i = 0; i < tokens.size(); ++i)
				{
					note += tokens[i];
					if (i != tokens.size() - 1)
						note += ' ';
				}

				if (note.empty() || note.find_first_not_of(' ') == std::string::npos)
				{
					std::cout << "There is no message!\n";
					return;
				}

				try
				{
					Date from(fromStr);
					Date to(toStr);
					hotel.checkIn(room, from, to, note, guests);
				}
				catch (...)
				{
					std::cout << "Invalid date format!\n";
				}
			}
			else if (command == "availability")
			{
				std::string dateStr;

				if (stream >> dateStr)
				{
					try
					{
						hotel.availability(Date(dateStr));
					}
					catch (...)
					{
						std::cout << "Invalid date format!\n";
					}
				}
				else
				{
					hotel.availability(Date::today());
				}
			}
			else if (command == "checkout")
			{
				unsigned short int room;
				if (stream >> room)
					hotel.checkOut(room);
				else
					std::cout << "Usage: checkout <room>\n";

			}
			else if (command == "report")
			{
				std::string fromStr, toStr;
				if (stream >> fromStr >> toStr)
				{
					if (fromStr >= toStr)
					{
						std::cout << "Invalid dates!\n";
						return;
					}
					try
					{
						hotel.report(Date(fromStr), Date(toStr));
					}
					catch (...)
					{
						std::cout << "Invalid date format!\n";
					}
				}
				else
				{
					std::cout << "Usage: report <from> <to>\n";
				}

			}
			else if (command == "find")
			{
				unsigned short int beds;
				std::string fromStr, toStr;

				if (stream >> beds >> fromStr >> toStr)
				{
					if (fromStr >= toStr)
					{
						std::cout << "Invalid dates!\n";
						return;
					}
					try
					{
						hotel.find(beds, Date(fromStr), Date(toStr));
					}
					catch (...)
					{
						std::cout << "Invalid date format!\n";
					}
				}
				else
				{
					std::cout << "Usage: find <beds> <from> <to>\n";
				}

			}
			else if (command == "find!")
			{
				unsigned short int beds;
				std::string fromStr, toStr;
				if (stream >> beds >> fromStr >> toStr)
				{
					if (fromStr >= toStr)
					{
						std::cout << "Invalid dates!\n";
						return;
					}
					try
					{
						hotel.findSpecial(beds, Date(fromStr), Date(toStr));
					}
					catch (...)
					{
						std::cout << "Invalid date format!\n";
					}
				}
				else
				{
					std::cout << "Usage: find! <beds> <from> <to>\n";
				}

			}
			else if (command == "unavailable")
			{
				unsigned short int room;
				std::string fromStr, toStr, message;
				if (!(stream >> room >> fromStr >> toStr))
				{
					std::cout << "Usage: unavailable <room> <from> <to> <note>\n";
					return;
				}
				if (fromStr >= toStr)
				{
					std::cout << "Invalid dates!\n";
					return;
				}
				std::getline(stream, message);
				size_t pos = message.find_first_not_of(' ');
				if (pos != std::string::npos)
					message = message.substr(pos);
				try
				{
					hotel.unavailable(room, Date(fromStr), Date(toStr), message);
				}
				catch (...)
				{
					std::cout << "Invalid date format!\n";
				}

			}
			else
			{
				std::cout << "|  Unknown command! Type \"help\" to see the available commands!  |\n";
			}
		}

	}
	catch (const std::runtime_error& e)
	{
		std::cout << "Error: " << e.what() << "\n";
	}
}

void UI::run()
{
	std::cout << "<Hotel Management System>\n  Type \"help\" to see the commands!\n";

	while (running)
	{
		std::cout << "> ";
		std::string line;
		std::getline(std::cin, line);
		if (!line.empty())
			processCommand(line);
	}

	std::cout << "Thanks for working with Hotel Management System!\n";
}