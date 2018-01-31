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

	void print(std::string string);
	void printLine(std::string string);
	void clearScreen();

	bool isOpen() { return window.isOpen(); }
	bool ready = false;

	std::vector<sf::Text> lines;

	void HandleEvents(const sf::Event &e);
	void Update();
	void Render();

private:
	sf::RenderWindow window;

	sf::View viewScroller;
	Scrollbar scrollbar;

	sf::Font font;

	void updateScrollThumbSize();
	void updateScrollLimits();
	// TODO: viewable area class
	float scrollerTopPosition;
	float scrollerBottomPosition;
	float scrollerMinPosition;
	float scrollerMaxPosition;

	bool update;
	bool repaint;
};

#endif /* CONSOLE_HPP */
 