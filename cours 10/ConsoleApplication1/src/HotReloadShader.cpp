#include "HotReloadShader.hpp"

void HotReloadShader::eval() {
	sf::Shader s;

	if (s.loadFromFile(vtxPath, fragPath)) {//check the shader compiles before loading it into main instance
		bool ok = sh.loadFromFile(vtxPath, fragPath);
		struct _stat stV;
		struct _stat stF;
		int err = _stat(vtxPath.c_str(), &stV);
		if( err ){
			std::cout << "cannot stat vtx shader\n";
			return;
		}
		_stat(fragPath.c_str(), &stF);
		if (err) {
			std::cout << "cannot stat frag shader\n";
			return;
		}
		lastLoaded = std::max<time_t>(stV.st_mtime,stF.st_mtime);
		std::cout << "evaled successfully\n";
	}
	else {
		std::cout << "cannot hot reload shader\n";
	}
}

void HotReloadShader::update(double dt) {
	timer += dt;

	if (timer > 0.1) {
		bool doEval = lastLoaded == 0;

		struct _stat stV;
		struct _stat stF;
		if (_stat(vtxPath.c_str(), &stV)) {
			return;//cannot eval time
		}
		else if (_stat(fragPath.c_str(), &stF)) {
			return;//cannot eval time
		}
		else {
			if ( (lastLoaded < stV.st_mtime) || (lastLoaded < stF.st_mtime))
				doEval = true;
		}

		if (doEval) {
			eval();
			lastLoaded = std::max<time_t>(stV.st_mtime, stF.st_mtime);
		}
		timer = 0.0;
	}
}
