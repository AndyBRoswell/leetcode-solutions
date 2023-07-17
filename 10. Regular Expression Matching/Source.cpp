#include <array>
#include <iostream>
#include <format>

#include <string>
#include <vector>
#include <functional>

/// <summary>
/// Note: When a regular expression includes optional quantifiers or alternation constructs, the evaluation of the input string is no longer linear.
/// https://learn.microsoft.com/en-us/dotnet/standard/base-types/backtracking-in-regular-expressions
/// </summary>
class Solution {
public:
    bool isMatch(const std::string& T, const std::string& P) { return has_match_2_bottom_up(T, P); }
    bool has_match_1(const std::string_view T, const std::string_view P) {
        if (P.empty()) { return T.empty(); }                                    // special case: empty pattern
        const bool first_match = !T.empty() && (T[0] == P[0] || P[0] == '.');   // attempt to match the 1st character
        if (P.size() >= 2 && P[1] == '*') {                         // pattern is with '*'
            return has_match_1(T, P.substr(2))                      // 0 repetition
                || (first_match && has_match_1(T.substr(1), P));    // 1 or more repetitions
        }
        else {                                              // pattern is without '*'
            return first_match
                && has_match_1(T.substr(1), P.substr(1));   // attempt to match the rest
        }
    }
    bool has_match_2_top_down(const std::string_view T, const std::string_view P) {
        // T[i:] matches P[j:] => m[i][j] = true
        // ∀m[i′][j′] = true s.t. i′ > i and j′ > j <=> m[i][j] = true
        std::vector<std::vector<bool>> m(T.size() + 1, std::vector<bool>(P.size() + 1, false));
        std::function<bool(size_t, size_t)> D = [&](const size_t i, const size_t j) -> bool {
            bool ans;
            if (j == P.size()) { ans = i == T.size(); } // special case: empty pattern <-> empty text
            else {
                bool first_match = i < T.size() && (T[i] == P[j] || P[j] == '.'); // attempt to match the 1st character
                if (j + 1 < P.size() && P[j + 1] == '*') {  // pattern is with '*'
                    ans = D(i, j + 2)                       // 0 repetition 
                        || (first_match && D(i + 1, j));    // 1 or more repetitions
                }
                else {                                      // pattern is without '*'
                    ans = first_match && D(i + 1, j + 1);   // attempt to match the rest
                }
            }
            m[i][j] = ans ? true : false;
            return ans;
        };
        return D(0, 0);
    }
    bool has_match_2_bottom_up(const std::string_view T, const std::string_view P) {

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