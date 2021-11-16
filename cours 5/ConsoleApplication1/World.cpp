#include "SFML/Graphics/RenderWindow.hpp"

#include "Entity.hpp"
#include "World.hpp"

using namespace sf;
void World::update(double dt){
	if (audio == nullptr)
		audio = new Audio();

	PlayerPad* pad = nullptr;
	int idx = 0;
	for (auto e : data) {
		if (e->type == PlayerObject) {
			pad = (PlayerPad*)e;
		}
	}

	for (auto e : data) {
		Vector2f predPos = e->getPosition();

		e->lastGoodPosition = e->getPosition();

		e->update(dt);

		if (e->type == PlayerObject) {
			pad = (PlayerPad*)e;
		}
		if (e->type == Ball) {
			for (int j = 0; j < data.size();++j) {
				auto oe = data[j];
				if (oe->type == Wall) {
					collideWallBall(oe, e);
				}
			}
		}
		if (e->type == Ball) {
			for (int j = 0; j < data.size(); ++j) {
				auto oe = data[j];
				if (oe->type == Brick) {
					collideBrickBall(oe, e);
				}
			}
		}
		if ( (e->type == Ball) && (pad->currentBall == nullptr)) {
			for (int j = 0; j < data.size(); ++j) {
				auto oe = data[j];
				if (oe->type == PlayerObject) {
					collideBrickBall(oe, e);
				}
			}
		}
		idx++;
	}

	for (auto e : data) {
		e->lastGoodPosition = e->getPosition();
		if (e->type == Ball) {
			if (e->getPosition().y > 1024) {
				e->setPosition(pad->getPosition());
				pad->currentBall = e;
			};
		}
	}
}

void World::collideBrickBall(Entity* brick, Entity* ball) {
	sf::Vector2f pos = ball->getPosition();
	if (brick->getBoundingBox().contains(pos)) {
		auto oldPos = ball->lastGoodPosition;
		auto box = brick->getBoundingBox();
		if ((oldPos.y < box.top) || (oldPos.y > (box.top + box.height))) {
			ball->dy = -ball->dy;
		}
		else {
			ball->dx = -ball->dx;
		}
		ball->setPosition(ball->lastGoodPosition);
	}
}

void World::collideWallBall(Entity* wall, Entity* ball) {
	auto e = wall;
	auto oe = ball;
	if (e->getBoundingBox().contains(oe->getPosition())) {
		audio->ballPong.play();
		//determiner si le rebond est sur l'axe vert ou horiz
		oe->setPosition(oe->lastGoodPosition);
		if (e->spr->getGlobalBounds().width > e->spr->getGlobalBounds().height) {
			//mur haut bass
			oe->dy = -oe->dy;
		}
		else {
			//mur gauche droite
			oe->dx = -oe->dx;
		}
	}
}

void World::draw(sf::RenderWindow& win)
{
	for (auto e : data)
		e->draw(win);
}

Audio::Audio(){
	if (ballPongBuffer.loadFromFile("res/ball_pong.wav"))
		ballPong.setBuffer(ballPongBuffer); 
	if (gothBuffer.loadFromFile("res/loligoth.ogg"))
		goth.setBuffer(gothBuffer);
	goth.play();
	goth.setLoop(true);
}
