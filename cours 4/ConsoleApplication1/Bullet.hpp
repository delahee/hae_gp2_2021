#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Bullet { 
public:
	sf::CircleShape b;

	std::vector<float>	px;
	std::vector<float>	py;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<bool>	alive;

	Bullet();

	void create(float px, float py, float dx, float dy);
	void update(double dt);

	void draw(sf::RenderWindow& win);
};