#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <SFML\Graphics.hpp>

#include <string>
#include <vector>

class Console
{
public:
	Console(std::string $title);
	Console(std::string $title, sf::Vector2i dimensions);
	~Console();



	void create();
	void close();
	void log(std::string message);

	sf::RenderWindow window;
};

#endif /* CONSOLE_HPP */
 