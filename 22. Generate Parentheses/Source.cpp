#include <vector>
#include <string>

class Solution {
public:
    void DFS(int n, int left, int right, std::vector<std::string>& ans, const std::string& str) {
        if (str.size() == 2 * n) {
            ans.emplace_back(str);
            return;
        }
        if (left < n) { DFS(n, left + 1, right, ans, str + '('); }
        if (right < left) { DFS(n, left, right + 1, ans, str + ')'); }
    }
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> ans;
        DFS(n, 0, 0, ans, "");
        return ans;
    }
};