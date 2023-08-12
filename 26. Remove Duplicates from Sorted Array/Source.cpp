#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    // https://leetcode.com/problems/remove-duplicates-from-sorted-array/solutions/3676877/best-method-100-c-java-python-beginner-friendly/
    // See MSVC implementation of std::unique
    int removeDuplicates(std::vector<int>& nums) {
        // the problem assumes nums.size() >= 1
        // i: current element
        // j: last element of the unique elements
        for (size_t i = 0, j = 0; ++i < nums.size(); ++j) {
            // Note: when the 1st time this branch is reached, i = 1 but j = 0
            if (nums[j] == nums[i]) { // found a duplicate
                while (++i != nums.size()) { // skip all the duplicates
                    if (nums[j] != nums[i]) { nums[++j] = nums[i]; } // found the next unique element
                }
                return ++j; // return the size of the unique elements, corresponding to the last index (end() iterator)
            }
        }
        return nums.size(); // all the elements are unique
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