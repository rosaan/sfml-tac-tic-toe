#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "grid.h"

using namespace std;

sf::RectangleShape createRectangle(float width = 1.0f, float height = 1.0f, sf::Vector2f position = sf::Vector2f(0, 0),
								   const sf::Color &myFillColor = sf::Color::White,
								   const sf::Color &myOutlineColor = sf::Color::Black,
								   float myOutlineThickness = -2)
{
	sf::RectangleShape myRectangle;
	sf::Vector2f myRectangleSize(width, height);
	myRectangle.setSize(myRectangleSize);
	myRectangle.setPosition(position);
	myRectangle.setFillColor(myFillColor);
	myRectangle.setOutlineColor(myOutlineColor);
	myRectangle.setOutlineThickness(myOutlineThickness);
	return myRectangle;
}

int main()
{

	bool p1 = true;
	bool p2 = false;
	bool done = false;
	bool win = false;
	bool theend = false;
	bool restart = false;
	int v = rand() % 9;
	int change = v;
	int gX = -1;
	int gY = -1;
	grid *g[9];
	g[0] = new grid(100, 50);
	g[1] = new grid(260, 50);
	g[2] = new grid(420, 50);
	g[3] = new grid(100, 210);
	g[4] = new grid(260, 210);
	g[5] = new grid(420, 210);
	g[6] = new grid(100, 370);
	g[7] = new grid(260, 370);
	g[8] = new grid(420, 370);
	const int screenWidth = 650;
	const int screenHeight = 575;
	sf::RectangleShape mainbg;
	sf::Texture background;
	if (!background.loadFromFile("data/bg/background4.png"))
	{
	};
	mainbg.setSize(sf::Vector2f(screenWidth, screenHeight));
	mainbg.setPosition(0, 0);
	mainbg.setTexture(&background);
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight, 32), "Window Title");
	window.setVerticalSyncEnabled(true);

	bool showHardwareMouse;
	bool started;
	bool drag = true;
	bool reset = true;

	while (window.isOpen())
	{
		string player;
		string playerw;
		if (p1)
		{
			player = "1";
		}
		else if (p2)
		{
			player = "2";
		}
		if (p1)
		{
			playerw = "2";
		}
		else if (p2)
		{
			playerw = "1";
		}
		sf::Font font;
		if (!font.loadFromFile("data/font/kenvector_future_thin.ttf"))
			;
		sf::Text text;
		text.setFont(font);
		text.setString("Player " + player + " turn");
		text.setPosition(200, 0);
		text.setCharacterSize(36);
		text.setColor(sf::Color::White);
		sf::Text textw;
		textw.setFont(font);
		textw.setString("Click SPACEBAR to restart the game");
		textw.setPosition(20, 525);
		textw.setCharacterSize(30);
		textw.setColor(sf::Color::White);

		if (restart)
		{
			p1 = true;
			p2 = false;
			done = false;
			win = false;
			theend = false;
			v = rand() % 9;
			change = v;
			gX = -1;
			gY = -1;
			g[0] = new grid(100, 50);
			g[1] = new grid(260, 50);
			g[2] = new grid(420, 50);
			g[3] = new grid(100, 210);
			g[4] = new grid(260, 210);
			g[5] = new grid(420, 210);
			g[6] = new grid(100, 370);
			g[7] = new grid(260, 370);
			g[8] = new grid(420, 370);
			restart = false;
		}

		if (reset)
		{
			showHardwareMouse = true;
			drag = false;
			started = false;
			reset = false;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Space:
					if (started)
					{
						started = false;
						reset = true;
					}
					else
					{
						started = true;
						reset = false;
					}
					if (win)
					{
						restart = true;
					}
					break;
				}
				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					break;
				case sf::Mouse::Middle:
					break;
				case sf::Mouse::Right:
					break;
				}
				break;
			}

			case sf::Event::MouseMoved:
			{
				break;
			}

			case sf::Event::MouseButtonReleased:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					break;
				case sf::Mouse::Middle:
					break;
				case sf::Mouse::Right:
					break;
				}
				break;
			}
			}
		}
		if (started)
		{
		}

		if (!win)
		{
			g[change]->setH(p1, p2);
			window.draw(mainbg);
			if (g[change]->checkW() == false)
				window.draw(text);
			sf::Vector2i pointerPos = sf::Mouse::getPosition(window);

			for (int i = 0; i < 9; i++)
			{
				sf::RectangleShape highlight = createRectangle(160.0f, 160.0f);
				highlight.setOutlineColor(sf::Color::Black);
				highlight.setOutlineThickness(-2);
				highlight.setPosition(g[i]->getX() - 5, g[i]->getY() - 5);
				window.draw(highlight);
			}
			g[change]->drawH(window);
			for (int i = 0; i < 9; i++)
			{
				g[i]->draw(window);
			}
			g[change]->perform(window, p1, p2, pointerPos, done);
			if (done)
			{
				g[change]->checkW();

				if (!g[change]->checkW())
				{
					change = g[change]->getC();
				}
				else
				{
					win = true;
				}
			}
			done = false;
		}
		else if (win)
		{
			window.draw(mainbg);
			text.setString("Player " + playerw + " WON");
			window.draw(text);
			window.draw(textw);
			for (int i = 0; i < 9; i++)
			{
				sf::RectangleShape highlight = createRectangle(160.0f, 160.0f);
				highlight.setOutlineColor(sf::Color::Black);
				highlight.setOutlineThickness(-2);
				highlight.setPosition(g[i]->getX() - 5, g[i]->getY() - 5);
				window.draw(highlight);
				for (int i = 0; i < 9; i++)
				{
					g[i]->draw(window);
				}
			}
		}

		window.display();
	}

	return EXIT_SUCCESS;
}
