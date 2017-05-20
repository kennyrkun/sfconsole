#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <SFML\Graphics.hpp>

#include <string>
#include <vector>

class Console
{
public:
	Console(std::string $title);
	~Console();

	void create();
	void close();

	void Main();
	void Render();
//	void Update();
	void ProcessInputs(sf::Event &e);

	void log(std::string message);

private:
	sf::RenderWindow window;

	sf::RectangleShape scrollbar_background;
	sf::RectangleShape scrollbar_bar;
	sf::RectangleShape scrollbar_up;
	sf::RectangleShape scrollbar_down;
};

#endif /* CONSOLE_HPP */
 