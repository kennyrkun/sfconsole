#include "Console.hpp"

#include <iostream>

Console::Console()
{
	std::cout << "New console created." << std::endl;
}

Console::~Console()
{
	std::cout << "Console destroyed." << std::endl;
}
