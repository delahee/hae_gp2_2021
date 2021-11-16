#pragma once
#include <vector>
#include "Entity.hpp"

class World {
public:
	std::vector<Entity*> data;
	void update(double dt);
	void draw(sf::RenderWindow& win);

};

