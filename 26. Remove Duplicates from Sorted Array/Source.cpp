#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    // https://leetcode.com/problems/remove-duplicates-from-sorted-array/solutions/3676877/best-method-100-c-java-python-beginner-friendly/
    // See MSVC implementation of std::unique
    int removeDuplicates(std::vector<int>& nums) {
        // the problem assumes nums.size() >= 1
        // i: Current index
        // j: Last element of the unique elements. We always put next unique element at index j + 1
        size_t i = 0, j = 0;
        while (++i != nums.size()) { // skip all the duplicates
            // Note: when the 1st time this branch is reached, i = 1 but j = 0
            if (nums[j] != nums[i]) {   // if the current element nums[i] is different from the last unique element nums[j]
                nums[++j] = nums[i];    // Note: nums[0] is always unique, so we can safely increment j
            }
        }
        return ++j; // return the size of the unique elements, corresponding to the last index (end() iterator)
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
    for (auto& test_case : test_cases) {
        const auto ret = s.removeDuplicates(test_case);
        std::cout << ret << ", ";
        //std::unique(test_case.begin(),test_case.end());
        std::cout << "[ ";
        for (const auto element : test_case) { std::cout << element << ' '; }
        std::cout << "]" << std::endl;
    }
}