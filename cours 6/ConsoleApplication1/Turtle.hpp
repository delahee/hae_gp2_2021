#pragma once
#include "SFML/Graphics/Transform.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Turtle {
public:
	sf::Transform		trs;
	sf::CircleShape		comps[3];
	sf::RectangleShape	dir;

	Turtle();
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};