#include "Game.hpp"
#include "Entity.hpp"
#include "imgui.h"
#include "SFML/Graphics/RectangleShape.hpp"
Particle Game::parts;
int Game::shake = 0;
Entity * Game::player= nullptr;
std::vector<sf::Vector2i> Game::walls;

void Game::particlesAt(sf::Vector2f pos) {
	int flip = (rand() % 2 == 0) ? 1 : -1;
	parts.create(pos.x, pos.y, flip * rand() % 200, - (rand() % 80) - 35);
}

void Game::init() {
	walls.push_back(sf::Vector2i(5, 5));
}

void Game::im() {
	using namespace ImGui;
	static bool imOpened = true;
	if (Begin("Game", &imOpened)) {
		if (player) player->im();

	}
	End();
}
void Game::update(double dt) {
	if (player) player->update(dt);
}

void Game::render(sf::RenderWindow& win) {
	if(player) player->draw(win);

	sf::RectangleShape rs(sf::Vector2f(Entity::stride,Entity::stride));
	rs.setOutlineThickness(1);
	rs.setOutlineColor(sf::Color::Red);
	for (auto v : walls) {
		rs.setPosition(v.x * Entity::stride, v.y * Entity::stride);
		win.draw(rs);
	}

}