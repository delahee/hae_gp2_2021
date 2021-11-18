
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Int64Array.hpp"
#include "Tool.hpp"
#include "List.hpp"
#include <algorithm>
#include "Tree.hpp"

#include "Curve.hpp"
#include "Particle.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "Turtle.hpp"


int main(){
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))	
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();
	
	bool mouseLeftWasPressed = false;

	Turtle turtle;

	turtle.trs.translate(400, 300);

	sf::Vector2i winPos = window.getPosition();
	while (window.isOpen()){
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			turtle.trs.rotate(2 * dt * 60);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			turtle.trs.rotate(-2 * dt * 60);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			turtle.trs.translate(0, -2 * dt * 60);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			turtle.trs.translate(0, 2 * dt * 60);
		}
		
		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		if (mouseLeftIsPressed && !mouseLeftWasPressed) {
			
		}

		if (mouseLeftIsPressed) 
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		////////////////////

		//CLEAR
		window.clear();
		
		////////////////////
		//UPDATE
		Game::parts.update(dt);
		turtle.update(dt);

		////////////////////
		//DRAW

		Game::parts.draw(window);

		turtle.draw(window);
		//ui
		window.draw(tDt);
		
		if (Game::shake > 0)
			window.setPosition(winPos + sf::Vector2i(0 + rand() % 5, 0 + rand() % 5));
		else
			window.setPosition(winPos);
		Game::shake--;

		window.display();
		tExitFrame = getTimeStamp();
	}

	return 0;
}