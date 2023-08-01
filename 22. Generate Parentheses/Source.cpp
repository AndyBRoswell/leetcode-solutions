#include <vector>
#include <string>

class Solution {
public:
    void DFS(int n, int nL, int nR, std::vector<std::string>& S, const std::string& p) {
        if (nL == n) { // reached the maximum recursion depth
            S.emplace_back(p + std::string(n - nR, ')')); // only 1 possible solution
            return;
        }
        if (nL < n) { DFS(n, nL + 1, nR, S, p + '('); }     // prefix p + '(' is possible
        if (nR < nL) { DFS(n, nL, nR + 1, S, p + ')'); }    // prefix p + ')' is possible
    }
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> ans;
        DFS(n, 0, 0, ans, ""); // start with empty prefix
        return ans;
    }
};