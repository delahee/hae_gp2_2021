
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Int64Array.hpp"
#include "Tool.hpp"

int StrLen(const char* str) {
	if (str == nullptr) return 0;
	if (str[0] == '\0') return 0;
	return 1 + StrLen(str+1);
}

const char* StrChr(const char* dst, char c) {
	if (dst == nullptr) return nullptr;
	if (dst[0] == 0) return nullptr;
	if (dst[0] == c )
		return dst;
	return StrChr( dst+1,c);
}


void StrCpy(char* dst, const char* src) {
	if (src == nullptr) return;
	if (dst == nullptr) return;
	if (src[0] == 0) {
		dst[0] = 0;
		return;
	}
	//on test pas si dest[0] = 0 parce qu'on veut l'ecraser
	dst[0] = src[0];
	StrCpy(dst + 1, src + 1);
}

void StrCat(char* dst, const char* src) {
	if (dst == nullptr) return;
	if (src == nullptr) return;

	if (dst[0] == 0)
		StrCpy(dst, src);
	else
		return StrCat(dst + 1, src);
}

int StrCmp(const char* a, const char* b) {
	if ( (a == nullptr) && (b == nullptr)) return 0;
	if ( (*a == 0) && (*b == 0)) return 0;

	if (*b == 0) {
		//a n est pas vide
		return 1;
	}

	if (*a == 0) {
		//src n'est pas vide
		return -1;
	}

	//aucun des deux est vide
	if (*a == *b) {
		return StrCmp(a + 1, b + 1);
	}
	else if (*a < *b) {
		return -1;
	}
	else //*a > *b
		return 1;
}

const char* StrStr(const char* str, const char* pattern) {
	if (str == nullptr) return nullptr;
	if (*str == 0) return nullptr;
	if (0 == StrCmp(str, pattern))
		return str;
	else
		return StrStr(str + 1, pattern);
}


int mainStr(){
	const char* null = nullptr;
	const char* empty = "";
	const char* longOne = "lorem ipsum";

	printf("%d %d %d", 
		StrLen(null), 
		StrLen(empty), 
		StrLen(longOne));

	if (StrChr(null, 'e')) throw "exception";
	if (StrChr(empty, 'e')) throw "exception";
	if (StrChr(longOne, 'z')) throw "exception";
	if (!StrChr(longOne, 'm'))	throw "exception";

	if ( 0 != StrCmp(longOne, "lorem ipsum"))	throw "exception";
	if ( 1!=  StrCmp(longOne, "lorem"))	throw "exception";
	if ( -1!=  StrCmp(longOne, "lorem ipsum ipsum"))	throw "exception";

	char* zoneQuonPeutEcrire = (char*) malloc(150);
	zoneQuonPeutEcrire[0] = 0;

	StrCpy(zoneQuonPeutEcrire, null);
	StrCpy(zoneQuonPeutEcrire, empty);
	StrCpy(zoneQuonPeutEcrire, longOne);

	zoneQuonPeutEcrire[0] = 0;
	StrCat(zoneQuonPeutEcrire, "sapin");
	StrCat(zoneQuonPeutEcrire, "sympa");
	return 0;
}

int main() {
	Int64Array arr(4);
	arr.ensure(8);

	Int64Array s;
	s.set(4, 6);
	if (s.curSize != 5)throw"exception";
	s.set(5, 6);
	if (s.curSize != 6)throw"exception";
	s.push_back(66);

	Int64Array t;
	for (int i = 0; i < 4; ++i)
		t[i] = i * i;

	Int64Array ti;
	ti.insert(0, 1);
	ti.insert(0, 2);
	ti.insert(0, 3);
	ti.insert(0, 4);
	ti.insert(0, 5);

	Int64Array ti1;
	ti1.insert(0, 1);
	ti1.insert(0, 2);
	ti1.insert(0, 3);
	ti1.insert(2, 5);
	ti1.insert(1, 6);
	ti1.insert(0, 7);

	Int64Array ti2;
	ti2.insert_ordered(666);
	ti2.insert_ordered(66);
	ti2.insert_ordered(6);
	ti2.insert_ordered(6666);
	ti2.insert_ordered(5);
	ti2.insert_ordered(10);
	{
		int idx0 = ti2.bsearch(118000);
		int idx1 = ti2.bsearch(5);
		int idx2 = ti2.bsearch(10);
		int idx3 = ti2.bsearch(66);
		int idx4 = ti2.bsearch(666);
		int here = 0;
	}


	int64_t tt[] = {448668,48,64,46,486,846,46,1646,16};
	int sz = sizeof(tt) / sizeof(int64_t);
	Int64Array ti3;
	ti3.append_sorted(tt,sz);

	Int64Array ti4;
	ti4.load(tt,8);

	Int64Array ti5;
	ti5.insertionSort(tt, sz);

	srand(0);
	Int64Array ti6;

	{
		double t0 = getTimeStamp();
		for (int i = 0; i < 8; ++i) {
			ti6.push_back(rand() % 11353453);
		}
		ti6.push_back(667789);
		double t1 = getTimeStamp();
		printf("time elapsed %llf s\n", (t1 - t0));
	}

	/*
	{
		double t0 = getTimeStamp();
		Int64Array tiAppend;
		tiAppend.append_sorted(ti6.data, ti6.curSize);
		double t1 = getTimeStamp();
		printf("time elapsed tappend %llf s\n", (t1 - t0));
	}
	*/
	
	double t0 = getTimeStamp();
	Int64Array tiSort;
	tiSort.insertionSort(ti6.data, ti6.curSize);
	double t1 = getTimeStamp();
	printf("time elapsed tsort %llf s\n", (t1 - t0));
	{
		int pos = ti6.bsearch(667789);
		int here = 0;
	}

	int nb = 50000;

	{
		double t0 = getTimeStamp();
		for (int i = 0; i < nb; ++i) {
			int64_t elem = ti6.randValue();
			volatile int pos = ti6.searchIter(elem);
		}
		double t1 = getTimeStamp();
		printf("time elapsed for lin search %llf s\n", (t1 - t0));
	}

	{
		double t0 = getTimeStamp();
		for (int i = 0; i < nb; ++i) {
			int64_t elem = ti6.randValue();
			volatile int pos = ti6.bsearch(elem);
		}
		double t1 = getTimeStamp();
		printf("time elapsed for bsearch rec %llf s\n", (t1 - t0));
	}

	{
		double t0 = getTimeStamp();
		for (int i = 0; i < nb; ++i) {
			int64_t elem = ti6.randValue();
			volatile int pos = ti6.bsearchIter(elem);
		}
		double t1 = getTimeStamp();
		printf("time elapsed for bsearch iter %llf s\n", (t1 - t0));
	}

	return 0;
}