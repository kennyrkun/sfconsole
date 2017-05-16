#include "Console.hpp"

#include <iostream>
#include <thread>
#include <chrono>

std::vector<sf::Text> lines;
sf::Font font;

Console::Console(std::string $title)
{
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

	sf::Text newline;
	newline.setString("SFBash [Version: something]");
	newline.setCharacterSize(13);
	newline.setFont(font);
	newline.setPosition(0, -2);
	lines.push_back(newline);

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
	window.create(sf::VideoMode(665, 320), "Console", sf::Style::Close);
	window.setPosition(sf::Vector2i(20, 20));

	sf::Text work;
	work.setFont(font);
	work.setString("copyright or whatever");
	work.setCharacterSize(13);
	work.setPosition(0, 0);

	for (size_t i = 0; i < 1000; i++)
	{
		log("test" + std::to_string(i));
	}

	sf::RectangleShape scrollbar_background;
	sf::RectangleShape scrollbar_bar;
	sf::RectangleShape scrollbar_up;
	sf::RectangleShape scrollbar_down;

	scrollbar_background.setSize(sf::Vector2f(20, window.getSize().y));
	scrollbar_background.setOrigin(sf::Vector2f(scrollbar_background.getLocalBounds().width / 2, scrollbar_background.getLocalBounds().height / 2));
	scrollbar_background.setPosition(sf::Vector2f(window.getSize().x - scrollbar_background.getLocalBounds().width / 2, window.getSize().y / 2));

	scrollbar_bar.setSize(sf::Vector2f(16, (window.getSize().y - lines.size()) / 4));
	scrollbar_bar.setPosition(sf::Vector2f(window.getSize().x - (scrollbar_background.getLocalBounds().width / 2) - scrollbar_bar.getLocalBounds().width / 2, 20));
	scrollbar_bar.setFillColor(sf::Color(190, 190, 190));

	sf::View view;
	view.setSize(sf::Vector2f(window.getSize()));
	view.setCenter(sf::Vector2f(window.getView().getCenter()));

	window.setView(view);

	sf::Vector2i olddimensions(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
				window.close();

			if (event.type == sf::Event::EventType::Resized)
			{
				if (window.getSize().x > olddimensions.x)
					std::cout << "width was increased" << std::endl;
				else if (window.getSize().x < olddimensions.x)
					std::cout << "width was decreased" << std::endl;
				else
					std::cout << "width did not change" << std::endl;

				if (window.getSize().y > olddimensions.y)
					std::cout << "height was increased" << std::endl;
				else if (window.getSize().y < olddimensions.y)
					std::cout << "height was decreased" << std::endl;
				else
					std::cout << "height did not change" << std::endl;

				olddimensions = sf::Vector2i(window.getSize().x, window.getSize().y);
			}

			else if (event.type == sf::Event::EventType::MouseWheelMoved)
			{
//				std::cout << event.mouseWheel.delta << std::endl;

				if (event.mouseWheel.delta > 0) // up
				{
					std::cout << "up" << std::endl;

					view.move(0, 13);
				}
				else // down
				{
					std::cout << "down" << std::endl;

					lines[1].setString("test");

					view.move(0, -13);
				}
			}
		}

		window.clear();

		window.draw(scrollbar_background);
		window.draw(scrollbar_bar);
		window.draw(scrollbar_up);
		window.draw(scrollbar_down);

		window.setView(view);

		if (!lines.empty())
		{
			for (size_t i = 0; i < lines.size(); i++)
			{
				window.draw(lines[i]);
			}
		}

		window.display();
	}
}

void Console::close()
{
	window.close();
}

void Console::log(std::string message)
{
	std::cout << "logging \"" + message + "\"" << std::endl;

	sf::Text newline;
	newline.setString(message);
	newline.setFont(font);
	newline.setCharacterSize(13);
	newline.setPosition(0, lines.back().getPosition().y + 12);
	lines.push_back(newline);
}
