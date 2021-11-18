#pragma once
#include "Particle.hpp"

class Game {
public:
	static int			shake;
	static int			score;
	static Particle		parts;
	static void			particlesAt(sf::Vector2f pos);
};