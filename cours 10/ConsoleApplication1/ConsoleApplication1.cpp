
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
#include <SFML/Graphics/Shader.hpp>
#include "SFML/Graphics/Glsl.hpp"

#include "imgui.h"

#include "HotReloadShader.hpp"


#include "Tool.hpp"

#include "Curve.hpp"
#include "Particle.hpp"
#include "Entity.hpp"
#include "Game.hpp"

float clamp(float val, float a, float b) {
	if (val < a)
		val = a;
	if (val > b)
		val = b;
	return val;
}


sf::Shader g_MainShaderNoTex;
sf::Shader g_MainShaderTex;
HotReloadShader g_bgShader;

bool loadFile(const char* path, std::string& res) {
	FILE* f = 0;
	fopen_s(&f,path, "r");
	if (!f) return false;
	fseek(f, 0L, SEEK_END);
	size_t sz = ftell(f);
	res.resize(sz);
	fseek(f, 0L, SEEK_SET);
	size_t read = fread(res.data(), sz, 1, f);
	if (f) {
		fclose(f);
	}
	else
		return false;
	return true;
}
sf::Texture bg;

int main(){
	sf::RenderWindow window(sf::VideoMode(Game::W, Game::H), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);


	if( !sf::Shader::isAvailable()){
		cout << "shaders are not supported\n";
		return 1;
	}

	bg.loadFromFile("res/bg.jpg");
	std::string vertContent;
	std::string fragContent;

	bool vertOk = loadFile("res/simple.vert", vertContent);
	bool fragOk = loadFile("res/simple.frag", fragContent);

	if (!vertOk) {
		cout << "cannot load vert\n";
		return 1;
	}
	if (!fragOk) {
		cout << "cannot load frag\n";
		return 1;
	}

	fragContent = "#define HAS_UNIFORM_COLOR \\n" + fragContent;

	{
		cout << "loading g_MainShaderTex\n";
		string frag;
		bool fragOk = loadFile("res/trans.frag", frag);
		
		if (!g_MainShaderTex.loadFromMemory(vertContent.c_str(), frag.c_str())) {
			cout << "cannot load shaders with tex\n";
			return 1;
		}
	}
	{
		cout << "loading g_MainShaderNoTex\n";
		if (!g_MainShaderNoTex.loadFromMemory(vertContent.c_str(), fragContent.c_str())) {
			cout << "cannot load shaders without tex\n";
			return 1;
		}
	}

	g_bgShader.vtxPath = "res/bg.vert";
	g_bgShader.fragPath = "res/bg.frag";
	g_bgShader.eval();

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
	spr->setOrigin(spr->getSize().x * 0.5, spr->getSize().y);
	Game::init();
	Game::player = new Entity(spr, Game::W / Entity::stride *0.5, lround(Game::H / Entity::stride) -2);

	while (window.isOpen()){
		sf::Event event;

		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);
		bool shifIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

		while (window.pollEvent(event)){
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {

				if( shifIsPressed){
					auto cx = event.mouseButton.x / Entity::stride;
					auto cy = event.mouseButton.y / Entity::stride;

					auto& p = Game::currentPath;
					Game::currentPath.clear();
					sf::Vector2i start = sf::Vector2i(Game::player->cx, Game::player->cy);
					sf::Vector2i end = sf::Vector2i(cx, cy);

					sf::Vector2i cur = end;
					Game::currentPath.push_back(end);
					while(cur != start){
						auto pos = Game::dij.pred.find(cur);
						if( pos != Game::dij.pred.end()){
							cur = Game::dij.pred[cur];
							Game::currentPath.push_back(cur);
						}
						else {
							Game::currentPath.clear();
							break;
						}
					}
					std::reverse(p.begin(), p.end());
					Game::player->curPath = p;
				}
				else {
					auto cx = event.mouseButton.x / Entity::stride;
					auto cy = event.mouseButton.y / Entity::stride;

					int pos = -1;
					int idx = 0;
					for (auto& v : Game::walls) {
						if (v.x == cx && v.y == cy)
							pos = idx;
						idx++;
					}

					if (pos < 0)
						Game::walls.push_back(sf::Vector2i(cx, cy));
					else
						Game::walls.erase(Game::walls.begin() + pos);
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				if( event.key.code == sf::Keyboard::Enter){
					Game::dij.compute( sf::Vector2i( Game::player->cx,Game::player->cy) );
				}
			}
		}

		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
		if (mouseLeftIsPressed && !mouseLeftWasPressed) {
			
		}

		auto player = Game::player;
		float max_speed = 10;

		static bool wasPressedUp = false;

		if (mouseLeftIsPressed) 
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		////////////////////

		//CLEAR
		window.clear(sf::Color::Black);
		
		////////////////////
		//UPDATE
		auto dtms = ((int)(dt * 1000.0));
		auto ms = sf::milliseconds(dtms==0?1:dtms);

		static sf::Glsl::Vec4 colAdd = sf::Glsl::Vec4(0,0,0,0);
		static sf::Glsl::Vec4 colMul = sf::Glsl::Vec4(1, 1, 1, 1);

		float id[] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1,
		};
		static sf::Glsl::Mat4 colTrans = sf::Glsl::Mat4(
			id
		);


		ImGui::SFML::Update(window, ms);

		Game::im();

		if (ImGui::Begin("Shader", 0)) {
			if (ImGui::TreeNode("Add")) {
				ImGui::ColorEdit4("colAdd", &colAdd.x);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Mul")) {
				ImGui::ColorEdit4("colMul", &colMul.x);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Trans")) {
				ImGui::ColorEdit4("r", &colTrans.array[0]);
				ImGui::ColorEdit4("g", &colTrans.array[4]);
				ImGui::ColorEdit4("b", &colTrans.array[8]);
				ImGui::ColorEdit4("a", &colTrans.array[12]);
				ImGui::TreePop();
			}
		}
		ImGui::End();

		g_bgShader.update(dt);
		Game::update(dt);
		Game::parts.update(dt);


		////////////////////
		//DRAW

		sf::RectangleShape rectBg;
		rectBg.setTexture(&bg);
		rectBg.setSize(sf::Vector2f(1280, 720));
		auto v = sf::Glsl::Vec4(1.0f, 1.0f, 1.0f, 1.0f);

		{
			auto& sh = g_bgShader.sh;
			sh.setUniform("col", v);
			sh.setUniform("colAdd", colAdd);
			sh.setUniform("colMul", colMul);
			sh.setUniform("colTrans", colTrans);
			sf::RenderStates rs;
			rs.shader = &sh;
			window.draw(rectBg, rs);
		}

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