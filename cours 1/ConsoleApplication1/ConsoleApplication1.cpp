
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "IntArray.hpp"

int main_()
{
    IntArray sapin(3);
    for (int i = 0; i < sapin.size; ++i)
        sapin.set(i, i * i);
    std::function<void(int)> foo = [](int value) {
        printf("%d\n", value);
    };
    sapin.iter(foo);

    double total = sapin.sum();
    double total2 = sapin.sumCapture();

    int s[4] = { 0,1,2,3 };
    IntArray* maCopie = IntArray::fromArray(s, 4);

    std::cout << "Hello World!\n" << total2 << "\n";
    return 0;
}

void Memcpy(char* dst, const char* src, int len) {
    //pour les len chars de  src, les copier dans dst
    for (int i = 0; i < len; ++i) {
        dst[i] = src[i];
    }
}

void MemcpyWhile(char* dst, const char* src, int len) {
    while (--len) 
        *dst++ = *src++;
}

const char* StrChr(const char* grange, char chat) {
    while (*grange) {
        if (*grange == chat)
            return grange;
        grange++;
    }
    return nullptr;
}

const char* StrStr(const char* a, const char* b) {
	//recuperer longueur de b
    int len = strlen(b);

	//tant que a
	while (*a) {
        bool found = true;
		//pour chaque caractere de b
        for (int i = 0; i < len; ++i) {
            if (a[i] != b[i]) {
				// si on trouve pas un char a, avancer a
				a++;
                found = false;
                break;
            }
        }
        if (found)
            return a;
    }
	return nullptr;
}


int add(int a, int b){ //avec que des +1,-1, return, apppels recursifs{
    if (b == 0)
        return a;
    else if( b > 0)
        return 1 + add(a, b - 1);
    else 
        return -1 + add(a, b + 1);
}
int sub(int a, int b) {
    return add(a, -b);
}

int mul(int a, int b) { // avec des additions
    if (b == 0) return 0;
    if (a == 0) return 0;
    if (b < 0)
        //return sub(0, mul(a, sub(0, b)));
        return -mul(a, -b);
    else 
        return add(a, mul(a, b - 1));
};

int divInt(int a, int b) // avec des soustractions utiliser une fonction intermédiaire 
{
    if (a == 0) return 0;
    if (b == 1) return a;
    if (b == 0) throw "division by zero";
    if (a < 0)  return sub(0, divInt(sub(0, a), b));
	if (a < b)  return 0;
    return 1 + divInt( sub(a,b), b);
}

int mod(int a, int b); // reste de la division

int len(int vecX, int vecY); // avec les fonctions precédentes

int mainStr () {
	int s[4] = { 0,0,0,0 };
	int t[4] = { 0,1,2,3 };

	MemcpyWhile((char*)s, (char*)t, 4 * sizeof(int));
	for (int i = 0; i < 4; ++i) {
		printf("%d\n", s[i]);
	}

	const char* toto = StrChr("sapin", 'p');
	const char* tota = StrStr("sapin", "p");
	const char* totu = StrStr("sapin", "n");
	const char* totm = StrStr("sapin", "s");
	const char* totn = StrStr("sapin", "pi");
	return 0;
}
int main(){
    int six = add(2, 4);
    int six2 = add(-2, -4);
    int two = add(-4, 2);
    int two2 = add(2, -4);
    int four = sub(6, 2);
    int vingtQuatre = mul(6, 4);
    int mvingtQuatre = mul(6, -4);
    int mvingtQuatre2 = mul(-6, 4);
    int trenteSix = mul(6,6);
    int quatre = divInt(24,6);
    int trois = divInt(23,6);
    int mquatre = divInt(-24,6);
    int mtrois = divInt(-23,6);
	return 0;
}