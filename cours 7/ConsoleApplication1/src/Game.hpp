#pragma once
#include "Particle.hpp"

class Game {
public:
	static int			shake;
	static Particle		parts;
	static void			particlesAt(sf::Vector2f pos);
};