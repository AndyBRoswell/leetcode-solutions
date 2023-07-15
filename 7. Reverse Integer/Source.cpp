#include <algorithm>

class Solution {
public:
    int reverse(int x) {
        constexpr int t = INT_MAX / 10;     // threshold
        const int f = x < 0 ? -1 : 1;       // factor
        if (x == -2147483648) { return 0; } // special case
        x = abs(x);
        div_t p{ x, 0 };
        int a = 0;
        while (true) {
            p = div(p.quot, 10);
            if (a > t) { return 0; }
            else if (a == t && p.rem > 7) { return 0; }
            a = a * 10 + p.rem;
            if (p.quot == 0) { return f * a; }
        }
    }
};