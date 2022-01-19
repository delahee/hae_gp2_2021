#include "SFML/Graphics/Shader.hpp"
#include <iostream>


class HotReloadShader{
public:
	sf::Shader	sh;

	std::string	vtxPath;
	std::string	fragPath;

	time_t		lastLoaded = 0;
	double		timer = 0.0;

	void eval();

	void update(double dt);
};