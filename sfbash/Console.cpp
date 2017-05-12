#include "Console.hpp"

#include <iostream>

Console::Console(std::string $title)
{
	std::cout << "New console created." << std::endl;
}

Console::Console(std::string $title, sf::Vector2i dimensions)
{
	std::cout << "New console created." << std::endl;
}

Console::~Console()
{
	window.close();

	std::cout << "Console destroyed." << std::endl;
}

void Console::create()
{
	window.create(sf::VideoMode(665, 320), "Terminal", sf::Style::Titlebar);
	window.setPosition(sf::Vector2i(20, 20));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
				window.close();

			if (event.type == sf::Event::EventType::Resized)
				std::cout << window.getSize().x << " : " << window.getSize().y << std::endl;
		}

		window.clear();

		window.display();
	}
}

void Console::close()
{
	window.close();
}

void Console::log(std::string message)
{
	std::cout << "logging" << std::endl;

	sf::Text newline;
	newline.setString(message);
}
