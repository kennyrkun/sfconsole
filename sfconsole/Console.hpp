#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <SFML\Graphics.hpp>

#include <string>
#include <vector>

#include "Scrollbar.hpp"

class sfConsole
{
public:
	sfConsole(std::string $title);
	~sfConsole();

	void create();
	void close();
	void Main();
	void printLine(std::string string);

	void enableInput();
	void disableInput();

	bool isOpen() { return m_open; }

	std::vector<sf::Text> lines;

private:
	sf::RenderWindow window;
	bool m_open;

	sf::View viewScroller;
	Scrollbar scrollbar;

	void Update();
	void Render();
	void ProcessInput(sf::Event &e);
};

#endif /* CONSOLE_HPP */
 