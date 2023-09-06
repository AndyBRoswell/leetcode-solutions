#include <climits>
#include <cmath>
#include <iostream>

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == INT_MIN) {
            switch (dividend) {
            case INT_MIN: return 1;
            default: return 0;
            }
        }
        if (dividend == INT_MIN) {
            switch (divisor) {
            case 1: return INT_MIN;
            case -1: return INT_MAX;
            default: {
                const int neg = divisor < 0;
                auto [d, i] = log(abs(divisor));
                if (i == false) { break; }
                switch (neg) {
                case false: return INT_MIN >> d;
                case true: return (INT_MAX >> d) + 1;
                }
            }
            }
        }
        if (dividend == INT_MAX) {
            const int neg = divisor < 0;
            auto [d, i] = log(abs(divisor));
            if (i == true) {
                switch (neg) {
                case false: return INT_MAX >> d;
                case true: return (INT_MIN >> d) + 1;
                }
            }
        }
        const int s = dividend > 0 ^ divisor > 0 ? -1 : 1;
        unsigned D = abs(dividend);
        const unsigned d = abs(divisor);
        if (D < d) { return 0; }
        int q = 0;
        while (D >= d) {
            unsigned δ = d, b = 1;
            while (δ << 1 <= D) {
                δ <<= 1; b <<= 1;
            }
            D -= δ; q += b;
        }
        return s * q;
    }
    template<class T> std::pair<T, bool> log(T x) {
        T p = -1, c = 0;
        while (x) {
            c += x & 1;
            ++p;
            x >>= 1;
        }
        return { p, c == 1 };
    }
};

int main() {
    Solution s;
    static constexpr int tests[][2] = {
        { INT_MAX, 2 },
        { INT_MAX, -2 },
        { INT_MIN, 2 },
        { INT_MIN, -2 },
        { INT_MAX, 3 },
        { INT_MAX, -3 },
        { INT_MIN, 3 },
        { INT_MIN, -3 },
        { INT_MAX, 4 },
        { INT_MAX, -4 },
        { INT_MIN, 4 },
        { INT_MIN, -4 },
    };
    for (const auto test : tests) {
        const auto q = s.divide(test[0], test[1]);
        std::cout << q << std::endl;
    }
    return 0;
}