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

 void Int64Array::ensureNew(int size) {//s’assure que le tableau fait au moins size
	if (size < maxSize)
		return;
	int oldSize = maxSize;
	maxSize = size;
	int64_t* oldData = data;
	data = new int64_t[size];
	memcpy(data, oldData, oldSize * sizeof(int64_t));
	delete[]oldData;
	zero(oldSize, maxSize);
}

 void Int64Array::set(int pos, int64_t elem)//meme chose avec ensure voir throw si hors borne
 {
	 ensure(pos + 1);
	 data[pos] = elem;
	 if (pos >= curSize)
		 curSize = pos + 1;
 }

 int64_t& Int64Array::get(int pos) {
	 ensure(pos + 1);
	 if (pos >= curSize)
		 curSize = pos + 1;
	 return data[pos];
 }

 // a b c d ( inserer e en 0)
 // 0 a b c d
 // e a b c d

 void Int64Array::push_front(int64_t elem) {
	 //decaller vers la droite
	 //poser la valuer 
	 insert(0, elem);
 }

 void Int64Array::_shift_from_to(int end, int cur) {
	 if (cur <= end) return;
	 data[cur] = data[cur - 1];
	 _shift_from_to(end, cur - 1);
 }

 void Int64Array::shift_right(int pos) {
	 ensure(curSize + 1);
	 _shift_from_to(pos, curSize);
	 curSize++;
 }

 void Int64Array::insert(int pos, int64_t elem) {
	 //decaller de pos vers la droite
	 // 
	 shift_right(pos);
	 //poser la valeur
	 set(pos, elem);
 }

 //inserer l'élement en respectant la relation d'ordre data[a-1] < data[a]

 void Int64Array::insert_ordered(int64_t elem) {
	 int pos = search_position(0, elem);
	 insert(pos, elem);
 }

 void Int64Array::append_sorted(const int64_t* arr, int sz) {
	 if (sz <= 0) return;
	 insert_ordered(arr[0]);
	 append_sorted(arr + 1, sz - 1);
 }

 void Int64Array::load(const int64_t* arr, int sz) {
	 if (sz == 0)
		 return;
	 set(curSize, arr[0]);
	 load(arr + 1, sz - 1);
 }

 void Int64Array::insertionSort(const int64_t* arr, int sz) {
	 clear();
	 load(arr, sz);
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
