#include "Particle.hpp"

Particle::Particle(){
	int t = 3;
	b = sf::CircleShape(t);
	b.setOutlineThickness(1);
	b.setFillColor(sf::Color::Yellow);
	b.setOutlineColor(sf::Color::Red);
	b.setOrigin(sf::Vector2f(t, t));
}

void Particle::create(float _px, float _py, float _dx, float _dy){
	for (int i = 0; i < px.size(); ++i) {
		if (!alive[i]) {
			px[i] = _px;
			py[i] = _py;
			dx[i] = _dx;
			dy[i] = _dy;
			alive[i] = true;
			return;
		}
	}
	px.push_back(_px);
	py.push_back(_py);
	dx.push_back(_dx);
	dy.push_back(_dy);
	alive.push_back(true);
}

void Particle::update(double dt) {
	for (int i = 0; i < px.size(); ++i) {
		if (alive[i]) {
			px[i] += dx[i] * dt;
			py[i] += dy[i] * dt;

			dy[i] += (9.0f * 50.0 ) * dt;

			if (
				(px[i] > 3000) || (px[i] < -100) ||
				(py[i] > 3000) || (py[i] < -100)
				) {
				alive[i] = false;
			}
		}
	}
}

void Particle::draw(sf::RenderWindow& win) {
	int idx = 0;
	const int sz = px.size();
	while (idx < sz) {
		if (alive[idx]) {
			b.setPosition(px[idx], py[idx]);
			win.draw(b);
		}
		idx++;
	}
}
