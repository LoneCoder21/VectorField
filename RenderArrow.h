#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <limits>
#include <array>

#pragma once

class RenderArrow
{
private:
	sf::RenderTexture tex;
	sf::Sprite arrow;

public:
	RenderArrow();
	sf::Sprite& getSprite() { return arrow; }
};