#include <cstring>
#include "Int64Array.hpp"

Int64Array::Int64Array(int size) {
	if (size < 0) size = 0;
	curSize = size;
	if (size <= 0)
		maxSize = 16;
	else
		maxSize = size;

	data = (int64_t*)malloc(maxSize * sizeof(int64_t));
	zero(0, maxSize);
}


void Int64Array::insert_ordered(int64_t elem) {
	int pos = search_position(0, elem);
	insert(pos, elem);
}

void Int64Array::set(int pos, int64_t elem)//meme chose avec ensure voir throw si hors borne
{
	ensure(pos + 1);
	data[pos] = elem;
	if (pos >= curSize)
		curSize = pos + 1;
}

void Int64Array::_shift_from_to(int end, int cur) {
	if (cur <= end) return;
	data[cur] = data[cur - 1];
	_shift_from_to(end, cur - 1);
}

void Int64Array::insertionSort(const int64_t* arr, int sz) {
	clear();
	loadIter(arr, sz);
	int j;
	for (int i = 0; i < curSize; i++) {
		j = i;
		while ((j > 0) && (data[j] < data[j - 1])) {
			int64_t tmp = data[j];
			data[j] = data[j - 1];
			data[j - 1] = tmp;
			j--;
		}
	}
}
void Int64Array::shift_right(int pos) {
	ensure(curSize + 1);
	_shift_from_to(pos, curSize);
	curSize++;
}

int64_t& Int64Array::get(int pos) {
	ensure(pos + 1);
	if (pos >= curSize)
		curSize = pos + 1;
	return data[pos];
}

void Int64Array::append_sorted(const int64_t* arr, int sz) {
	if (sz <= 0) return;
	insert_ordered(arr[0]);
	append_sorted(arr + 1, sz - 1);
}

void Int64Array::insert(int pos, int64_t elem) {
	//decaller de pos vers la droite
	// 
	shift_right(pos);
	//poser la valeur
	set(pos, elem);
}
void Int64Array::load(const int64_t* arr, int sz) {
	if (sz == 0)
		return;
	set(curSize, arr[0]);
	load(arr + 1, sz - 1);
}

void Int64Array::loadIter(const int64_t* arr, int sz) {
	ensure(sz);
	for (int i = 0; i < sz; ++i)
		set(i, arr[i]);
}

void Int64Array::zero(int idx, int nbElem) {
	memset(data + idx, 0, nbElem * sizeof(int64_t));
}

void Int64Array::ensure(int size) {//s’assure que le tableau fait au moins size
	if (size < maxSize)
		return;
	int oldSize = maxSize;
	maxSize = size * 1.75;
	data = (int64_t*)realloc(data, maxSize * sizeof(int64_t));
	zero(oldSize, maxSize - oldSize);
}

int Int64Array::bsearch(int64_t elem)
{
	return _bsearch(elem, 0, curSize - 1);
}

int Int64Array::bsearchIter(int64_t elem)
{
	int lo = 0;
	int hi = curSize + 1;
	for (;;) {
		if (lo > hi) return -1;
		if (data[lo] == elem) return lo;
		if (data[hi] == elem) return hi;
		int mid = (lo + hi) >> 1;
		if (data[mid] == elem) return mid;
		if (elem < data[mid]) {
			lo = lo + 1;
			hi = mid - 1;
		}
		else {
			lo = mid + 1;
			hi = hi -1;
		}
	}
}

int Int64Array::_bsearch(int64_t elem, int lo, int hi){
	//est ce qu'on a deja trouvé ?
	if (hi < lo)
		return -1;

	if (data[lo] == elem) return lo;
	if (data[hi] == elem) return hi;

	//est ce que la solution est au milieu
	int mid = (lo + hi) >> 1;
	if (data[mid] == elem) return mid;

	//si pas au milieu, chercher dans la premier moitié si pertinent
	if ( elem < data[mid]) 
		return _bsearch(elem, lo + 1, mid - 1);
	return _bsearch(elem,mid + 1, hi -1);
}

int64_t Int64Array::randValue()
{
	return rand() % (curSize - 1);
}

