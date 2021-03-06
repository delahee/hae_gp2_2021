
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
#include <SFML/Audio.hpp>

#include "Curve.hpp"
#include "Particle.hpp"
#include "Entity.hpp"
#include "World.hpp"
#include "Game.hpp"

//will contains our bricks


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

	float baseline = 450;

	sf::Vector2f a(0, baseline);
	sf::Vector2f b(window.getSize().x, baseline);

	arr.append(sf::Vertex(a, col));
	arr.append(sf::Vertex(b, col));

	window.draw(arr);
}

int main(){
	

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(120,16));
	shape->setFillColor(sf::Color::Green);
	shape->setPosition(800, 600);
	shape->setOrigin(60, 8);

	sf::RectangleShape gun(sf::Vector2f(4, 32));
	gun.setFillColor(sf::Color(0xFF, 0x00, 0x00));
	gun.setOrigin(2, 0);

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

	int ballSize = 6;
	sf::CircleShape* ballShape = new sf::CircleShape(ballSize);
	ballShape->setOrigin(ballSize, ballSize);
	ballShape->setOutlineThickness(2);
	ballShape->setFillColor(sf::Color::Yellow);
	ballShape->setOutlineColor(sf::Color::Red);

	PlayerPad* playerPad = new PlayerPad(EType::PlayerObject, shape);
	Entity* ball = new Entity(EType::Ball, ballShape);
	ball->setPosition(playerPad->getPosition());

	auto vWallShapeLeft = new sf::RectangleShape(sf::Vector2f(16, 2048));
	vWallShapeLeft->setOrigin(8, 0);
	vWallShapeLeft->setFillColor(sf::Color::Green);

	auto vWallShapeRight = new sf::RectangleShape(*vWallShapeLeft);

	Entity* leftWall = new Entity(EType::Wall, vWallShapeLeft);
	Entity* rightWall = new Entity(EType::Wall, vWallShapeRight);
	rightWall->setPosition(sf::Vector2f(1280, 0));

	auto vWallShapeTop = new sf::RectangleShape(sf::Vector2f(2048, 16));
	vWallShapeTop->setOrigin(0, 8);
	vWallShapeTop->setFillColor(sf::Color::Green);

	Entity* topWall = new Entity(EType::Wall, vWallShapeTop);
	topWall->setPosition(sf::Vector2f(0, 0));

	World world;
	world.data.push_back(topWall);
	world.data.push_back(rightWall);
	world.data.push_back(leftWall);
	world.data.push_back(playerPad);
	world.data.push_back(ball);
	
	for( int iy = 1; iy < 5;++iy)
		for (int ix = 0; ix < 14; ++ix) {
			if( ( rand() % 10 >5 ))
				continue;

			auto b = new sf::RectangleShape(sf::Vector2f(64, 24));
			auto szB = b->getSize();
			szB.x *= 0.5;
			szB.y *= 0.5;
			b->setOrigin(szB);
			b->setFillColor(sf::Color::Red);
			b->setOutlineColor(sf::Color::Green);
			b->setOutlineThickness(2);

			Entity* brick0 = new Entity(EType::Brick, b);
			sf::Vector2f pos;
			pos.x = ix * (brick0->getBoundingBox().width + 16) + 95;
			pos.y = iy * (brick0->getBoundingBox().height + 16) + 64;
			brick0->setPosition(pos);
			world.data.push_back(brick0);
		}

	playerPad->currentBall = ball;

	
	bool mouseLeftWasPressed = false;
	Curve c;

	sf::Texture bgTex;
	if (!bgTex.loadFromFile("res/bg.jpg")) {
		cout << "load texture failed\n";
	}

	int score = 0;
	sf::Text scoreTxt;
	scoreTxt.setPosition(48, 16);
	scoreTxt.setFont(fArial);
	scoreTxt.setFillColor(sf::Color::White);
	scoreTxt.setOutlineColor(sf::Color::Magenta);
	scoreTxt.setOutlineThickness(2);
	scoreTxt.setCharacterSize(45);

	sf::Vector2i winPos = window.getPosition();
	while (window.isOpen()){
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		auto pos = playerPad->getPosition();
		float deltaX = dt * 160 * 6;
		float deltaY = dt * 160 * 6;
		bool keyHit = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			pos.x -= deltaX;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			pos.x += deltaX;
			keyHit = true;
		}
		if (keyHit) {
			if (pos.x < 0)
				pos.x = 0;
			if (pos.x > window.getSize().x)
				pos.x = window.getSize().x;
			playerPad->setPosition(pos);
		}

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
			dxy *= 60.0f * 8;
			if (playerPad->currentBall) {
				auto ball = playerPad->currentBall;
				ball->dx = dxy.x;
				ball->dy = dxy.y;
				float push = 0.1;
				
				ball->setPosition( sf::Vector2f(ball->getPosition().x, playerPad->getPosition().y - 16));
			}
			playerPad->currentBall = nullptr;
		}

		if (mouseLeftIsPressed) 
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		//calculate angle from char to mouse
		sf::Vector2f characterToMouse(
			mousePos.y - shape->getPosition().y,
			mousePos.x - shape->getPosition().x);

		float radToDeg = 57.2958;
		float angleC2M = atan2(characterToMouse.y, characterToMouse.x);
		gun.setRotation(-angleC2M * radToDeg);
		gun.setPosition(shape->getPosition());
		ptr.setPosition(mousePos);
		//tDt.setString( to_string(dt)+" FPS:"+ to_string((int)(1.0f / dt)));
		
		scoreTxt.setString("SCORE :" + to_string(Game::score));

		////////////////////

		//CLEAR
		window.clear();
		
		////////////////////
		//UPDATE
		Game::parts.update(dt);
		world.update(dt);

		////////////////////
		//DRAW
		bgTex.setSmooth(true);

		sf::Sprite bgSpr;
		bgSpr.setTexture(bgTex);
		bgSpr.setScale(1.5, 1.5);

		window.draw(bgSpr);
		drawMountain(window);
		drawGround(window);

		world.draw(window);
		window.draw(gun);
		
		c.draw(window);
		window.draw(ptr);

		Game::parts.draw(window);

		//ui
		window.draw(tDt);
		window.draw(scoreTxt);
		
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