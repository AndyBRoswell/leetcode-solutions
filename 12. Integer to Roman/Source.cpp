#include <string>
#include <array>

class Solution {
public:
    // https://leetcode.com/problems/integer-to-roman/solutions/2962674/easiest-o-1-faang-method-ever/
    std::string intToRoman(int n) {
        constexpr std::array<std::array<const char*, 10>, 4> r = { /* An extra layer of parentheses here is required */ {
            { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" },
            { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" },
            { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" },
            { "", "M", "MM", "MMM" }
        } };
        return std::string(r[3][n / 1000]) + r[2][n / 100 % 10] + r[1][n / 10 % 10] + r[0][n % 10];
    }
};

int main() {

}