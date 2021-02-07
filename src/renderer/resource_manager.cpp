#include <resource_manager.h>


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

std::string ResourceManager::read_string_from_file(std::string fileName)
{
	std::ifstream meInput(fileName);
	if (!meInput.good())
	{
		std::cout << "Failed to load file.." << fileName << '\n';
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>()
	);
}

std::vector<std::vector<char>>  ResourceManager::read_level_from_file(const char* fileName)
{
    std::ifstream meInput(fileName);

    if (!meInput.good())
    {
        std::cout << "Failed to load " << fileName << '\n';
        exit(1);
    }

    // Retrieves the text from file, and turns it into a string
    char c;
    std::vector<std::vector<char>> layout;

    int x = 0;

    layout.push_back(std::vector<char>());
    while (!meInput.eof())
    {
        meInput.get(c);
        switch (c) {
        case ' ':
            break;
        case '\n':
            x++;
            layout.push_back(std::vector<char>());
            break;
        default:
            layout[x].push_back(c);
            break;
        }
    }

    return layout;
}