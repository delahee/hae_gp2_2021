#include "Game.hpp"
#include "Entity.hpp"
#include "imgui.h"
Particle Game::parts;
int Game::shake = 0;
Entity * Game::player= nullptr;

void Game::particlesAt(sf::Vector2f pos) {
	int flip = (rand() % 2 == 0) ? 1 : -1;
	parts.create(pos.x, pos.y, flip * rand() % 200, - (rand() % 80) - 35);
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
}