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
	newline.setPosition(0, 0);
	lines.push_back(newline);

	std::cout << "New console created." << std::endl;
}

Console::~Console()
{
	window.close();

	std::cout << "Console destroyed." << std::endl;
}

void Console::create()
{
	window.create(sf::VideoMode(665, 315), "Console", sf::Style::Close);
	window.setPosition(sf::Vector2i(20, 20));

	scrollbar_background.setSize(sf::Vector2f(20.0f, static_cast<int>(window.getSize().y)));
	scrollbar_background.setOrigin(sf::Vector2f(scrollbar_background.getLocalBounds().width / 2.0f, scrollbar_background.getLocalBounds().height / 2.0f));
	scrollbar_background.setPosition(sf::Vector2f(static_cast<int>(window.getSize().x) - scrollbar_background.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f));

	scrollbar_bar.setSize(sf::Vector2f(16, (static_cast<int>(window.getSize().y) - lines.size()) / 4.0f));
	scrollbar_bar.setPosition(sf::Vector2f(static_cast<int>(window.getSize().x) - (scrollbar_background.getLocalBounds().width / 2) - scrollbar_bar.getLocalBounds().width / 2, 20));
	scrollbar_bar.setFillColor(sf::Color(190, 190, 190));

	Main();
}

void Console::close()
{
	window.close();
}

void Console::Main()
{
	sf::View view;
	view.setSize(sf::Vector2f(window.getSize()));
	view.setCenter(sf::Vector2f(window.getView().getCenter()));

	window.setView(view);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
				window.close();

			else if (event.type == sf::Event::EventType::MouseWheelMoved)
			{
				//				std::cout << event.mouseWheel.delta << std::endl;

				if (event.mouseWheel.delta < 0) // up
				{
					view.move(0, 13);
				}
				else if (event.mouseWheel.delta > 0 && (view.getCenter().y - view.getSize().y / 2) > 0) // down
				{
					lines[1].setString("test");

					view.move(0, -13);
				}
			}
		}

		scrollbar_background.setPosition((view.getCenter().x * 2) - (scrollbar_background.getLocalBounds().width / 2), view.getCenter().y);
		scrollbar_bar.setPosition(scrollbar_background.getPosition().x, scrollbar_background.getPosition().y);

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

void Console::log(std::string message)
{
//	std::cout << "logging \"" + message + "\"" << std::endl;

	sf::Text newline;
	newline.setString(message);
	newline.setFont(font);
	newline.setCharacterSize(13);
	newline.setPosition(2, lines.back().getPosition().y + 13);
	lines.push_back(newline);
}
