#pragma once
#include "SFML/Graphics/Transform.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

enum CmdType {
	Advance,
	Rotate,
	PenUp,
	PenDown,
	PenColor,
};

struct Cmd {
	CmdType				type = Advance;
	float				maxDuration = 0.333f;
	float				timer = 0.0f;
	float				value = 0.0f;
	float				originalValue = 0.0f;
	sf::Color			col;
	Cmd*				next = nullptr;

	Cmd(CmdType t, float _value = 0.0) {
		type = t;
		value = _value;
		originalValue = value;
	};

	Cmd* append(Cmd* nu) {
		if (next == nullptr)
			next = nu;
		else
			next = next->append(nu);
		return this;
	};

	Cmd* popFirst() {
		Cmd* nu = next;
		delete this;
		return nu;
	};
};

class Turtle {
public:
	sf::CircleShape		comps[3];
	sf::RectangleShape	dir;
	sf::RenderTexture	rt;

	bool				penEnabled = false;
	sf::Color			penColor;

						Turtle();

	virtual void		update(double dt);
	virtual void		draw(sf::RenderWindow& win);

	//ajoute les cmds a la fin de la liste courante
	void				appendCmd(Cmd * cmd);

	void				translate(float value) { appendCmd(new Cmd(Advance, value)); };
	void				rotate(float value) { appendCmd(new Cmd(Rotate, value)); };

	void				setPen(bool value) { 
		if(value) 
			appendCmd(new Cmd(PenDown));
		else 
			appendCmd(new Cmd(PenUp));
	};

	void				setPenColor(sf::Color col) {
		auto colCmd = new Cmd(PenColor);
		colCmd->col = col;
		appendCmd(colCmd);
	};

protected:
	sf::Transform		trs;
	Cmd*				applyCmd(Cmd* cmd);
	Cmd*				applyCmdInterp(Cmd* cmd,double dt);
	Cmd*				cmds = nullptr;
};