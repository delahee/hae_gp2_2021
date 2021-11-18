
#include "Entity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace sf;

void Entity::update(double dt) {
	auto pos = getPosition();
	pos.x += dx * dt;
	pos.y += dy * dt;
	spr->setPosition(pos);
}

void Entity::draw(sf::RenderWindow& win) {
	if(visible)
		win.draw(*spr);
}

void PlayerPad::update(double dt){
	Entity::update(dt);
	if (currentBall) {
		currentBall->dx = currentBall->dy = 0.0;
		currentBall->setPosition( spr->getPosition() + Vector2f(0,-4));
	}
}

void PlayerPad::draw(sf::RenderWindow& win){
	Entity::draw(win);

}
