
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

char* StrChr(const char* grange, char chat) {
    //chercher le char chat dans la grange
    return nullptr;
}

int main(){
    int s[4] = { 0,0,0,0 };
    int t[4] = { 0,1,2,3 };

    MemcpyWhile((char*)s, (char*)t, 4 * sizeof(int));
    for (int i = 0; i < 4; ++i) {
        printf("%d\n", s[i]);
    }

    char* toto = StrChr("sapin", 's');
	return 0;
}