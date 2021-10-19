
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Int64Array.hpp"

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
	for (int i = 0; i < 64; ++i) {
		//printf();
	}
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

	return 0;
}