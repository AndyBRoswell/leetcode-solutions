#include <string>
#include <unordered_map>

class Solution {
public:
    int romanToInt(const std::string& s) {
        const std::unordered_map<char, int> f{ {'I', 1}, { 'V', 5 }, { 'X', 10 }, { 'L', 50 }, { 'C', 100 }, { 'D', 500 }, { 'M', 1000 } };
        int a = 0;
        for (size_t i = 0; i != s.size(); ++i) {
            if (i + 1 < s.size() && f.at(s[i]) < f.at(s[i + 1])) { a -= f.at(s[i]); }
            else { a += f.at(s[i]); }
        }
        return a;
    };
};