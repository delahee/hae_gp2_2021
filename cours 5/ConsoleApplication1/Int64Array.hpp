#pragma once

#include <ctype.h>
#include <cstdlib>
#include <stdint.h>

class Int64Array {
public:
	int64_t* data = nullptr;

	int maxSize = 0;
	int curSize = 0;

	Int64Array(int size = 0);

	void zero(int idx, int nbElem);
	void ensure(int size);
	void ensureNew(int size);
	void set_unsafe(int pos, int64_t elem) {
		data[pos] = elem;
	};

	void set(int pos, int64_t elem);
	void push_back(int64_t elem) {
		set(curSize, elem);
	}

	int64_t& get(int pos);

	int64_t& operator[](int idx) {
		return get(idx);
	};

	void push_front(int64_t elem);

protected:
	void _shift_from_to(int end, int cur);
public:

	void shift_right(int pos);
	void insert(int pos, int64_t elem);

	int search_position(int idx, int elem) {
		if (idx >= curSize)
			return curSize;
		if (data[idx] >= elem) 
			return idx;
		return search_position(idx + 1, elem);
	}

	int searchIter(int64_t elem) {
		for (int i = 0; i < curSize; ++i)
			if (data[i] == elem)
				return i;
		return -1;
	};

	//inserer l'élement en respectant la relation d'ordre data[a-1] < data[a]
	void insert_ordered(int64_t elem);;

	void clear() {
		curSize = 0;
	}

	void append_sorted(const int64_t* arr, int sz);
	void load(const int64_t* arr, int sz);
	void loadIter(const int64_t* arr, int sz);
	void insertionSort(const int64_t* arr, int sz);

	int bsearch(int64_t elem);

	int bsearchIter(int64_t elem);

	int _bsearch(int64_t elem, int lo, int hi);

	int64_t randValue();

	~Int64Array() {
		free(data);
		data = nullptr;
		maxSize = 0;
		curSize = 0;
	};

protected :
};