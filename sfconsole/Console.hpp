#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <SFML\Graphics.hpp>

#include <string>
#include <vector>

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

	std::vector<sf::Text> lines;

private:
	sf::RenderWindow window;

	sf::RectangleShape scrollbar_background;
	sf::RectangleShape scrollbar_bar;
	sf::RectangleShape scrollbar_up;
	sf::RectangleShape scrollbar_down;

	sf::View viewArea;

	void Update();
	void Render();
	void ProcessInput(sf::Event &e);
};

#endif /* CONSOLE_HPP */
 