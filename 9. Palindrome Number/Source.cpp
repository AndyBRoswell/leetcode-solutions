#include <string>

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) { return false; }
        const std::string s = std::to_string(x);
        const size_t l = s.size() / 2;
        for (size_t i = 0; i < l; ++i) {
            const size_t j = s.size() - i - 1;
            if (s[i] != s[j]) { return false; }
        }
        return true;
    }
};