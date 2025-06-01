#pragma once
#include <string>
class FileCommands
{
private:
	const std::string filename;
public:
	void open();
	void close();
	void save();
	void saveAs();
	void help();
	void exit();
};