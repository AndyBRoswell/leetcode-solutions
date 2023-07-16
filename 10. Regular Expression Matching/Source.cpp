#include <array>
#include <iostream>
#include <format>

#include <string>

class Solution {
public:
    bool isMatch(const std::string& S, const std::string& P) {
        enum class state { single, multi, };
        enum class special_type { any, };
        state state = state::single;
        size_t i = 0, j = 0;
        char c_rep;
        while (i < S.size() && j < P.size()) {
            switch (state) {
            case state::single: {
                const char next = j + 1 < P.size() ? P[j + 1] : '\0';
                c_rep = S[i];
                switch (P[j]) {
                case '.': c_rep = 0; ++i; ++j; break;
                case '*': return false; // invalid pattern
                default: // other chars: 'a', 'b', 'c', ...
                    if (S[i] == P[j]) { ++i; ++j; }
                    else { return false; }
                }
                if (next == '*') { state = state::multi; }
            }
                break;
            case state::multi:
                if (c_rep == 0 || S[i] == c_rep) { ++i; }
                else { ++j; state = state::single; }
                break;
            }
        }
        return j == P.size() && state == state::single ? i == S.size() : true;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Solution solution;
    constexpr std::array<std::array<const char*, 2>, 3> test_cases = {
        std::array<const char*, 2>{ "aa", "a" },
        std::array<const char*, 2>{ "aa", "a*" },
        std::array<const char*, 2>{ "ab", ".*" },
    };
    for (const auto& test_case : test_cases) {
        const auto& S = test_case[0];
        const auto& P = test_case[1];
        const auto result = solution.isMatch(S, P);
        std::cout << std::format("{}, {}: {}", S, P, result ? "true" : "false") << std::endl;
    }

    return 0;
}