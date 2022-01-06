#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>


class Curve {
public:
	std::vector<float> px;
	std::vector<float> py;
	
	void clear() {
		px.clear();
		py.clear();
	};

	static inline float c(float p0, float p1, float p2, float p3, float t) {
		float q = 2.0f * p1;
		float t2 = t * t;

		q += (-p0 + p2) * t;
		q += (2.0f * p0 - 5.0f * p1 + 4 * p2 - p3) * t2;
		q += (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t2 * t;

		return 0.5f * q;
	}

	void addPoint(sf::Vector2f p) {
		px.push_back(p.x);
		py.push_back(p.y);
	};

	inline static int clamp(int v, int a, int b) {
		if (v < a) return a;
		if (v > b) return b;
		return v;
	}

	void draw(sf::RenderWindow&wnd){
		int a = clamp(5, 0, 8);
		int b = clamp(5, -3, 8);
		int c = clamp(5, -3, 4);
		int d = clamp(5, 6, 12);
		sf::VertexArray arr;
		arr.setPrimitiveType(sf::PrimitiveType::LineStrip);
		sf::Color col = sf::Color::Red;
		for (int i = 0; i < px.size(); ++i) {
			int im = clamp(i - 1, 0, px.size() - 1);
			int ip1 = clamp(i + 1, 0, px.size() - 1);
			int ip2 = clamp(i + 2, 0, px.size() - 1);
			sf::Vector2f p0 = sf::Vector2f(px[im],	py[im]);
			sf::Vector2f p1 = sf::Vector2f(px[i],	py[i]);
			sf::Vector2f p2 = sf::Vector2f(px[ip1], py[ip1]);
			sf::Vector2f p3 = sf::Vector2f(px[ip2], py[ip2]);
			for (int sub = 0; sub < 16; ++sub) {
				sf::Vector2f p(
					Curve::c(p0.x, p1.x, p2.x, p3.x, sub / 15.0f),
					Curve::c(p0.y, p1.y, p2.y, p3.y, sub / 15.0f));
				arr.append(sf::Vertex(sf::Vector2f(p.x, p.y), col));
			}
		}
		wnd.draw(arr);
	}
};