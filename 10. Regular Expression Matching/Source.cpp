#include <array>
#include <iostream>
#include <format>

#include <string>
#include <vector>

class Solution {
public:
    bool isMatch(const std::string& S, const std::string& P) {
        std::vector<std::string_view> token;
        for (size_t i = 0; i < P.size(); ++i) {
            if (i + 1 < P.size() && P[i + 1] == '*') {
                token.emplace_back(P.substr(i, 2));
                ++i;
            }
            else { token.emplace_back(P.substr(i, 1)); }
        }
        size_t i = 0, j = 0;
        while (i < S.size() && j < P.size()) {
            if (token[j].find('*') != std::string_view::npos) {
                if (token[j][0] == '.') { // '.*'
                    i = S.size(); // match all
                    ++j;
                    break;
                }
                else { while (i < S.size() && S[i] == token[j][0]) { ++i; } } // ...
            }
            else {
                if (token[j][0] == '.' || S[i] == token[j][0]) { ++i; } // match
                else { return false; }  // mismatch
            }
        }
        return S.size() == i && P.size() == j; // complete match is required
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