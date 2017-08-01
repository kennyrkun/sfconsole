#include "Console.hpp"

#include <iostream>
#include <thread>
#include <chrono>

sf::Font font;
sf::Text userInput;
sf::RectangleShape thingybehindtheuserinput;

bool update(false);
bool canDoInput(false);

// Public

sfConsole::sfConsole(std::string $title)
{
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

	sf::Text newline;
	newline.setString("SFConsole [Version: something]");
	newline.setCharacterSize(13);
	newline.setFont(font);
	newline.setPosition(sf::Vector2f(2, 0));
	lines.push_back(newline);

	userInput.setFont(font);
	userInput.setCharacterSize(13);
//	userInput.setString("> ");

	thingybehindtheuserinput.setSize(sf::Vector2f(8, 3));
	thingybehindtheuserinput.setOrigin(sf::Vector2f(thingybehindtheuserinput.getLocalBounds().width / 2, thingybehindtheuserinput.getLocalBounds().height / 2));

	std::cout << "New console created." << std::endl;
}

sfConsole::~sfConsole()
{
	window.close();

	std::cout << "Console destroyed." << std::endl;
}

void sfConsole::create()
{
	window.create(sf::VideoMode(665, 315), "Console", sf::Style::Close);
	window.setPosition(sf::Vector2i(20, 20));

	scrollbar_background.setSize(sf::Vector2f(20.0f, static_cast<int>(window.getSize().y)));
	scrollbar_background.setOrigin(sf::Vector2f(scrollbar_background.getLocalBounds().width / 2.0f, scrollbar_background.getLocalBounds().height / 2.0f));
	scrollbar_background.setPosition(sf::Vector2f(static_cast<int>(window.getSize().x) - scrollbar_background.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f));

	scrollbar_bar.setSize(sf::Vector2f(16, (static_cast<int>(window.getSize().y) - lines.size()) / 4.0f));
	scrollbar_bar.setPosition(sf::Vector2f(static_cast<int>(window.getSize().x) - (scrollbar_background.getLocalBounds().width / 2) - scrollbar_bar.getLocalBounds().width / 2, 20));
	scrollbar_bar.setFillColor(sf::Color(190, 190, 190));

//	Main();
}

void sfConsole::close()
{
	window.close();
}

void sfConsole::printLine(std::string string)
{
	update = true;

	sf::Text newline;
	newline.setString(string);
	newline.setFont(font);
	newline.setCharacterSize(13);
	newline.setPosition(2, lines.back().getPosition().y + 13);

	lines.push_back(newline);
}

void sfConsole::Update()
{
	std::cout << "updating" << std::endl;

	scrollbar_background.setPosition(sf::Vector2f((viewArea.getCenter().x * 2) - (scrollbar_background.getLocalBounds().width / 2), viewArea.getCenter().y));
	scrollbar_bar.setPosition(sf::Vector2f(scrollbar_background.getPosition().x - scrollbar_background.getLocalBounds().width / 2, scrollbar_background.getPosition().y));
	userInput.setPosition(sf::Vector2f(2, lines.back().getPosition().y + 13));
	thingybehindtheuserinput.setPosition(sf::Vector2f(userInput.getPosition().x + (userInput.getLocalBounds().width + 8), userInput.getPosition().y + 13));

	update = false;
}

void sfConsole::Main()
{
	update = true;

	viewArea.setSize(sf::Vector2f(window.getSize()));
	viewArea.setCenter(sf::Vector2f(window.getView().getCenter()));

	window.setView(viewArea);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::EventType::MouseWheelMoved)
			{
				if (event.mouseWheel.delta < 0) // up
				{
					viewArea.move(0, 13);
				}
				else if (event.mouseWheel.delta > 0 && (viewArea.getCenter().y - viewArea.getSize().y / 2) > 0) // down
				{
					viewArea.move(0, -13);
				}

				update = true;
			}
			else if (canDoInput && event.type == sf::Event::EventType::TextEntered)
			{
				ProcessInput(event);
				update = true;
			}
		}

		if (update)
		{
			Update();
			Render();
		}
	}
}

void sfConsole::enableInput()
{
	canDoInput = true;
}

void sfConsole::disableInput()
{
	canDoInput = false;
}

// Private

void sfConsole::Render()
{
	window.clear();

	window.draw(scrollbar_background);
	window.draw(scrollbar_bar);
	window.draw(scrollbar_up);
	window.draw(scrollbar_down);

	window.setView(viewArea);

	for (size_t i = 0; i < lines.size(); i++)
	{
		window.draw(lines[i]);
	}

	if (canDoInput)
	{
		window.draw(userInput);
		window.draw(thingybehindtheuserinput);
	}

	window.display();
}

void sfConsole::ProcessInput(sf::Event &e)
{
	if (e.text.unicode < 128) // something on a keyboard
	{
		std::string message = userInput.getString(); // temp string

		if (e.text.unicode == 13) // return key
		{
			if (message.length() != 0) // can't send nothing, can we?
			{
				printLine(message);
			}
			else // length != 0
			{
				std::cout << "cannot send an empty message" << std::endl;
			}

			message.clear();
		}
		else if (e.text.unicode == 8) // backspace
		{
			if (message.length() != 0) // can't remove nothing
				message.pop_back();
		}
		else // regular characters
		{
			message += static_cast<wchar_t>(e.text.unicode);
		}

		userInput.setString(message);
	}
}
