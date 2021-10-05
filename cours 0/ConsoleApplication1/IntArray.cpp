#include "IntArray.hpp"
#include <utility>

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
	size = newSize;
#else
	int* ndata = new int[newSize];
	memset(ndata, 0, newSize * sizeof(int));
	memcpy(ndata, data, size * sizeof(int));
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
}

void IntArray::insert(int value)
{
	//find the rightful index

	//insert at pos
	//insertAt(idx, value);

}

void IntArray::insertAt(int idx, int value){
	int sz = size;
	resize(std::max<int>(idx+1, size + 1));
	for ( ; sz > idx; sz--)
		data[sz] = data[sz-1];
	data[idx] = value;
}

void IntArray::insertAtMove(int idx, int value) {
	int sz = size;
	resize(std::max<int>(idx + 1, size + 1));
	memmove(&data[idx+1], &data[idx], (sz - idx) * sizeof(int));
	data[idx] = value;
}

