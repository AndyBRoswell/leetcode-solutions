#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        // the problem assumes nums.size() >= 1
        size_t _UFirst = 0, _UFirstb;
        const size_t _ULast = nums.size();
        for (_UFirstb = _UFirst; ++_UFirst < _ULast; _UFirstb = _UFirst) {
            if (nums[_UFirstb] == nums[_UFirst]) {
                while (++_UFirst != _ULast) {
                    if (nums[_UFirstb] != nums[_UFirst]) {
                        nums[++_UFirstb] = nums[_UFirst];
                    }
                }
                return ++_UFirstb;
            }
        }
        return _ULast;
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