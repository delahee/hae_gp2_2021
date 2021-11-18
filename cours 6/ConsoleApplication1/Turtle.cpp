#include "Turtle.hpp"
#include "Tool.hpp"

Turtle::Turtle() {
	auto& bdy = comps[0];
	bdy = sf::CircleShape(48);
	bdy.setFillColor(sf::Color::Green);
	bdy.setOutlineColor(sf::Color::White);
	bdy.setOutlineThickness(2);
	bdy.setOrigin(48, 48);

	auto& leye = comps[1];
	leye = sf::CircleShape(8);
	leye.setFillColor(sf::Color::Black);
	leye.setOutlineColor(sf::Color::White);
	leye.setOutlineThickness(2);
	leye.setOrigin( cos(pi()*0.4) * 48 + 8, sin(pi() * 0.4) * 48 + 8);

	auto& reye = comps[2];
	reye = sf::CircleShape(8);
	reye.setFillColor(sf::Color::Black);
	reye.setOutlineColor(sf::Color::White);
	reye.setOutlineThickness(2);
	reye.setOrigin(cos(pi() * 0.6) * 48 + 8, sin(pi() * 0.6) * 48 + 8);
}

void Turtle::update(double dt)
{
	
}



void Turtle::draw(sf::RenderWindow & win){
	for (auto& c : comps)
		win.draw(c, trs);
	win.draw(dir, trs);
}