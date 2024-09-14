#include <iostream>
#include "big_int.h"

using namespace std;

int main()
{
    //big_integer a("-0b1011011011101011010100010101101010000111010");
    big_int a("0b100"), b("0b111111111111111111111111111111111111111111111111100");
    cout << b << '\n';
    cout << a + b << '\n';
}