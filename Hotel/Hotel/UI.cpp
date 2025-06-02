#include "UI.h"
#include <iostream>
#include <sstream>

UI::UI() : running(true) {}

void UI::showHelp() const
{
    std::cout
        <<"\n |                    COMMANDS                    |\n"
        << " |                                                |\n"
        << " |  addRoom <room> <beds>                         |\n"
        << " |  checkin <room> <from> <to> <note> [<guests>]  |\n"
        << " |  availability [<date>]                         |\n"
        << " |  checkout <room>                               |\n"
        << " |  report <from> <to>                            |\n"
        << " |  find <beds> <from> <to>                       |\n"
        << " |  find! <beds> <from> <to>                      |\n"
        << " |  unavailable <room> <from> <to> <note>         |\n"
        << " |  open <filename>                               |\n"
        << " |  close                                         |\n"
        << " |  save                                          |\n"
        << " |  saveas <filename>                             |\n"
        << " |  help                                          |\n"
        << " |  exit                                          |\n"
        << " |             Dates format: YYYY-MM-DD           |\n";
}

void UI::processCommand(const std::string& commandLine)
{
    std::istringstream stream(commandLine);
    std::string command;
    stream >> command;

    if (command == "addRoom")
    {
        unsigned short int roomNumber, beds;

        if (stream >> roomNumber >> beds)
        {
            hotel.addRoom(roomNumber, beds);
        }
        else
        {
            std::cout << "Usage: addRoom <room> <beds>\n";
        }

    }
    else if (command == "checkin")
    {
        unsigned short int roomNumber, guests = 0;
        std::string fromStr, toStr, message;

        if (!(stream >> roomNumber >> fromStr >> toStr))
        {
            std::cout << "Usage: checkin <room> <from> <to> <note> [<guests>]\n";
            return;
        }

        std::getline(stream, message);
        size_t pos = message.find_first_not_of(' ');

        if (pos != std::string::npos) message = message.substr(pos);

        std::istringstream noteStream(message);
        std::string lastToken;
        unsigned short int parsedGuests = 0;
        bool hasGuests = false;
        if (noteStream >> lastToken)
        {
            try
            {
                parsedGuests = static_cast<unsigned short int>(std::stoi(lastToken));
                hasGuests = true;
            }
            catch (...)
            {
                hasGuests = false;
            }
        }
        if (hasGuests)
        {
            size_t lastSpace = message.find_last_of(' ');

            if (lastSpace != std::string::npos)
                message = message.substr(0, lastSpace);

            guests = parsedGuests;
        }

        try
        {
            Date from(fromStr);
            Date to(toStr);

            hotel.checkIn(roomNumber, from, to, message, guests);
        }
        catch (...)
        {
            std::cout << "Invalid date format.\n";
        }

    }
    else if (command == "availability") {
        std::string dateStr;
        if (stream >> dateStr) {
            try {
                Date date(dateStr);
                hotel.availability(date);
            }
            catch (...) {
                std::cout << "Invalid date format.\n";
            }
        }
        else {
            std::cout << "Usage: availability <date>\n";
        }

    }
    else if (command == "checkOut") {
        unsigned short int roomNumber;
        if (stream >> roomNumber) {
            hotel.checkOut(roomNumber);
        }
        else {
            std::cout << "Usage: checkOut <roomNumber>\n";
        }

    }
    else if (command == "report") {
        std::string fromStr, toStr;
        if (stream >> fromStr >> toStr) {
            try {
                Date from(fromStr);
                Date to(toStr);
                hotel.report(from, to);
            }
            catch (...) {
                std::cout << "Invalid date format.\n";
            }
        }
        else {
            std::cout << "Usage: report <from> <to>\n";
        }

    }
    else if (command == "find") {
        unsigned short int beds;
        std::string fromStr, toStr;
        if (stream >> beds >> fromStr >> toStr) {
            try {
                Date from(fromStr);
                Date to(toStr);
                hotel.find(beds, from, to);
            }
            catch (...) {
                std::cout << "Invalid date format!\n";
            }
        }
        else {
            std::cout << "Usage: find <beds> <from> <to>\n";
        }

    }
    else if (command == "find!")
    {
        unsigned short int beds;
        std::string fromStr, toStr;

        if (stream >> beds >> fromStr >> toStr)
        {
            try
            {
                Date from(fromStr);
                Date to(toStr);
                hotel.findSpecial(beds, from, to);
            }
            catch (...)
            {
                std::cout << "Invalid date format!\n";
            }
        }
        else
        {
            std::cout << "Usage: findSpecial <beds> <from> <to>\n";
        }

    }
    else if (command == "unavailable")
    {
        unsigned short int roomNumber;
        std::string fromStr, toStr, note;
        if (!(stream >> roomNumber >> fromStr >> toStr))
        {
            std::cout << "Usage: unavailable <room> <from> <to> <note>\n";
            return;
        }

        std::getline(stream, note);

        size_t pos = note.find_first_not_of(' ');

        if (pos != std::string::npos) note = note.substr(pos);

        try
        {
            Date from(fromStr);
            Date to(toStr);
            hotel.unavailable(roomNumber, from, to, note);
        }
        catch (...)
        {
            std::cout << "Invalid date format!\n";
        }

    }
    else if (command == "openFile")
    {
        std::string filename;
        if (stream >> filename)
        {
            hotel.openFile(filename);
        }
        else
        {
            std::cout << "Usage: open <filename>\n";
        }

    }
    else if (command == "saveFile")
    {
        std::string filename;

        if (stream >> filename)
        {
            hotel.saveFile(filename);
        }
        else
        {
            std::cout << "Usage: saveas <filename>\n";
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
    else
    {
        std::cout << "Unknown command! Type 'help' for a list of commands!\n";
    }
}

void UI::run()
{
    std::cout << "<Hotel Management System>\n   Type \"help\" to see the commands\n";

    while (running)
    {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);
        if (!line.empty())
            processCommand(line);
    }
    std::cout << "Goodbye!\n";
}