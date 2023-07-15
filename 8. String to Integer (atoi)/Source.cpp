#include <string>

using std::string;

class Solution {
public:
    int myAtoi(string S) {
        enum class state { leading, digit, };
        constexpr int t = INT_MAX / 10; // threshold
        int r = 0, s = 1;               // result and sign
        state state = state::leading;
        for (const auto c : S) {
            switch (state) {
            case state::leading:
                switch (c) {
                case ' ': continue;
                case '-': s = -1; state = state::digit; continue;
                case '+': state = state::digit; continue;
                default:
                    if (isdigit(c)) { r = 10 * r + (c - '0'); state = state::digit; continue; }
                    return 0;
                }
            case state::digit:
                if (isdigit(c)) {
                    if (r > t) { return s > 0 ? INT_MAX : INT_MIN; }
                    if (r == t) {
                        if (s > 0 && c >= '7') { return INT_MAX; }
                        if (s < 0 && c >= '8') { return INT_MIN; }
                    }
                    r = 10 * r + (c - '0');
                    continue;
                }
                return s * r;
            }
        }
        return s * r; // reached end of string
    }
};