#include <SFML/Graphics.hpp>

#include "Turtle.hpp"
#include "Tool.hpp"



Turtle::Turtle() {
	auto& bdy = comps[0];
	bdy = sf::CircleShape(48);
	bdy.setFillColor(sf::Color::Green);
	bdy.setOutlineColor(sf::Color::White);
	bdy.setOutlineThickness(2);
	bdy.setOrigin(48, 48);

	auto& leye = comps[1];
	leye = sf::CircleShape(8);
	leye.setFillColor(sf::Color::Black);
	leye.setOutlineColor(sf::Color::White);
	leye.setOutlineThickness(2);
	leye.setOrigin( cos(pi()*0.4) * 48 + 8, sin(pi() * 0.4) * 48 + 8);

	auto& reye = comps[2];
	reye = sf::CircleShape(8);
	reye.setFillColor(sf::Color::Black);
	reye.setOutlineColor(sf::Color::White);
	reye.setOutlineThickness(2);
	reye.setOrigin(cos(pi() * 0.6) * 48 + 8, sin(pi() * 0.6) * 48 + 8);

	rt.create(2048, 2048);
	rt.clear(sf::Color(0,0,0,0));

	trs.translate(200,200);
	trs.rotate(180);
}

void Turtle::reset(){
	trs = sf::Transform::Identity;
	trs.translate(200, 200);
	trs.rotate(180);
	rt.clear(sf::Color(0, 0, 0, 0));

	while (cmds) {
		cmds = cmds->popFirst();
	}
}

void Turtle::update(double dt){
	//while (cmds) {
	//	applyCmd(cmds);
	//	cmds = cmds->popFirst();
	//}
	
	if( cmds )
	 cmds = applyCmdInterp(cmds,dt);
}

void Turtle::draw(sf::RenderWindow & win){
	for (auto& c : comps)
		win.draw(c, trs);
	win.draw(dir, trs);

	rt.display();

	sf::Sprite s;
	s.setTexture(rt.getTexture());
	win.draw(s);
}

void Turtle::appendCmd(Cmd* cmd){
	if (cmds) 
		cmds = cmds->append(cmd);
	else 
		cmds = cmd;
}

void Turtle::write(FILE* f, Cmd* cmd) {
	switch (cmd->type) {
	case Clear:		{ fprintf(f, "Clear\n"); break; }
	case Advance:	{ fprintf(f, "Advance %d\n", (int)cmd->value); break; }
	case Rotate:	{ fprintf(f, "Rotate %d\n", (int)cmd->value); break; }
	case PenUp:		{ fprintf(f, "PenUp\n"); break; }
	case PenDown:	{ fprintf(f, "PenDown\n"); break; }
	case PenColor:	{ fprintf(f, "PenColor %u\n", (unsigned int)cmd->col.toInteger()); break; }
	}
	if (cmd->next)
		write(f, cmd->next);
}

void Turtle::writeCommands(const char* fname){
	FILE* f=nullptr;
	fopen_s(&f,fname, "wb");
	if (f) {
		write(f, cmds);
		fflush(f);
		fclose(f);
	}
}

Cmd* Turtle::applyCmd(Cmd* cmd){
	switch (cmd->type){
		case Clear:
			reset();
			break;
		case Advance:	
			trs.translate(0,-cmd->value);
			if (penEnabled) {
				sf::CircleShape pen(8);
				pen.setFillColor(penColor);
				pen.setOrigin(8,8);
				pen.setPosition(trs.transformPoint(sf::Vector2f(0,0)));
				rt.draw(pen);
			}
			break;
		case Rotate:	trs.rotate(cmd->value); break; 
		case PenUp:		penEnabled = false; break;
		case PenDown:	penEnabled = true; break;
		case PenColor:
			penColor = cmd->col;
			break;
	default:
		break;
	}

	return nullptr;
}

Cmd* Turtle::applyCmdInterp(Cmd* cmd, double dt) {
	dt = 1.0f / 60.0f * 0.1;
	float ratio = cmd->timer / cmd->maxDuration;
	float speed = 1.0f/cmd->maxDuration;
	bool destroy = false;
	switch (cmd->type) {
	case Clear:
		destroy = true;
		break;
	case Advance:
		trs.translate(0, -cmd->value * dt * speed);
		if (penEnabled) {
			sf::CircleShape pen(8);
			pen.setFillColor(penColor);
			pen.setOrigin(8, 8);
			pen.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));
			rt.draw(pen);
		}
		break;
	case Rotate:	
		trs.rotate(cmd->value * dt * speed);
		break;
	case PenUp:		penEnabled = false; 
		destroy = true;
		break;
	case PenDown:	penEnabled = true; 
		destroy = true;
		break;
	case PenColor:
		penColor = cmd->col;
		destroy = true;
		break;
	default:
		destroy = true;
		break;
	}

	cmd->timer += dt;
	if (cmd->timer >= cmd->maxDuration)
		destroy = true;

	if (!destroy) {
		return cmd;
	}
	else {
		cmd = cmd->popFirst();
		return cmd;
	}
}
