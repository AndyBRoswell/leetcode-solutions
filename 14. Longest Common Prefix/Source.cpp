#include <string>
#include <vector>

class Solution {
public:
    std::string longestCommonPrefix(const std::vector<std::string>& strs) {
        const auto shortest_str_pos = std::min_element(strs.begin(), strs.end(), [](const std::string& a, const std::string& b) { return a.size() < b.size(); });
        const auto shortest_str = *shortest_str_pos;
        for (size_t i = 0; i < shortest_str.size(); ++i) {
            for (auto j = strs.cbegin(); j != strs.cend(); ++j) {
                if (j == shortest_str_pos) { continue; }
                if ((*j)[i] != shortest_str[i]) { return shortest_str.substr(0, i); }
            }
        }
        return shortest_str;
    }
};