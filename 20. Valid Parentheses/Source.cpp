#include <string>
#include <stack>

class Solution {
public:
    bool isValid(const std::string& s) {
        std::stack<char> stack;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') { stack.push(c); }
            else if (c == ')') {
                if (stack.empty() || stack.top() != '(') { return false; }
                stack.pop();
            }
            else if (c == ']') {
                if (stack.empty() || stack.top() != '[') { return false; }
                stack.pop();
            }
            else if (c == '}') {
                if (stack.empty() || stack.top() != '{') { return false; }
                stack.pop();
            }
        }
        return stack.empty();
    }
};