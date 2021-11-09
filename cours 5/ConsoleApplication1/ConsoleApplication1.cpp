
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Int64Array.hpp"
#include "Tool.hpp"
#include "List.hpp"
#include <algorithm>
#include <vector>
#include "Tree.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include "Curve.hpp"
#include "Bullet.hpp"

float catmull(float p0 , float p1 , float p2,float p3 , float t ) {
	auto q = 2.0f * p1;
	auto t2 = t * t;

	q += (-p0 + p2) * t;
	q += (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2;
	q += (-p0 + 3 * p1 - 3 * p2 + p3) * t2 * t;

	return 0.5f * q;
}

void drawMountain(sf::RenderWindow& window) {

	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);
	sf::Color col = sf::Color::Green;

	float baseline = 350;

	sf::Vector2f a(0, baseline+50);
	sf::Vector2f b(400, baseline-150);
	sf::Vector2f c(1100, baseline +32);
	sf::Vector2f d(window.getSize().x, baseline);
	col.a = 100;

	col = sf::Color::Magenta;
	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(a.x, a.x, b.x, c.x, t);
		float y = catmull(a.y, a.y, b.y, c.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}
	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(a.x, b.x, c.x, d.x, t);
		float y = catmull(a.y, b.y, c.y, d.y, t);
		arr.append(sf::Vertex( sf::Vector2f(x,y), col));
	}

	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(b.x, c.x, d.x, d.x, t);
		float y = catmull(b.y, c.y, d.y, d.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}
	window.draw(arr);
}

void drawGround(sf::RenderWindow& window) {
	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);
	sf::Color col = sf::Color::Yellow;

	float baseline = 600+60;

	sf::Vector2f a(0, baseline);
	sf::Vector2f b(window.getSize().x, baseline);

	arr.append(sf::Vertex(a, col));
	arr.append(sf::Vertex(b, col));

	window.draw(arr);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	sf::RectangleShape shape(sf::Vector2f(25,60));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(800, 600);

	sf::RectangleShape gun(sf::Vector2f(8, 32));
	gun.setFillColor(sf::Color(	0xFF,0x00,0x00));
	gun.setOrigin(4,0);
	gun.setPosition(800, 600);

	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))	
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);

	sf::CircleShape ptr(8);
	ptr.setFillColor(sf::Color::Cyan);
	ptr.setOrigin(4, 4);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	Bullet bullets;
	bool mouseLeftWasPressed = false;
	Curve c;
	while (window.isOpen()){
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		auto pos = shape.getPosition();
		float deltaX = dt * 160;
		float deltaY = dt * 160;
		bool keyHit = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			pos.x -= deltaX;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			pos.x += deltaX;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			pos.y -= deltaY;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			pos.y += deltaY;
			keyHit = true;
		}
		if(keyHit)
			shape.setPosition(pos);


		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		if (false) {
			if (mouseIsReleased) c.addPoint(mousePos);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) c.clear();
		}

		if (mouseLeftIsPressed && !mouseLeftWasPressed) {
			auto pos = gun.getPosition();
			auto dir = mousePos - pos;
			float dirLen = std::sqrt(dir.x * dir.x + dir.y * dir.y);
			sf::Vector2f dxy(1, 0);
			if (dirLen) {
				dxy = dir / dirLen;
			}
			dxy *= 60.0f * 3;
			bullets.create(pos.x, pos.y, dxy.x, dxy.y);
		}

		if (mouseLeftIsPressed) 
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		//calculate angle from char to mouse
		sf::Vector2f characterToMouse(
			mousePos.y - shape.getPosition().y,
			mousePos.x - shape.getPosition().x);

		float radToDeg = 57.2958;
		float angleC2M = atan2(characterToMouse.y, characterToMouse.x);
		gun.setRotation(-angleC2M * radToDeg);
		gun.setPosition(shape.getPosition() + sf::Vector2f(8, 16));
		///

		ptr.setPosition(mousePos);
		tDt.setString( to_string(dt)+" FPS:"+ to_string((int)(1.0f / dt)));
		
		////////////////////

		//CLEAR
		window.clear();
		
		////////////////////
		//UPDATE
		bullets.update(dt);

		////////////////////
		//DRAW
		drawMountain(window);

		bullets.draw(window);

		//game elems
		window.draw(shape);
		window.draw(gun);
		
		c.draw(window);
		window.draw(ptr);

		//ui
		window.draw(tDt);
		
		window.display();
		tExitFrame = getTimeStamp();
	}

	return 0;
}