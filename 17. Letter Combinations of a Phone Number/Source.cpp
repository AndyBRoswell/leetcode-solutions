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
        const std::vector<size_t> initial_value(d.size(), 0);
        std::vector<size_t> current_value = initial_value;
        do {
            std::string str;
            for (size_t i = 0; i < d.size(); ++i) { str += L[d[i]][current_value[i]]; }
            ans.push_back(str);
            for (size_t i = 0; i < d.size(); ++i) {
                if (current_value[i] < L[d[i]].size() - 1) { ++current_value[i]; break; }
                else {
                    current_value[i] = 0;
                }
            }
        } while (current_value != initial_value);
    }
};

int main() {

}