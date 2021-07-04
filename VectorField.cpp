#define _USE_MATH_DEFINES

#include "Graph.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <functional>

sf::Vector2f field(const sf::Vector2f& p)
{
	const float x = p.x, y = p.y;

	return sf::Vector2f(x * y, y + 1);
}

int main()
{
	const unsigned int W = 800;
	const unsigned int H = 800;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(W, H), "SFML works!", sf::Style::Default, settings);
	window.setFramerateLimit(60.f);

	std::vector<sf::RectangleShape> rects;
	rects.reserve(10);

	rects.push_back(sf::RectangleShape(sf::Vector2f(100, 100)));
	rects.back().setFillColor(sf::Color::Red);
	rects.back().setPosition(20, 20);

	rects.push_back(sf::RectangleShape(sf::Vector2f(100, 100)));
	rects.back().setFillColor(sf::Color::Red);
	rects.back().setPosition(450, 150);

	GraphPlotter mgraph(W,H,1,3, field, sf::Vector2f(2, 3));

	while (window.isOpen())
	{
		window.clear(sf::Color(128, 128, 128));

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}
		mgraph.draw(window);

		window.display();
	}
	return 0;
}
