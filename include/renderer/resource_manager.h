#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	//ReadStringFromFile reads the .txt file with the set path: "fileName" and returns
	//the file as a std::string.
	std::string read_string_from_file(std::string fileName);
	std::vector<std::vector<char>>  ResourceManager::read_level_from_file(const char* fileName);

private:

};

#endif // !RESOURCEMANAGER_H
