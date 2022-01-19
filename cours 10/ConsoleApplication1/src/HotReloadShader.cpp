#include "HotReloadShader.hpp"

void HotReloadShader::eval() {
	sf::Shader s;

	if (s.loadFromFile(vtxPath, fragPath)) {//check the shader compiles before loading it into main instance
		bool ok = sh.loadFromFile(vtxPath, fragPath);
		struct _stat st;
		int err = _stat(vtxPath.c_str(), &st);
		if( err ){
			std::cout << "cannot stat vtx shader\n";
			return;
		}
		_stat(fragPath.c_str(), &st);
		if (err) {
			std::cout << "cannot stat frag shader\n";
			return;
		}
		lastLoaded = st.st_mtime;
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

		struct _stat st;
		if (_stat(vtxPath.c_str(), &st)) {
			return;//cannot eval time
		}
		else {
			if (lastLoaded < st.st_mtime) {
				doEval = true;
			}
		}

		if (doEval) {
			eval();
		}
		timer = 0.0;
	}
}
