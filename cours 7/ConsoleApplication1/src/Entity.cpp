
#include "Entity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "imgui.h"
#include "Game.hpp"

using namespace sf;

void Entity::syncSprite(){
	px = (cx + rx) * stride;
	py = (cy + ry) * stride;
	spr->setPosition(px, py);
}

void Entity::im(){
	using namespace ImGui;

	bool modified = false;
	modified |= DragFloat("dx", &dx, 1);
	modified |= DragFloat("dy", &dy, 1);

	modified |= DragFloat("gy", &gy, 0.001f);

	modified |= DragFloat("frict_x", &frict_x, 0.01f);
	modified |= DragFloat("frict_y", &frict_y, 0.01f);

	modified |= DragFloat("cx", &cx, 1.0f);
	modified |= DragFloat("cy", &cy, 1.0f);
	modified |= DragFloat("rx", &rx, 0.05f);
	modified |= DragFloat("ry", &ry, 0.05f);
	Value("px", (float)px);
	Value("py", (float)py);
	if (modified) 
		syncSprite();
}

bool Entity::isColliding(int ccx, int ccy) {
	if (ccx < 0)
		return true;
	if (ccy < 0)
		return true;

	if (ccx >= 1280 / stride)
		return true;

	if (ccy >= 720 / stride)
		return true;

	for (auto& vi : Game::walls)
		if ( (vi.x == ccx) && (vi.y == ccy))
			return true;

	return false;
}

void Entity::update(double dt) {
	dy += gy * dt;
	rx += dt * dx;
	ry += dt * dy;

	dx *= pow(frict_x, dt * 60.0f);
	dy *= pow(frict_y, dt * 60.0f);

	while (rx >= 1) {
		if (isColliding(cx + 1, cy)) {
			dx = 0;
			rx = 0.9;
		}
		else {
			rx--;
			cx++;
		}
	}
	while (rx <= 0) {
		if (isColliding(cx - 1, cy)) {
			dx = 0;
			rx = 0.1; // - 2.3 -> - 0.3
		}
		else {
			rx++;
			cx--;
		}
	}

	while (ry >= 1) {
		if (isColliding(cx, cy+1)) {
			dy = 0;
			ry = 0.999f;
		}
		else {
			ry--;
			cy++;
		}
	}

	while (ry <= 0) {
		if (isColliding(cx, cy - 1)) {
			dy = 0.0f;
			ry = 0.1f;
		}
		else {
			ry++;
			cy--;
		}
	}
	syncSprite();
}

void Entity::draw(sf::RenderWindow& win) {
	if(visible)
		win.draw(*spr);
}

