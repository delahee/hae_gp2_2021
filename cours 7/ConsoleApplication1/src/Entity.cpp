
#include "Entity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "imgui.h"

using namespace sf;

void Entity::syncSprite(){
	px = (cx + rx) * stride;
	py = (cy + ry) * stride;
	spr->setPosition(px, py);
}

void Entity::im(){
	using namespace ImGui;

	bool modified = false;
	modified |= DragFloat("cx", &cx, 1);
	modified |= DragFloat("cy", &cy, 1);
	modified |= DragFloat("rx", &rx, 0.05);
	modified |= DragFloat("ry", &ry, 0.05);
	Value("px", (float)px);
	Value("py", (float)py);
	if (modified) 
		syncSprite();
}

void Entity::update(double dt) {
	while (rx > 1) {
		//test coll gauche droite ?
		rx--;
		cx++;
	}
	while (rx < 0) {
		//test coll gauche droite ?
		rx++;
		cx--;
	}
	syncSprite();
}

void Entity::draw(sf::RenderWindow& win) {
	if(visible)
		win.draw(*spr);
}

