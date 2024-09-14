#include "big_int.h"

big_int::big_int() {
    isNega = false;
    digits.push_back(0ull);
}

big_int::big_int(std::vector<unsigned int>& digits) : digits(digits) {
    isNega = false;
}
big_int::big_int(const char* number) {
    std::string str_num = "";
    for (int i = 0; number[i] != '\0'; i++)
        str_num += number[i];
    *this = big_int(str_num);
}
big_int::big_int(const std::string& number) {
    isNega = (number[0] == '-');
    if (number.substr(0 + isNega, 2) == "0b")
        InitBin(number);
}

big_int operator|(const big_int& a, const big_int& b) {

    int d = std::max(a.digits.size(), b.digits.size());

    big_int c;
    c.digits.resize(d);

    for (int i = 0; i < d; i++)
    {
        if (i >= a.digits.size())
            c.digits[i] = b.digits[i];
        else if (i >= b.digits.size())
            c.digits[i] = a.digits[i];
        else
            c.digits[i] = a.digits[i] | b.digits[i];
    }
    c.isNega = a.isNega || b.isNega;
    return c;
}
big_int operator&(const big_int& a, const big_int& b) {

    int d = std::min(a.digits.size(), b.digits.size());

    big_int c;
    c.digits.resize(d);

    for (int i = 0; i < d; i++)
        c.digits[i] = a.digits[i] & b.digits[i];
    c.isNega = a.isNega && b.isNega;
    return c;
}
big_int operator^(const big_int& a, const big_int& b) {
    int d = std::max(a.digits.size(), b.digits.size());

    big_int c;
    c.digits.resize(d);

    for (int i = 0; i < d; i++)
    {
        if (i >= a.digits.size())
            c.digits[i] = b.digits[i];
        else if (i >= b.digits.size())
            c.digits[i] = a.digits[i];
        else
            c.digits[i] = a.digits[i] ^ b.digits[i];
    }
    c.isNega = a.isNega ^ b.isNega;
    return c;
}

big_int operator+(const big_int& a, const big_int& b) {
    int d = std::max(a.digits.size(), b.digits.size());
    big_int c;
    c.digits.resize(d);

    unsigned long long carry = 0;
    for (int i = 0; i < d; i++)
    {
        unsigned long long digit = carry;
        if (i < a.digits.size())
            digit += a.digits[i];
        if (i < b.digits.size())
            digit += b.digits[i];
        std::cout << digit << " asd ";

        c.digits[i] = (unsigned int)digit;
        carry = (digit >> UINT_BIT);
        std::cout << carry << '\n';
    }
    if (carry != 0)
        c.digits.push_back(carry);

    return c;
}

std::ostream& operator<<(std::ostream& os, const big_int& bi) {
    if (bi.isNega)
        os << '-';
    for (unsigned int digit : bi.digits)
        os << digit << ' ';
    /*std::string result = "";

    for (auto it = bi.digits.rbegin(); it != bi.digits.rend(); ++it) {
        unsigned int carry = *it;
        std::string temp;

        for (char digit : result) {
            unsigned int value = carry * 10 + (digit - '0');
            temp += (value / BIT32) + '0';
            carry = value % BIT32;
        }

        while (carry > 0) {
            temp += (carry % 10) + '0';
            carry /= 10;
        }

        result = temp;
    }
    std::reverse(result.begin(), result.end());
    os << result;*/

    return os;
}

void big_int::InitBin(const std::string& bin) {
    int n = bin.size();
    assert(n > 2 + isNega);

    for (int i = n - 1; i >= 2 + isNega; i--)
    {
        unsigned int digit = 0;
        unsigned int base = 1;
        for (int j = 0; j < UINT_BIT; j++)
        {
            if (i < 2 + isNega)
                break;

            assert(bin[i] == '0' || bin[i] == '1');

            digit += (bin[i] - '0') * base;
            i--;
            base <<= 1;
        }

        if (isNega)
            digit = ~digit;
        digits.push_back(digit);
        i++;
    }
}