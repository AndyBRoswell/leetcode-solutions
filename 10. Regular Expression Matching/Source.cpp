#include <string>

class Solution {
public:
    bool isMatch(const std::string& S, const std::string& P) {
        enum class state { single, multi, };
        state state = state::single;
        size_t i = 0, j = 0;
        char c_rep;
        while (i < S.size() && j < P.size()) {
            switch (state) {
            case state::single:
                c_rep = S[i];
                switch (P[j]) {
                case '.': ++i; ++j; break;
                case '*': return false; // invalid pattern
                default: // other chars: 'a', 'b', 'c', ...
                    if (S[i] == P[j]) { ++i; ++j; }
                    else { return false; }
                }
                if (P[j + 1] == '*') { state = state::multi; }
                break;
            case state::multi:
                if (S[i] == c_rep) { ++i; }
                else { ++j; state = state::single; }
                break;
            }
        }
        return j == P.size();
    }
};