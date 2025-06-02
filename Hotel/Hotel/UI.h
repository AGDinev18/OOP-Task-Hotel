#pragma once
#include "Hotel.h"
#include <string>

class UI {
private:
    Hotel hotel;
    bool running;

    void showHelp() const;
    void processCommand(const std::string& commandLine);

public:
    UI();
    void run();
};