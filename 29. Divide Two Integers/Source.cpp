#include <climits>
#include <cmath>

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN) {
            switch (divisor) {
            case 1: return INT_MIN;
            case -1: return INT_MAX;
            }
        }
        if (dividend == INT_MAX and divisor == 1) { return INT_MAX; }
        const int sgn = dividend > 0 ^ divisor > 0 ? -1 : 1;
        int D = abs(dividend);
        const int d = abs(divisor);
        int q = 0;
        while (D >= d) {
            int δ = d, b = 1;
            while (δ << 1 <= D) { δ <<= 1; b <<= 1; }
            D -= δ; q += b;
        }
        return sgn * q;
    }
};