
#include <iostream>
#include "Toto.h"
#include "IntArray.hpp"

void main0()
{
    printf("0\n");
    int zero = 0;
    printf("%i\n",zero);

    printf("%f\n",0.5f);
    printf("%s\n","toto");
   
    long long int t = 123456789123456789;// 
	printf("%lld\n", t);

    uint64_t t1 = 123456789123456789;
	printf("%lld\n", t1);

    std::cout << "0" << std::endl;
    std::cout << "0.5" << std::endl;
    std::cout << "toto" << std::endl;
    std::cout << 0.6 << std::endl;
    std::cout << 123456789123456789 << std::endl;
}

struct Vec4 {
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;

    Vec4 add(Vec4 v) {
        Vec4 res;
		res.x = x + v.x;
		res.y = y + v.y;
		res.z = z + v.z;
		res.w = w + v.w;
        return res;
    };

	void incr(Vec4 v) {
		x = x + v.x;
		y = y + v.y;
		z = z + v.z;
		w = w + v.w;
	};

	void incr(float f) {
		x = x + f;
		y = y + f;
		z = z + f;
		w = w + f;
	};

	Vec4 div(Vec4 v) {
		Vec4 res;
		res.x = x / v.x;
		res.y = y / v.y;
		res.z = z / v.z;
		res.w = w / v.w;
		return res;
	};

	Vec4 div(float f) {
		Vec4 res;
		res.x = x / f;
		res.y = y / f;
		res.z = z / f;
		res.w = w / f;
		return res;
	};

};


int Strlen(const char* maChaine) {
	int res = 0;
	//parcourir la chaine
	while (maChaine[res] != 0) {
		res++;
	}
	return res;
}

int Strlen2(const char* maChaine) {
	const char* cursor = maChaine;
	while (*cursor) cursor++;
	return cursor - maChaine;
}

int Countc(const char* maChaine, char c) {
	int sizeOfString = strlen(maChaine);
	int res = 0;//compte de characters

	for (int i = 0; i < sizeOfString; i++) 
		if ( maChaine[i] == c)
			res++;	
	return res;
}

void StrCpy(char* dst, const char* src) {
	int NbOfChar;
	NbOfChar = Strlen(src);
	for (int i = 0; i < NbOfChar; i++)
	{
		dst[i] = src[i];
	}
	dst[NbOfChar] = 0;
}

void StrCpyFast(char* dst, const char* src) {
	while (*src /*!= 0*/ ) {
		*dst = *src;
		dst++;
		src++;
	}
	*dst = 0;
}

void StrNCpyULTRA_UNREADABLE(char* dst, int nb, const char* src) {
	while (nb-- && (*dst++ = *src++));
	*dst = 0;
}

void StrNCpy(char* dst, int nb, const char* src) {
	while( nb-- && *src) {
		*dst = *src;
		dst++;
		src++;
	}
	*dst = 0;
}

int main()
{
	IntArray toto(4);
	for (int i = 0; i < 4; ++i) 
		toto.set(i, 2*i);
	toto.insert(3);
    return 0;
}