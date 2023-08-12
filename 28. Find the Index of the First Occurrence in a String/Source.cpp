#include <string>

class Solution {
public:
    int strStr(std::string& T, std::string& P) {
        const auto p = T.find(P);
        return p == std::string::npos ? -1 : p;
    }
};