#include "IntArray.hpp"
#include <utility>
#include <cstdlib>
#undef max
#undef min
void IntArray::set(int idx, int value) {
	//si idx est hors des bornes du tableau 
	//faire throw "exception:out of bounds";
	if ((idx < 0) || (idx >= size))
		throw "exception:out of bounds";

	//recuperer la donn?e a la case idx et l'affecter
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

	//d?livrer la memoire si besoin
}

void IntArray::insert(int value){
	int idx = 0;
	while( (idx < size) && (data[idx] < value)) 
		idx++;
	insertAt(idx, value);
}

void IntArray::insertAt(int idx, int value){
	using namespace std;

	int sz = size;
	resize(max(idx+1, size + 1));
	//resize(max(idx + 1, size + 1));

	for ( ; sz > idx; sz--)
		data[sz] = data[sz-1];
	data[idx] = value;
}

static int cmp(const void * v0, const void * v1) {
	return *(int*)v0 - *(int*)v1;
}

void IntArray::qsort() {
	::qsort(data, size, sizeof(int), cmp);
}

void IntArray::insertAtMove(int idx, int value) {
	int sz = size;
	resize(std::max<int>(idx + 1, size + 1));
	memmove(&data[idx+1], &data[idx], (sz - idx) * sizeof(int));
	data[idx] = value;
}

