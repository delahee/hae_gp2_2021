
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "IntArray.hpp"

int main()
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
}
