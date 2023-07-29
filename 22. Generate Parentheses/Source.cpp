#include <vector>
#include <string>

class Solution {
public:
    void DFS(int n, int nL, int nR, std::vector<std::string>& S, const std::string& s) {
        if (s.size() == 2 * n) {
            S.emplace_back(s);
            return;
        }
        if (nL < n) { DFS(n, nL + 1, nR, S, s + '('); }
        if (nR < nL) { DFS(n, nL, nR + 1, S, s + ')'); }
    }
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> ans;
        DFS(n, 0, 0, ans, "");
        return ans;
    }
};