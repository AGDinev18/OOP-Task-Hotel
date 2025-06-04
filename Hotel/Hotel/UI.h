#pragma once
#include "Hotel.h"
#include <string>

class UI {
private:
    bool running;
    bool fileOpened;
    std::string currentFileName;
    Hotel hotel;

    void requireFileOpened() const; // Requires an opened file
    void showHelp() const; // Prints the list of possible commands

public:
    UI(); // Constructor to create object
    void run(); // Main method to start running the app
    void processCommand(const std::string& commandLine); // Handles the given command
};