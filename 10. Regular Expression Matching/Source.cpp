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
                switch (P[j]) {
                case '.': c_rep = S[i]; ++i; ++j; break;
                default:
                    if (S[i] == P[j]) { c_rep = S[i]; ++i; ++j; }
                    else { return false; }
                }
                if (P[j + 1] == '*') { state = state::multi; }
                break;
            case state::multi:
                break;
            }
        }
    }
};