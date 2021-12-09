
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <optional>
#include <algorithm>
#include <sys/stat.h>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "imgui.h"

#include "Tool.hpp"

#include "Curve.hpp"
#include "Particle.hpp"
#include "Entity.hpp"
#include "Game.hpp"

int main(){
	sf::RenderWindow window(sf::VideoMode(Game::W, Game::H), "SFML works!");
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);

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
	double timer = 0.0;

	ImGui::SFML::Init(window);

	sf::Vector2i winPos = window.getPosition();

	sf::RectangleShape* spr = new sf::RectangleShape(sf::Vector2f(12, 28));
	spr->setFillColor(sf::Color::Red);
	spr->setOutlineColor(sf::Color::Green);
	spr->setOutlineThickness(4);
	spr->setOrigin(spr->getSize().x*0.5, spr->getSize().y);
	Game::player = new Entity(spr, Game::W / Entity::stride *0.5, lround(Game::H / Entity::stride) -2);

	while (window.isOpen()){
		sf::Event event;

		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)){
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		if (mouseLeftIsPressed && !mouseLeftWasPressed) {
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			Game::player->rx -= 10 * 1.0f * dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			Game::player->rx += 10 * 1.0f * dt;
		}

		if (mouseLeftIsPressed) 
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		////////////////////

		//CLEAR
		window.clear(sf::Color::Black);
		
		////////////////////
		//UPDATE
		ImGui::SFML::Update(window, sf::milliseconds((int)(dt * 1000.0)));

		Game::im();

		Game::update(dt);
		Game::parts.update(dt);


		////////////////////
		//DRAW

		Game::parts.draw(window);
		Game::render(window);
		window.draw(tDt);
		
		/*
		if (Game::shake > 0)
			window.setPosition(winPos + sf::Vector2i(0 + rand() % 5, 0 + rand() % 5));
		else
			window.setPosition(winPos);
		Game::shake--;
		*/
		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();

		timer += dt;
	}

	return 0;
}