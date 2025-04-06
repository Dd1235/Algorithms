#include <iostream>

int len(int n)
{
    int res = 0;
    while (n > 0)
    {
        n /= 10;
        res++;
    }
    return res;
}

unsigned long long Karatsuba(unsigned long long x, unsigned long long y)
{

    if (x < 10 || y < 10)
    {
        return x * y;
    }

    int n = std::max(len(x), len(y));
    int m = std::ceil(n / 2.0);

    unsigned long long a = x / static_cast<unsigned long long>(std::pow(10, m)); // keep the first n/2 digits
    unsigned long long b = x % static_cast<unsigned long long>(std::pow(10, m)); // keep the last n/2 digits
    unsigned long long c = y / static_cast<unsigned long long>(std::pow(10, m));
    unsigned long long d = y % static_cast<unsigned long long>(std::pow(10, m));

    unsigned long long ac = Karatsuba(a, c);
    unsigned long long bd = Karatsuba(b, d);
    unsigned long long ad_bc = Karatsuba((a + b), (c + d)) - ac - bd;

    unsigned long long result = ac * static_cast<unsigned long long>(std::pow(10, 2 * m)) + (ad_bc * static_cast<unsigned long long>(std::pow(10, m))) + bd;

    return result;
}

int main()
{
    unsigned long long x, y, result;
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter y: ";
    std::cin >> y;
    result = Karatsuba(x, y);
    std::cout << "The result using Karatsuba Multiplication is " << result << std::endl;
    std::cout << "The result using the * operator is " << x * y << std::endl;
    return 0;
}