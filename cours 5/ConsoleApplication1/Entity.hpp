#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

enum EType {
	PlayerObject,
	Brick,
	Wall,
	Ball,
};

class Entity {
public:
	sf::Shape*		spr = nullptr;
	EType			type;

	bool visible = true;
	float dx = 0.0f;
	float dy = 0.0f;

	Entity(EType type,sf::Shape* _spr) {
		spr = _spr;
	}

	~Entity() {
		if (spr) {
			delete spr;
			spr = nullptr;
		}
	}

	sf::Vector2f getPosition() {
		return spr->getPosition();
	}

	void setPosition(sf::Vector2f pos) {
		return spr->setPosition(pos);
	}

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};

class PlayerPad : public Entity {
public:

	Entity* currentBall = nullptr;

	PlayerPad(EType type, sf::Shape* _spr) : Entity(type, _spr) {

	}


	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};