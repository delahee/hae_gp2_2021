#pragma once

#include <cstdlib>
#include <cstring>

class IntArray {
public:
	int* data = nullptr;
	int size = 0;
public:

	IntArray() {
		//faire l'allocation dynamique de 'data' qui sera de taille "suffisamment grande"
		//data = new int[size = 65535];
		data = (int*) malloc(65535 * sizeof(int) );
		memset(data, 0, 65535 * sizeof(int));
	};

	IntArray(int size) {
		//faire l'allocation dynamique de 'data' qui sera de taille "suffisamment grande"
		//data = new int[size];
		data = (int*)malloc(size * sizeof(int));
		memset(data, 0, size * sizeof(int));
		this->size = size;
	};

	~IntArray() {
		//liberer la m�moire allou�e par le constructeur
		//delete [] data;
		free(data);
	};

	void set(int idx, int value);;

	int get(int idx) {
		//si idx est hors des bornes du tableau 
		//faire throw "exception:out of bounds";
		if( (idx < 0) || (idx >= size) )
			throw "exception:out of bounds";

		//recuperer la donn�e a la case idx et la retourner
		return data[idx];
	};
};

