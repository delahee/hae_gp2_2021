#pragma once
#include "Particle.hpp"
#include "Entity.hpp"

class Game {
public:
	static inline const int W = 1280;
	static inline const int H = 720;
	static int			shake;
	static Particle		parts;

	static std::vector<sf::Vector2i> walls;

	static Entity*		player;
	static void			particlesAt(sf::Vector2f pos);
	static void			init();
	static void			im();
	static void			update(double dt);
	static void			render(sf::RenderWindow &win);
};