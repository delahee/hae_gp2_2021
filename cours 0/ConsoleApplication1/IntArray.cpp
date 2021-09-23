#include "IntArray.hpp"

void IntArray::set(int idx, int value) {
	//si idx est hors des bornes du tableau 
	//faire throw "exception:out of bounds";
	if ((idx < 0) || (idx >= size))
		throw "exception:out of bounds";

	//recuperer la donnée a la case idx et l'affecter
	data[idx] = value;
}
