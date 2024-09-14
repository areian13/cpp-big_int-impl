#ifndef _BIG_INT_
#define _BIG_INT_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

#define BIT32 (1ll << 32)
#define UINT_BIT 32

class big_int {
public:

    big_int();
    big_int(std::vector<unsigned int>& digits);
    big_int(const char* number);
    big_int(const std::string& number);

    friend big_int operator|(const big_int& a, const big_int& b);
    friend big_int operator&(const big_int& a, const big_int& b);
    friend big_int operator^(const big_int& a, const big_int& b);

    friend big_int operator+(const big_int& a, const big_int& b);

    friend std::ostream& operator<<(std::ostream& os, const big_int& bi);

private:
    std::vector<unsigned int> digits;
    bool isNega;

    void InitBin(const std::string& bin);
};

#endif // !_BIG_INT_