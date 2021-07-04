#include "RenderArrow.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <limits>
#include <array>

#pragma once

class GraphPlotter
{
private:
	int w, h;

	const int normal = 6;

	const int thick = normal;
	const int reduce = 50;

	int start;
	int amount;

	const int grid_thick = thick/4;

	sf::View view;

	sf::RectangleShape vert;
	sf::RectangleShape horiz;

	sf::RectangleShape gridx;
	sf::RectangleShape gridy;

	sf::RectangleShape line;

	sf::ConvexShape tri;

	RenderArrow arrow;

	sf::Font font;
	sf::Text text;

	sf::Vector2f field;
	sf::Color field_color;
	sf::Vector2f field_miman;
	std::function<sf::Vector2f(sf::Vector2f)> field_func;

	std::array<sf::Vertex, 4> grad_rect;

	void maxminfield();

	void drawTri(sf::RenderWindow& win);
	void drawGrid(sf::RenderWindow& win);
	void drawText(sf::RenderWindow& win);
	void drawField(sf::RenderWindow& win);
public:
	GraphPlotter(int w, int h, int start, int amount, std::function<sf::Vector2f(sf::Vector2f)> f1, const sf::Vector2f& f);

	void draw(sf::RenderWindow& win);
};