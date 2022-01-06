#include "Game.hpp"
#include "Entity.hpp"
#include "imgui.h"
#include "SFML/Graphics/RectangleShape.hpp"
Particle Game::parts;
int Game::shake = 0;
Entity * Game::player= nullptr;
Dijkstra Game::dij;
std::vector<sf::Vector2i> Game::walls;

void Game::particlesAt(sf::Vector2f pos) {
	int flip = (rand() % 2 == 0) ? 1 : -1;
	parts.create(pos.x, pos.y, flip * rand() % 200, - (rand() % 80) - 35);
}

void Game::init() {
	dij.dist[sf::Vector2i(0, 0)] = 1.0f;
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
	sf::RectangleShape rs(sf::Vector2f(Entity::stride, Entity::stride));
	rs.setOutlineThickness(1);
	rs.setOutlineColor(sf::Color::Red);
	for (auto& v : walls) {
		rs.setPosition(v.x * Entity::stride, v.y * Entity::stride);
		win.draw(rs);
	}
	if(player) player->draw(win);

	sf::RectangleShape rrs(sf::Vector2f(4, 4));
	rrs.setFillColor(sf::Color::Red);
	auto& g = dij.g;
	for( auto & v : g){
		rrs.setPosition(v.first.x * Entity::stride + 0.5 * Entity::stride, v.first.y * Entity::stride + 0.5 * Entity::stride);
		win.draw(rrs);
	}
}

static bool isColliding(int ccx, int ccy) {
	if (ccx < 0)
		return true;
	if (ccy < 0)
		return true;

	if (ccx >= 1280 / Entity::stride)
		return true;

	if (ccy >= 720 / Entity::stride)
		return true;

	for (auto& vi : Game::walls)
		if ((vi.x == ccx) && (vi.y == ccy))
			return true;

	return false;
}

void Dijkstra::compute(){
	g.clear();
	int maxCellW = Game::W / Entity::stride + 1;
	int maxCellH = Game::H / Entity::stride + 1;
	for( int y = 0; y < maxCellH;++y)
		for (int x = 0; x < maxCellW; ++x){
			if(!isColliding(x,y))
				g[sf::Vector2i(x, y)] = true;
		}
}