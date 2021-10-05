#include "IntArray.hpp"

void IntArray::set(int idx, int value) {
	//si idx est hors des bornes du tableau 
	//faire throw "exception:out of bounds";
	if ((idx < 0) || (idx >= size))
		throw "exception:out of bounds";

	//recuperer la donnée a la case idx et l'affecter
	data[idx] = value;
}

void IntArray::resize(int newSize) {
	//si la taille d'allocation est suffisante
	if (size >= newSize)
		// 	   sortir
		return;
#ifdef MALLOC_VERSION
	data = (int*)realloc(data, newSize * sizeof(int));
	memset(data + size, 0, (newSize - size) * sizeof(int));
	//for (int i = size; i < newSize; i++) 
	//	data[i] = 0;
	size = newSize;
#else
	int* ndata = new int[newSize];
	//memcpy(ndata, data, size * sizeof(int));
	for (int i = 0; i < size; i++)
		ndata[i] = data[i];
	for (int i = size; i < newSize; i++)
		ndata[i] = 0;
	int* oldData = data;
	this->data = ndata;
	delete oldData;
	size = newSize;
#endif

	// 
	//sinon
	// soit utiliser realloc et basta ( si vous etes en malloc )
	// sot en new... reallou un tableau et copier la partie restante

	//délivrer la memoire si besoin
};
