#include "SFML/Graphics/RenderWindow.hpp"

#include "Entity.hpp"
#include "World.hpp"

void World::update(double dt){
	for (auto e : data)
		e->update(dt);
}

void World::draw(sf::RenderWindow& win)
{
	for (auto e : data)
		e->draw(win);
}