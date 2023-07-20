#include <string>
#include <vector>
#include <set>
#include <iostream>

class Solution {
public:
    std::vector<std::string> letterCombinations(std::string& digits) {
        if (digits.empty()) { return {}; }
        constexpr std::string_view L[] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        for (auto& digit : digits) { digit = digit - '0'; }         // just for convenience of subsequent processing
        const std::vector<int> d(digits.cbegin(), digits.cend());   // d: digit
        std::vector<std::string> ans;
        std::vector<size_t> v(d.size(), 0);
        while (true) {
            for (size_t i = 0; i < L[*d.crbegin()].size(); ++i, ++ * v.rbegin()) { // LSB
                std::string str;
                for (size_t i = 0; i < d.size(); ++i) { str += L[d[i]][v[i]]; }
                ans.push_back(str);
            }
            *v.rbegin() = 0;
            if (d.size() > 1) { // carry
                ++*(v.rbegin() + 1);
                for (auto i = v.rbegin() + 1; i != v.rend() - 1; ++i) {
                    if (*i < L[d[(d.size() - 1) - (i - v.rbegin())]].size()) { break; }
                    *i = 0;
                    ++*(i + 1);
                }
                if (*v.cbegin() == L[d[0]].size()) { *v.begin() = 0; break; } // overflow (all combinations are generated)
            }
            else break;
        }
        return ans;
    }
};

int main() {
    Solution s;
    constexpr const char* inputs[] = { "23", "5678", "2", };
    for (const auto& input : inputs) {
        std::string digits(input);
        const auto ans = s.letterCombinations(digits);
        for (const auto& str : ans) { std::cout << str << ' '; }
        std::cout << std::endl;
    }
}