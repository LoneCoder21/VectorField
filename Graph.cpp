#include "Graph.h"

#include "glm/glm.hpp"

float length(sf::Vector2f vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float sign(float p)
{
	if (p == 0.0f) return 0.0f;
	if (p  < 0.0f) return -1.0f;

	return 1.0f;
}

void GraphPlotter::maxminfield()
{
	float amt = amount + 1;
	float pw = float(gridy.getSize().y / 2) / amt;

	int imat = start * amount;

	field_miman.x = std::numeric_limits<float>::max();
	field_miman.y = 1.0f;

	for (int i = 0; i < amt * 2 - 1; ++i, imat -= start)
	{
		int fmat = -start * amount;
		for (int f = 0; f < amt * 2 - 1; ++f, fmat += start)
		{
			sf::Vector2f xy = sf::Vector2f(fmat, imat);
			sf::Vector2f vec = field_func(xy);

			float len = length(vec);

			field_miman.x = std::min(len, field_miman.x);
			field_miman.y = std::max(len, field_miman.y);
		}
	}
}

void GraphPlotter::drawTri(sf::RenderWindow& win)
{
	for (int i = 0, rot = -90; i < 4; ++i, rot+=90) 
	{
		float x = w * sign(std::max(0, i - 1));
		float y = h * (!(i % 3));
		
		tri.setScale(1.0f,1.0f);
		tri.setRotation(rot);
		tri.setPosition(sf::Vector2f(x, y));

		win.draw(tri);
	}
}

void GraphPlotter::drawGrid(sf::RenderWindow& win)
{
	float amt = amount + 1;
	float pw = float(gridy.getSize().y / 2) / amt;

	gridy.setPosition(sf::Vector2f(w/2, reduce));
	gridx.setPosition(sf::Vector2f(reduce, h/2));

	for (int i = 0; i < amt-1; ++i)
	{
		gridy.move(sf::Vector2f(pw, 0));
		gridx.move(sf::Vector2f(0, pw));

		win.draw(gridx);
		win.draw(gridy);
	}

	gridy.setPosition(sf::Vector2f(w / 2, reduce));
	gridx.setPosition(sf::Vector2f(reduce, h / 2));

	for (int i = 0; i < amt-1; ++i)
	{
		gridy.move(sf::Vector2f(-pw, 0));
		gridx.move(sf::Vector2f(0, -pw));

		win.draw(gridx);
		win.draw(gridy);
	}
}

void GraphPlotter::drawText(sf::RenderWindow& win)
{
	text.setFillColor(sf::Color::White);

	sf::FloatRect gb = text.getGlobalBounds();

	float csize = thick * 3.5;
	text.setOrigin(sf::Vector2f(gb.width/2, gb.height / 2));
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(csize/8);

	float amt = amount + 1;
	float pw = float(gridy.getSize().y / 2) / amt;

	int smat = -start * amount;

	text.setCharacterSize(csize);

	text.setString("0");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2));
	text.setPosition(sf::Vector2f(w/2 - text.getGlobalBounds().width/2 - thick/2, h/2 + text.getGlobalBounds().height/2));
	win.draw(text);
	
	for (int i = 0; i < amt * 2-1; ++i, smat += start)
	{
		text.setString(std::to_string(smat));
		gb = text.getGlobalBounds();
		text.setOrigin(sf::Vector2f(gb.width / 2, gb.height / 2));

		float prod = pw * (smat / start);

		if (smat)
		{
			text.setPosition(sf::Vector2f(w / 2 + prod - gb.width / 2, h / 2 + gb.height / 2));
			win.draw(text);

			text.setPosition(sf::Vector2f(w / 2 - gb.width / 2 - thick/2, h + reduce/2 - thick/2 - ( h / 2 + prod + gb.height / 2)));
			win.draw(text);
		}
	}
}

