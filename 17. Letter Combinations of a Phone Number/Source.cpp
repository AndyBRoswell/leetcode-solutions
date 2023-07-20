#include <string>
#include <vector>
#include <set>

class Solution {
public:
    std::vector<std::string> letterCombinations(std::string& digits) {
        if (digits.empty()) { return {}; }
        constexpr std::string_view L[] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        for (auto& digit : digits) { digit = digit - '0'; } // just for convenience of subsequent processing
        const std::set<int> s(digits.cbegin(), digits.cend());
        const std::vector<int> d(s.cbegin(), s.cend());
        std::vector<std::string> ans;
        const std::vector<size_t> v0(d.size(), 0);
        std::vector<size_t> v = v0;
        do {
            std::string str;
            for (size_t i = 0; i < d.size(); ++i) { str += L[d[i]][v[i]]; }
            ans.push_back(str);
            for (size_t i = 0; i < L[*d.crbegin()].size(); ++i) {

            }
        } while (v != v0);
        return ans;
    }
};

int main() {

}