#ifndef _GRID
#define _GRID

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class grid
{
	int gridSize = 3;
	int gridCellSize = 50;
	int gridX;
	int gridY;
	int X;
	int Y;
	int gX;
	int gY;

public:
	sf::Texture cross;
	sf::Texture circle;
	sf::RectangleShape gri[3][3];
	sf::RectangleShape highlightCell = createRectangle(gridCellSize, gridCellSize);
	grid(int x, int y) : gridX(x), gridY(y)
	{
		for (int i = 0; i < gridSize; i++)
		{
			X = x;
			Y = y;
			for (int j = 0; j < gridSize; j++)
			{
				gri[i][j] = createRectangle(gridCellSize, gridCellSize, sf::Vector2f(gridX, gridY));
				gridX += gridCellSize;
			}

			gridY += gridCellSize;
			gridX = x;
		}

		if (!circle.loadFromFile("data/blue_circle.png"))
		{
		}
		if (!cross.loadFromFile("data/red_cross.png"))
		{
		}
	}
	sf::RectangleShape createRectangle(float width = 1.0f, float height = 1.0f, sf::Vector2f position = sf::Vector2f(0, 0),
									   const sf::Color &myFillColor = sf::Color::White,
									   const sf::Color &myOutlineColor = sf::Color::Black,
									   float myOutlineThickness = -2)
	{
		sf::RectangleShape myRectangle;
		sf::Vector2f myRectangleSize(width, height);
		myRectangle.setSize(myRectangleSize);
		myRectangle.setPosition(position);
		myRectangle.setFillColor(sf::Color(255, 255, 255));
		myRectangle.setOutlineColor(myOutlineColor);
		myRectangle.setOutlineThickness(myOutlineThickness);
		return myRectangle;
	}

	int getSize() { return gridSize; }
	int getX() { return X; }
	int getY() { return Y; }

	void draw(sf::RenderWindow &window)
	{

		for (int i = 0; i < getSize(); i++)
			for (int j = 0; j < getSize(); j++)
			{
				window.draw(gri[i][j]);
			}
	}

	void drawH(sf::RenderWindow &window)
	{
		sf::RectangleShape highlight = createRectangle(160.0f, 160.0f);
		highlight.setFillColor(sf::Color(0, 255, 0));
		highlight.setOutlineThickness(-2);
		highlight.setPosition(X - 5, Y - 5);
		window.draw(highlight);
	}

	void perform(sf::RenderWindow &window, bool &p1, bool &p2, sf::Vector2i &pointerPos, bool &done)
	{
		for (int i = 0; i < getSize(); i++)
		{
			for (int j = 0; j < getSize(); j++)
			{
				sf::FloatRect gridBounds = gri[i][j].getGlobalBounds();
				if (gridBounds.contains((sf::Vector2f)pointerPos))
				{
					highlightCell.setPosition(gri[i][j].getPosition());
					window.draw(highlightCell);
					if (p1)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							if (gri[i][j].getTexture() == false)
							{
								gri[i][j].setTexture(&circle);
								done = true;
								p2 = true;
								p1 = false;
								gX = i;
								gY = j;
							}
						}
					}
					else if (p2)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							if (gri[i][j].getTexture() == false)
							{
								gri[i][j].setTexture(&cross);
								done = true;
								p1 = true;
								p2 = false;
								gX = i;
								gY = j;
							}
						}
					}
				}
			}
		}
	}

	void setH(bool &p1, bool &p2)
	{

		if (!p2 && !checkW())
		{
			highlightCell.setTexture(&circle);
			highlightCell.setOutlineColor(sf::Color(0, 102, 0));
		}
		else if (!p1 && !checkW())
		{
			highlightCell.setTexture(&cross);
			highlightCell.setOutlineColor(sf::Color(0, 102, 0));
		}
	}

	bool checkW()
	{
		if (gri[0][0].getTexture() == &circle && gri[0][1].getTexture() == &circle && gri[0][2].getTexture() == &circle)
		{
			return true;
		}
		else if (gri[1][0].getTexture() == &circle && gri[1][1].getTexture() == &circle && gri[1][2].getTexture() == &circle)
		{
			return true;
		}
		else if (gri[2][0].getTexture() == &circle && gri[2][1].getTexture() == &circle && gri[2][2].getTexture() == &circle)
		{
			return true;
		}
		else if (gri[0][0].getTexture() == &circle && gri[1][0].getTexture() == &circle && gri[2][0].getTexture() == &circle)
		{
			return true;
		}
		else if (gri[0][1].getTexture() == &circle && gri[1][1].getTexture() == &circle && gri[2][1].getTexture() == &circle)
		{
			return true;
		}
		else if (gri[0][2].getTexture() == &circle && gri[1][2].getTexture() == &circle && gri[2][2].getTexture() == &circle)
		{
			return true;
		}
		else if (gri[0][0].getTexture() == &circle && gri[1][1].getTexture() == &circle && gri[2][2].getTexture() == &circle)
		{
			return true;
		}
		else if (gri[0][2].getTexture() == &circle && gri[1][1].getTexture() == &circle && gri[2][0].getTexture() == &circle)
		{
			return true;
		}
		else if (gri[0][0].getTexture() == &cross && gri[0][1].getTexture() == &cross && gri[0][2].getTexture() == &cross)
		{
			return true;
		}
		else if (gri[1][0].getTexture() == &cross && gri[1][1].getTexture() == &cross && gri[1][2].getTexture() == &cross)
		{
			return true;
		}
		else if (gri[2][0].getTexture() == &cross && gri[2][1].getTexture() == &cross && gri[2][2].getTexture() == &cross)
		{
			return true;
		}
		else if (gri[0][0].getTexture() == &cross && gri[1][0].getTexture() == &cross && gri[2][0].getTexture() == &cross)
		{
			return true;
		}
		else if (gri[0][1].getTexture() == &cross && gri[1][1].getTexture() == &cross && gri[2][1].getTexture() == &cross)
		{
			return true;
		}
		else if (gri[0][2].getTexture() == &cross && gri[1][2].getTexture() == &cross && gri[2][2].getTexture() == &cross)
		{
			return true;
		}
		else if (gri[0][0].getTexture() == &cross && gri[1][1].getTexture() == &cross && gri[2][2].getTexture() == &cross)
		{
			return true;
		}
		else if (gri[0][2].getTexture() == &cross && gri[1][1].getTexture() == &cross && gri[2][0].getTexture() == &cross)
		{
			return true;
		}
		else
			return false;
	}
	int getC()
	{
		int change = -1;
		if (gX == 0 && gY == 0)
			change = 0;
		else if (gX == 0 && gY == 1)
			change = 1;
		else if (gX == 0 && gY == 2)
			change = 2;
		else if (gX == 1 && gY == 0)
			change = 3;
		else if (gX == 1 && gY == 1)
			change = 4;
		else if (gX == 1 && gY == 2)
			change = 5;
		else if (gX == 2 && gY == 0)
			change = 6;
		else if (gX == 2 && gY == 1)
			change = 7;
		else if (gX == 2 && gY == 2)
			change = 8;
		return change;
	}
};

#endif
