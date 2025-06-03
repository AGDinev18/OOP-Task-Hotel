#pragma once
#include "Hotel.h"
#include <string>

class UI {
private:
    bool running;
    bool fileOpened;
    std::string currentFileName;
    Hotel hotel;

    void requireFileOpened() const;
    void showHelp() const;

public:
    UI();
    void run();
    void processCommand(const std::string& commandLine);
};