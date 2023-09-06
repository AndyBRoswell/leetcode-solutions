#include <climits>
#include <cmath>
#include <iostream>

// https://leetcode.com/problems/divide-two-integers/solutions/13407/c-bit-manipulations/
// The solution above uses long for D and d but this causes infinite loop on my platform.
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == INT_MIN) { // special case: divisor == -2^31
            switch (dividend) {
            case INT_MIN: return 1;
            default: return 0;
            }
        }
        if (dividend == INT_MIN) { // special case: dividend == -2^31
            switch (divisor) {
            case 1: return INT_MIN;
            case -1: return INT_MAX;
            default: {
                const int neg = divisor < 0;
                auto [d, i] = log(abs(divisor));
                if (i == false) { break; } // d is not power of 2
                switch (neg) {
                case false: return INT_MIN >> d;
                case true: return (INT_MAX >> d) + 1;
                }
            }
            }
        }
        if (dividend == INT_MAX) { // special case: dividend == 2^31 - 1
            const int neg = divisor < 0;
            auto [d, i] = log(abs(divisor));
            if (i == true) { // d is power of 2
                switch (neg) {
                case false: return INT_MAX >> d;
                case true: return (INT_MIN >> d) + 1;
                }
            }
        }
        const int s = dividend > 0 ^ divisor > 0 ? -1 : 1;  // sign
        unsigned D = labs(dividend);                        // dividend (Note: if D is int, then D = INT_MAX will overflow and result in infinite loop)
        const unsigned d = labs(divisor);                   // divisor
        if (D < d) { return 0; }                            // just in order to bypass the overflow sanitizer on LeetCode
        int q = 0;                                          // quotient
        while (D >= d) {
            unsigned δ = d, b = 1; // δ: divisor, b: bit
            while (δ << 1 <= D) { δ <<= 1; b <<= 1; } // trial division
            D -= δ; q += b;
        }
        return s * q;
    }
    template<class T> std::pair<T, bool> log(T x) { // base is 2
        T p = -1, c = 0; // p: power, c: count of digit 1
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
        { INT_MAX, 1 },
        { INT_MAX, -1 },
        { INT_MIN, 1 },
        { INT_MIN, -1 },
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