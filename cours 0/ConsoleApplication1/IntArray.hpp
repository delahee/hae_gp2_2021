#pragma once

class IntArray {
	int* data = nullptr;

public:
	IntArray() {
		//faire l'allocation dynamique de 'data' qui sera de taille "suffisamment grande"
		data = new int[65536];
	};

	void set(int idx, int value) {
		//recuperer la donnée a la case idx et l'affecter
		data[idx] = value;

		// ecriture pure ptr
		//*(data + idx) = value;
	};

	int get(int idx) {
		//recuperer la donnée a la case idx et la retourner
		return data[idx];
	};
};