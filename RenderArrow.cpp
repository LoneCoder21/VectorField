#include "RenderArrow.h"

RenderArrow::RenderArrow()
{
	if (!tex.create(200, 200))
		std::cout << "texture creation failed\n";

	tex.clear(sf::Color::Red);
	tex.display();

	arrow.setTexture(tex.getTexture());
	arrow.setPosition(sf::Vector2f(0,0));
}