#include <array>
#include <iostream>
#include <format>

#include <string>
#include <vector>

class Solution {
public:
    bool isMatch(const std::string& S, const std::string& P) { return has_match_1(S, P); }
    bool has_match_1(const std::string& S, const std::string& P) {

    }
    bool has_match_2_top_down(const std::string& S, const std::string& P) {

    }
    bool has_match_2_bottom_up(const std::string& S, const std::string& P) {

    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Solution solution;
    constexpr std::array<std::array<const char*, 2>, 6> test_cases = {
        std::array<const char*, 2>{ "aa", "a" },
        std::array<const char*, 2>{ "aa", "a*" },
        std::array<const char*, 2>{ "ab", ".*" },
        std::array<const char*, 2>{ "aab", "c*a*b" },
        std::array<const char*, 2>{ "aaa", "a*a" },
        std::array<const char*, 2>{ "ab", ".*c" },
    };
    for (const auto& test_case : test_cases) {
        const auto& S = test_case[0];
        const auto& P = test_case[1];
        const auto result = solution.isMatch(S, P);
        std::cout << std::format("{}, {}: {}", S, P, result ? "true" : "false") << std::endl;
    }

    return 0;
}