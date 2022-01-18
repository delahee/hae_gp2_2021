#include "Game.hpp"
#include "Entity.hpp"
#include "imgui.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include <optional>
Particle Game::parts;
int Game::shake = 0;
Entity * Game::player= nullptr;
Dijkstra Game::dij;
std::vector<sf::Vector2i> Game::walls;
std::vector<sf::Vector2i> Game::currentPath;

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

	sf::VertexArray arr;
	arr.setPrimitiveType(sf::Lines);
	for( auto & p : dij.pred){
		sf::Vertex start;
		sf::Vertex end;
		start.color = sf::Color::Green;
		start.color.a = 127;
		end.color = start.color;

		start.position.x = (p.first.x + 0.5) * Entity::stride;
		start.position.y = (p.first.y + 0.5) * Entity::stride;

		end.position.x = (p.second.x + 0.5) * Entity::stride;
		end.position.y = (p.second.y + 0.5) * Entity::stride;

		arr.append(start);
		arr.append(end);
	}
	win.draw(arr);

	sf::VertexArray arrPath;
	arrPath.setPrimitiveType(sf::LinesStrip);
	for (auto& p : currentPath) {
		sf::Vertex start;
		start.color = sf::Color::Magenta;

		start.position.x = (p.x + 0.5) * Entity::stride;
		start.position.y = (p.y + 0.5) * Entity::stride;

		arrPath.append(start);
	}
	win.draw(arrPath);
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

std::optional<sf::Vector2i> Dijkstra::find_min(std::vector<sf::Vector2i> & q) {
	std::optional<sf::Vector2i>  res  = std::nullopt;
	float distMin = 1024 * 1024;
	for( auto& s : q){
		if( dist[s] < distMin){
			distMin = dist[s];
			res = s;
		}
	}
	return res;
}


void Dijkstra::init(const sf::Vector2i& start){
	for (auto& s : g) {
		dist[s.first] = 1024 * 1024;
		queue.push_back(s.first);
	}
	dist[start] = 0;
}

float len(const sf::Vector2i & s){
	return sqrt( s.y * s.y + s.x * s.x);
}

void Dijkstra::relax(sf::Vector2i& s1, sf::Vector2i& s2) {
	float d_s1s2 = len(s2 - s1);
	if( dist[s2] > (dist[s1] + d_s1s2) ) {
		dist[s2] = dist[s1] + d_s1s2;
		pred[s2] = s1;
	}
}

void Dijkstra::compute( const sf::Vector2i& start ){
	using namespace sf;
	g.clear();
	int maxCellW = Game::W / Entity::stride + 1;
	int maxCellH = Game::H / Entity::stride + 1;
	for( int y = 0; y < maxCellH;++y)
		for (int x = 0; x < maxCellW; ++x){
			if(!isColliding(x,y))
				g[sf::Vector2i(x, y)] = true;
		}
	queue.clear();
	dist.clear();
	pred.clear();
	init(start);
	while( !queue.empty()){
		std::optional<sf::Vector2i> s1 = find_min(queue);
		if (s1 == std::nullopt) 
			break;

		auto pos = std::find(queue.begin(), queue.end(),*s1);
			if(pos != queue.end())
		queue.erase(pos);
		sf::Vector2i dirs[] = {
			sf::Vector2i(0,1),
			sf::Vector2i(0,-1),
			sf::Vector2i(-1,0),
			sf::Vector2i(1,0),
		};
		for( int  i = 0; i < 4;++i){
			sf::Vector2i neighbor = *s1 + dirs[i];
			if(g.find(neighbor) != g.end())
				relax(*s1,neighbor);
		}
	}
	int here = 0;
}