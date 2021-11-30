
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <optional>

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
#include <sys/stat.h>
#include "../../../../Users/david/AppData/Local/Temp/7zO06147E97/imgui-SFML.h"
#include "imgui.h"

static Turtle* t = nullptr;
static sf::Color clearColor(0, 0, 0, 255);
static bool toolsOpened = true;
static void showTools() {
	using namespace ImGui;
	if (Begin("My Tools", &toolsOpened)) {
		float f[4] = { 
			clearColor.r / 255.0f,
			clearColor.g / 255.0f,
			clearColor.b / 255.0f,
			clearColor.a / 255.0f,
		};
		ImVec4 col(clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f);
		if (ImGui::ColorEdit4("bg", f)) {
			clearColor.r = f[0]*255.0f;
			clearColor.g = f[1]*255.0f;
			clearColor.b = f[2]*255.0f;
			clearColor.a = f[3]*255.0f;
		}
	}
	if (t) {
		sf::Vector2f pos = t->getPosition();
		Value("x", pos.x);
		Value("y", pos.y);
		if (Button("Reset")) {
			t->reset();
		} SameLine();
		if (Button("Avance")) {
			t->translate(90);
		} SameLine();
		if (Button("Gauche")) {
			t->rotate(-25);
		}SameLine();
		if (Button("Droite")) {
			t->rotate(25);
		}
		Checkbox("pen state", &t->penEnabled);


		static Cmd* head = nullptr;
		//
		if (TreeNode("Commandes")) {
			//faire un bouton pour creer une nouvelle commande
			if (Button("+")) {
				auto p = new Cmd(Advance);
				p->value = p->originalValue = 50;
				if (nullptr == head)
					head = p;
				else
					head = head->append(p);
			}

			int idx = 0;
			ImGui::Separator();
			auto h = head;
			while (h) {
				PushID(idx);
				Value("idx", idx);
				static const char* items[] = {
					"Clear",
					"Advance",
					"Rotate",
					"PenUp",
					"PenDown",
					"PenColor",
				};
				if (Combo("Cmd type", (int*)&h->type, items, IM_ARRAYSIZE(items))) {
					if (h->type == Rotate)
						h->value = h->originalValue = 0;
				}
				Value("timer", h->timer);
				switch (h->type)
				{
				case CmdType::Clear:
					break;
				case PenDown:
				case PenUp:
					break;
				case PenColor: {
					auto& col = h->col;
					float fcol[4] = { col.r / 255.0f, col.g / 255.0f, col.b / 255.0f, col.a / 255.0f };
					if (ImGui::ColorEdit4("col", fcol)) {
						col.r = fcol[0] * 255.0f;
						col.g = fcol[1] * 255.0f;
						col.b = fcol[2] * 255.0f;
						col.a = fcol[3] * 255.0f;
					}
					break;
				}
				case Rotate: {
					float degToRad = 0.0174533;
					float deg = h->originalValue * degToRad;
					if (SliderAngle("value", &deg)) {
						h->value = h->originalValue = deg / degToRad;
					}
					break;
				}
				default:
					if (DragFloat("value", &h->originalValue)) {
						h->value = h->originalValue;
					}
					break;
				}
				NewLine();
				ImGui::Separator();
				h = h->next;
				idx++;
				PopID();
			}
			//pour chaque commande
			// pouvoir editer le type
			// pouvoir editer la valeur
			// pouvoir editer la couleur
			
			Separator();
			Cmd* tc = t->cmds;
			idx = 0;
			while (tc) {
				PushID(idx);
				Value("val", tc->value);
				tc = tc->next;
				idx++;
				PopID();
			}

			SameLine();
			if (Button("Run")) {
				if(head)t->appendCmd(head);
				head = nullptr;
				//passer le head a la tortues
			}
			SameLine();
			if (Button("Load")) {
				FILE* f = nullptr;
				fopen_s(&f, "res/manualsave.txt", "rb");
				if (f && !feof(f)) {
					const int maxLineSize = 256;
					char line[maxLineSize] = {};
					for (;;) {
						int64_t nb = 0;
						fscanf_s(f, "%s %lld\n", line, maxLineSize, &nb);
						std::string s = line;
						if (s == "Advance") {
							t->translate(nb);
						}
						else if (s == "Rotate") {
							t->rotate(nb);
						}
						else if (s == "PenUp") {
							t->setPen(false);
						}
						else if (s == "PenDown") {
							t->setPen(true);
						}
						else if (s == "PenColor") {
							t->setPenColor(sf::Color((unsigned int)nb));
						}
						else if (s == "Clear") {
							t->appendCmd(new Cmd(Clear));
						}
						if (feof(f))
							break;
					}
					fclose(f);
					head = t->cmds;
					t->cmds = nullptr;
				}
			}
			SameLine();

			if (Button("Save")) {
				//sauver le fichier
				FILE* f = nullptr;
				fopen_s(&f, "res/manualsave.txt", "wb");
				if (f&& head) {
					t->write(f, head);
					fflush(f);
					fclose(f);
				}
			}
			//bouton executer liste
			//bouton sauver liste
			//bouton charger liste
			TreePop();
		}
		

	}
	End();
}

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

	struct _stat st;

	if (_stat("res/cmd.txt", &st))
		throw "cannot read cmd file";

	__time64_t lastTime = st.st_mtime;
	double timer = 0.0;

	bool doReinterpret = false;

	Turtle turtle;

	//turtle.trs.translate(400, 300);
	//turtle.appendCmd(new Cmd(Advance, 250) );
	//turtle.appendCmd(new Cmd(Rotate, 90) );
	//turtle.appendCmd(new Cmd(Advance, 250));
	ImGui::SFML::Init(window);

	sf::Vector2i winPos = window.getPosition();
	while (window.isOpen()){
		sf::Event event;

		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)){
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
		}

		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			turtle.rotate( -2 * dt * 60);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			turtle.rotate( 2 * dt * 60);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			turtle.translate(2 * dt * 60);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			turtle.translate(-2 * dt * 60);
		}
		*/

		static bool penEnabled = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			penEnabled = !penEnabled;
			turtle.setPen(penEnabled);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) ) 
			turtle.setPenColor(sf::Color::Red);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2) ) 
			turtle.setPenColor(sf::Color::Green); 
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
			turtle.setPenColor(sf::Color::Blue);

		static bool enterWasPressed = false;
		if (doReinterpret|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !enterWasPressed) {
			FILE* f = nullptr;
			fopen_s(&f,"res/cmd.txt","rb");
			if (f && !feof(f)) {
				const int maxLineSize = 256;
				char line[maxLineSize] = {};
				for (;;) {
					int64_t nb = 0;
					fscanf_s(f, "%s %lld\n", line, maxLineSize, &nb );
					std::string s = line;
					if (s == "Advance") {
						turtle.translate(nb);
					}
					else if (s == "Rotate") {
						turtle.rotate(nb);
					}
					else if (s == "PenUp") {
						turtle.setPen(false);
					}
					else if (s == "PenDown") {
						turtle.setPen(true);
					}
					else if (s == "PenColor") {
						turtle.setPenColor( sf::Color((unsigned int) nb) );
					}
					else if (s == "Clear") {
						turtle.appendCmd(new Cmd(Clear));
					}
					if (feof(f))
						break;
				}
				fclose(f);
			}
			cout << "reinterpreting\n";
			enterWasPressed = true;
			doReinterpret = false;

			turtle.writeCommands("res/save.txt");
		}
		t = &turtle;
		enterWasPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);

		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		if (mouseLeftIsPressed && !mouseLeftWasPressed) {
			
		}

		if (mouseLeftIsPressed) 
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		if (timer > 0.1f) {
			_stat("res/cmd.txt", &st);

			if (lastTime < st.st_mtime) {
				//reinterpret
				doReinterpret = true;
				lastTime = st.st_mtime;
			}
			//reinterpreter
			timer = 0.0;
		}

		////////////////////

		//CLEAR
		window.clear(clearColor);
		
		////////////////////
		//UPDATE
		Game::parts.update(dt);
		turtle.update(dt);

		ImGui::SFML::Update(window, sf::milliseconds((int) (dt * 1000.0)));

		////////////////////
		//DRAW
		
		showTools();
		//ImGui::ShowDemoWindow();

		Game::parts.draw(window);

		turtle.draw(window);
		//ui
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