
#include <iostream>
#include "Toto.h"
#include "IntArray.hpp"

void  main0()
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

	/*
	 //Vec toto;
	Vec4 a;
	Vec4 b;

	a.x = 16;
	b.y = 17;
	a.z = b.z = 8;
	b.w = -16;

	Vec4 res = a.add(b);
	printf("%f %f %f", res.x,res.y,res.z);

	res.incr(b);
	res.incr(18);
	Vec4 resDiv = res.div(2);

	*/
};

int main()
{
	IntArray bob;
	for (int i = 0; i < 16; i++) {
		bob.set(i, i * i);
	}
	for (int i = 0; i < 16; i++) {
		printf("%d ", bob.get(i));
	}
	printf("\n");

    return 0;
}