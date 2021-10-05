#pragma once

#include <cstdlib>
#include <cstring>


//#define MALLOC_VERSION
class IntArray {
public:
	int* data = nullptr;
	int size = 0;
public:

	IntArray() {
		//faire l'allocation dynamique de 'data' qui sera de taille "suffisamment grande"
		//data = new int[size = 65535];

#ifdef MALLOC_VERSION
		data = (int*) malloc(65535 * sizeof(int) );
		memset(data, 0, 65535 * sizeof(int));
#else
		data = new int[size= 65535];
		memset(data, 0, 65535 * sizeof(int));
#endif
	};

	IntArray(int _size) {
#ifdef MALLOC_VERSION
		data = (int*)malloc(size * sizeof(int));
#else
		data = new int[size = _size];
#endif
		memset(data, 0, size * sizeof(int));
		this->size = size;
	};

	~IntArray() {
#ifdef MALLOC_VERSION
		free(data);
#else
		delete[]data;
#endif
	};

	void set(int idx, int value);

	void resize(int newSize);
	void insert(int value);
	void insertAt(int idx,int value);
	void insertAtMove(int idx,int value);

	int get(int idx) {
		//si idx est hors des bornes du tableau 
		//faire throw "exception:out of bounds";
		if( (idx < 0) || (idx >= size) )
			throw "exception:out of bounds";

		//recuperer la donnée a la case idx et la retourner
		return data[idx];
	};
};