void GraphPlotter::drawField(sf::RenderWindow& win)
{
	float amt = amount + 1;
	float pw = float(gridy.getSize().y / 2) / amt;
	
	line.setPosition(w/2- pw * amt,h/2 - pw * amt);

	int imat = start * amount;

	for (int i = 0; i < amt*2 - 1; ++i, imat-=start)
	{
		line.move(0, pw);
		int fmat = -start * amount;
		
		for (int f = 0; f < amt * 2 - 1; ++f, fmat+=start)
		{
			line.move(pw, 0);

			sf::Vector2f xy =  sf::Vector2f(fmat,imat);
			sf::Vector2f vec = field_func(xy);

			vec.x = (!vec.x) ? 0 : vec.x;
			vec.y = (!vec.y) ? 0 : vec.y;

			float angle = glm::degrees(atan(vec.y / vec.x));

			angle += -sign(std::min(0.0f, vec.x)) * 180;
			line.setRotation(360 - angle);

			float c = (length(vec) / field_miman.y);
			line.setFillColor(sf::Color(c * field_color.r, c * field_color.g, c * field_color.b));

			win.draw(line);
		}
		line.setPosition(w / 2 - pw * amt, line.getPosition().y);
	}
	view.setViewport(sf::FloatRect(0,0,1,1));
	win.setView(view);

	text.setString("Magnitude");
	text.setPosition(sf::Vector2f(start * amt + pw - 10, h - h * (1 - 0.85f)));

	float xw = start * amt + pw - 20, yh = h - h * (1 - 0.85f) + 20;
	float sw = 200, sh = 20;

	grad_rect[0] = sf::Vertex(sf::Vector2f(xw, yh), sf::Color::Black);
	grad_rect[1] = sf::Vertex(sf::Vector2f(xw, sh+yh), sf::Color::Black);
	grad_rect[2] = sf::Vertex(sf::Vector2f(xw+sw, sh+yh), field_color);
	grad_rect[3] = sf::Vertex(sf::Vector2f(xw+sw, yh), field_color);

	win.draw(text);
	text.setString(std::to_string((int)field_miman.x));
	text.move(0, yh-text.getPosition().y + sh + text.getLocalBounds().width);
	win.draw(text);

	text.setString(std::to_string((int)ceil(field_miman.y)));
	text.move(sw - text.getLocalBounds().width, 0);
	win.draw(text);

	win.draw(grad_rect.data(), 4, sf::Quads);

	view.setViewport(sf::FloatRect((1.0f - .85f) / 2, 0.f, .85f, .85f));
	win.setView(view);
}

GraphPlotter::GraphPlotter(int w, int h, int start, int amount, std::function<sf::Vector2f(sf::Vector2f)> field_func, const sf::Vector2f& field) 
	:
	w(w), h(h), start(start), amount(amount), 
	vert(sf::Vector2f(thick, w - reduce * 2)), 
	horiz(sf::Vector2f(h - reduce * 2, thick)), field_func(field_func), field(field),
	gridx(sf::Vector2f(h - reduce * 2, grid_thick)), 
	gridy(sf::Vector2f(grid_thick, w - reduce * 2)), 
	line(sf::Vector2f(50,thick*1.5)),
	view(sf::FloatRect(0, 0, w, h))
{
	vert.setFillColor(sf::Color::White);
	horiz.setFillColor(sf::Color::White);
	gridy.setFillColor(sf::Color::White);
	gridx.setFillColor(sf::Color::White);
	line.setFillColor(sf::Color::Black);

	vert.setOrigin(sf::Vector2f(thick/2,0));
	horiz.setOrigin(sf::Vector2f(0, thick/2));
	gridy.setOrigin(sf::Vector2f(grid_thick / 2, 0));
	gridx.setOrigin(sf::Vector2f(0, grid_thick / 2));
	line.setOrigin(sf::Vector2f(0, thick / 2));

	vert.setPosition(sf::Vector2f(w/2,reduce));
	horiz.setPosition(sf::Vector2f(reduce,h/2));

	line.setPosition(sf::Vector2f(w/2,h/2));

	field_color = sf::Color::Red;

	tri.setPointCount(3);
	tri.setFillColor(sf::Color::Black);

	if (!font.loadFromFile("C://Windows//Fonts//arial.ttf"))
	{
		std::cout << "Font failed to load\n";
	}

	text.setFont(font);

	int tw=2, th = 5;

	tri.setPoint(0, sf::Vector2f(w/2 - tw*thick/2, reduce));
	tri.setPoint(1, sf::Vector2f(w/2, reduce - thick*th));
	tri.setPoint(2, sf::Vector2f(w / 2 + tw*thick/2, reduce));

	maxminfield();
}

void GraphPlotter::draw(sf::RenderWindow& win)
{
	drawGrid(win);

	win.draw(vert);
	win.draw(horiz);

	drawTri(win);

	drawText(win);
	
	drawField(win);
}