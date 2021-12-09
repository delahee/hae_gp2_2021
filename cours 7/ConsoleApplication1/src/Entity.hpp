#pragma once

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Entity {
public:
	sf::Shape*		spr = nullptr;

	bool			visible = true;

	float			cx = 0.0f;
	float			cy = 0.0f;
	float			rx = 0.0f;
	float			ry = 0.0f;
	float			px = 0.0f;
	float			py = 0.0f;

	float			dx = 0.0f;
	float			dy = 0.0f;

	float			gy = 90;

	float			frict_x = 0.93f;
	float			frict_y = 0.93f;

	inline static const int	stride = 32;

	Entity(sf::Shape* _spr, float _cx, float _cy) {
		this->spr = _spr;
		cx = _cx;
		cy = _cy;
		syncSprite();
	}

	void			im();
	bool			isColliding(int _cx, int _cy);
	virtual void	update(double dt);
	virtual void	draw(sf::RenderWindow& win);
	void			syncSprite();
};
