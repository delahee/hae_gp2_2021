#pragma once

#include <ctype.h>
#include <cstdlib>
#include <stdint.h>

class Int64Array {
public:
	int64_t* data = nullptr;

	int maxSize = 0;
	int curSize = 0;

	Int64Array( int size = 0) {
		if (size < 0) size = 0;
		curSize = size;
		if (size <= 0)
			maxSize = 16;
		else
			maxSize = size;

		data = (int64_t *) malloc(maxSize * sizeof(int64_t));

		zero(0, maxSize);
	}

	void zero(int idx, int nbElem) {
		if (idx >= nbElem)
			return;
		data[idx] = 0;
		zero(idx + 1, nbElem);
	};

	void ensure(int size) {//s’assure que le tableau fait au moins size
		if (size < maxSize)
			return;
		int oldSize = maxSize;
		maxSize = size;
		data = (int64_t*)realloc(data,maxSize * sizeof(int64_t));
		zero(oldSize, maxSize);
	}

	void ensureNew(int size) {//s’assure que le tableau fait au moins size
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

	void set_unsafe(int pos, int64_t elem) {
		data[pos] = elem;
	};

	void set(int pos, int64_t elem)//meme chose avec ensure voir throw si hors borne
	{
		ensure(pos + 1);
		data[pos] = elem;
		if (pos >= curSize)
			curSize = pos + 1;
	};

	void push_back(int64_t elem) {
		set(curSize, elem);
	}

	int64_t& get(int pos) {
		ensure(pos+1);
		if( pos >= curSize )
			curSize = pos + 1;
		return data[pos];
	}

	int64_t& operator[](int idx) {
		return get(idx);
	};

	void push_front(int64_t elem) {
		//decaller vers la droite
		//poser la valuer 
		insert(0, elem);
	}

	void shift_right(int pos) {
		
	}
	// a b c d ( inserer e en 0)
	// 0 a b c d
	// e a b c d
	void insert(int pos, int64_t elem) {
		//decaller de pos vers la droite
		// 
		shift_right(pos);
		//poser la valeur
		set(pos, elem);
	}

	void insert_ordered(int pos, int64_t elem) {

	}

	~Int64Array() {
		free(data);
		data = nullptr;
		maxSize = 0;
		curSize = 0;
	};

};