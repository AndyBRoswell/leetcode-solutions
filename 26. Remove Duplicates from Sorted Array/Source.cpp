#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        // the problem assumes nums.size() >= 1
        for (size_t i = 0, j = i; ++i < nums.size(); j = i) {
            if (nums[j] == nums[i]) {
                while (++i != nums.size()) {
                    if (nums[j] != nums[i]) { nums[++j] = nums[i]; }
                }
                return ++j;
            }
        }
        return nums.size();
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::vector<int> test_cases[] = {
        { 1, 1, 2 },
        { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 },
    };
    Solution s;
    for (auto& test_case: test_cases) {
        const auto ret = s.removeDuplicates(test_case);
        std::cout << ret << ", ";
        //std::unique(test_case.begin(),test_case.end());
        std::cout << "[ ";
        for (const auto element : test_case) { std::cout << element << ' '; }
        std::cout << "]" << std::endl;
    }
}