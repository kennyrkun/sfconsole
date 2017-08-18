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
	scrollbar.create(&window);

	m_open = true;
}

void sfConsole::close()
{
	m_open = false;
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

	// set the scrollbar size
	float contentHeight = 0;
		contentHeight += 13 * lines.size();

	scrollbar.update(contentHeight, viewScroller.getSize().y);

	userInput.setPosition(sf::Vector2f(2, lines.back().getPosition().y + 13));
	thingybehindtheuserinput.setPosition(sf::Vector2f(userInput.getPosition().x + (userInput.getLocalBounds().width + 8), userInput.getPosition().y + 13));

	update = false;
}

void sfConsole::Main()
{
	viewScroller.setSize(sf::Vector2f(window.getSize()));
	viewScroller.setCenter(sf::Vector2f(window.getView().getCenter()));
	window.setView(viewScroller);

	Update();

//	update = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				close();
			}
			else if (event.type == sf::Event::EventType::MouseWheelMoved)
			{
				if (event.mouseWheel.delta < 0) // up
				{
//					if ((viewScroller.getCenter().y - viewScroller.getSize().y) < scrollbar.scrollJumpMultiplier) // top of the thing
					{
						viewScroller.move(0, static_cast<int>(scrollbar.scrollJump));
						scrollbar.moveThumbUp();
					}
				}
				else if (event.mouseWheel.delta > 0) // scroll down
				{
//					if ((viewScroller.getCenter().y - viewScroller.getSize().y / 2) > scrollbar.scrollJumpMultiplier) // top of the thing
					{
						viewScroller.move(0, static_cast<int>(-scrollbar.scrollJump));
						scrollbar.moveThumbDown();
					}
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

//	window.draw(scrollbar_background);
//	window.draw(scrollbar_bar);
//	window.draw(scrollbar_up);
//	window.draw(scrollbar_down);

	window.setView(window.getDefaultView());
	scrollbar.draw();

	window.setView(viewScroller);

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
			message += static_cast<char>(e.text.unicode);
		}

		userInput.setString(message);
	}
}
