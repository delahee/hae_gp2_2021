
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

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	sf::RectangleShape shape(sf::Vector2f(25,60));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(800, 600);

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
		float deltaX = dt * 40;
		float deltaY = dt * 40;
		bool keyHit = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			pos.x -= deltaX;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			pos.x += deltaX;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			pos.y -= deltaY;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			pos.y += deltaY;
			keyHit = true;
		}
		if(keyHit)
			shape.setPosition(pos);

		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (mouseLeftIsPressed && !mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		if (mouseIsReleased) 
			c.addPoint(mousePos);

		if (mouseLeftIsPressed) 
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			c.clear();
		}

		ptr.setPosition(mousePos);

		tDt.setString( to_string(dt)+" FPS:"+ to_string((int)(1.0f / dt)));
		window.clear();
		
		//game elems
		window.draw(shape);
		
		c.draw(window);
		window.draw(ptr);

		//ui
		window.draw(tDt);
		
		window.display();
		tExitFrame = getTimeStamp();
	}

	return 0;
}