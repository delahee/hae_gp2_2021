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
		Vector2f predPos = e->getPosition();
		e->update(dt);
		if (e->type == PlayerObject) {
			pad = (PlayerPad*)e;
		}
		if (e->type == Wall) {
			for (int j = idx+1; j < data.size();++j) {
				auto oe = data[j];
				if (oe->type == Ball) {
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
