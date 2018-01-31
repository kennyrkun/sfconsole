#include "Console.hpp"

#include <iostream>
#include <thread>
#include <chrono>

// Public

sfConsole::sfConsole(std::string $title)
{
	font.loadFromFile("C://Windows//Fonts//Arial.ttf");

	sf::Text newline;
	newline.setString("SFConsole [Version: 1]");
	newline.setCharacterSize(13);
	newline.setFont(font);
	newline.setPosition(sf::Vector2f(2, 0));
	lines.push_back(newline);

	std::cout << "Console created." << std::endl;
}

sfConsole::~sfConsole()
{
	window.close();

	std::cout << "Console destroyed." << std::endl;
}

void sfConsole::create()
{
	window.create(sf::VideoMode(665, 315), "Console", sf::Style::Close);
	window.setFramerateLimit(1);
	window.setPosition(sf::Vector2i(20, 20));
	scrollbar.create(&window);

	viewScroller.setSize(sf::Vector2f(window.getSize()));
	viewScroller.setCenter(sf::Vector2f(window.getView().getCenter()));
	window.setView(viewScroller);

	ready = true;
	update = true;
	repaint = true;
}

void sfConsole::close()
{
	window.close();
}

void sfConsole::print(std::string string)
{
	if (!lines.empty())
	{
		// TODO: make this match the size of the console
		const int maxStringLength = std::numeric_limits<int>::max();

		std::string newLine; // the line the add onto

		std::string lastLine = lines.back().getString(); //  temporary last line printed

		newLine = lastLine + string; // add this to the back of the last line

		if (newLine.size() > maxStringLength)
		{
			std::string firstLine = lastLine.substr(0, maxStringLength); // beginning to the place where it hits the edge of the screen
			std::string secondLine = lastLine.substr(maxStringLength, lastLine.back()); // place where it hits the edge of the screen to the end

			//TODO: this might break if the string is so long that it wraps around three lines

			lines.back().setString(firstLine); // set the last printed line to the first part of the new line
			printLine(secondLine); // print new line after the first line
		}
		else // line is not longer than max
		{
			lines.back().setString(newLine);
		}
	}
	else
	{
		printLine(string);
	}
}

void sfConsole::printLine(std::string string)
{
	sf::Text newline;
	newline.setFont(font);
	newline.setCharacterSize(13);
	newline.setString(string);
	newline.setPosition(2, lines.back().getPosition().y + 13);

	lines.push_back(newline);

	updateScrollThumbSize();
	updateScrollLimits();
}

void sfConsole::clearScreen()
{
	lines.clear();

	updateScrollThumbSize();
	updateScrollLimits();
}

void sfConsole::Main()
{
	viewScroller.setSize(sf::Vector2f(window.getSize()));
	viewScroller.setCenter(sf::Vector2f(window.getView().getCenter()));
	window.setView(viewScroller);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			HandleEvents(event);

		Update();
		Render();
	}
}

void sfConsole::HandleEvents(const sf::Event& event)
{
	if (event.type == sf::Event::EventType::Closed)
	{
		close();
	}
	else if (event.type == sf::Event::EventType::MouseWheelMoved && scrollbar.isEnabled)
	{
		if (event.mouseWheel.delta < 0) // down, or move items up
		{
			scrollbar.moveThumbDown();

			if (scrollerBottomPosition < scrollerMaxPosition)
			{
				viewScroller.move(0, scrollbar.scrollJump);

				updateScrollLimits();

				if (scrollerBottomPosition > scrollerMaxPosition) // clamp cardScroller
				{
					std::cout << "cardScroller went too far down (" << scrollerBottomPosition - scrollerMaxPosition << "), clamping..." << "\n";
					viewScroller.setCenter(viewScroller.getCenter().x, scrollerMaxPosition - viewScroller.getSize().y / 2 + 8);
					updateScrollLimits();
				}
			}
			else
			{
				std::cout << "cannot scroll view down (" << scrollerBottomPosition << " < " << scrollerMaxPosition << ")" << "\n";
			}
		}
		else if (event.mouseWheel.delta > 0) // scroll up, or move items down
		{
//			if (scrollbar.canScrollUp())
//				cardScroller->move(0, -scrollbar.scrollJump);

			scrollbar.moveThumbUp();

			if (scrollerTopPosition > scrollerMinPosition)
			{
				viewScroller.move(0, -scrollbar.scrollJump);

				updateScrollLimits();

				if (scrollerTopPosition < scrollerMinPosition) // clamp cardScroller
				{
					std::cout << "cardScroller went too far up (" << scrollerMaxPosition - scrollerTopPosition << "), clamping..." << "\n";
					viewScroller.setCenter(viewScroller.getCenter().x, scrollerMinPosition + viewScroller.getSize().y / 2);
					updateScrollLimits();
				}
			}
			else
			{
				std::cout << "cannot scroll view up (" << scrollerTopPosition << " < " << scrollerMaxPosition << ")" << "\n";
			}
		}
	}
}

void sfConsole::Update()
{
}

void sfConsole::Render()
{
	window.clear();

	window.setView(window.getDefaultView());
	window.draw(scrollbar);

	window.setView(viewScroller);

	for (size_t i = 0; i < lines.size(); i++)
		window.draw(lines[i]);

	window.display();
}

// private

void sfConsole::updateScrollThumbSize()
{
	// set the scrollbar size

	float contentHeight(0);
	contentHeight = 13 * lines.size();

	scrollbar.update(contentHeight, viewScroller.getSize().y);

	updateScrollLimits();
}

void sfConsole::updateScrollLimits()
{
	scrollerTopPosition = viewScroller.getCenter().y - viewScroller.getSize().y / 2;
	scrollerBottomPosition = viewScroller.getCenter().y + viewScroller.getSize().y / 2;
	scrollerMinPosition = 0;
	scrollerMaxPosition = scrollbar.contentHeight;
}
