#include <vector>
#include <algorithm>
#include <array>
#include <iostream>

class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int ans = nums[0] + nums[1] + nums[2];
        for (auto i = nums.cbegin(); i != nums.cend() - 2; ++i) {
            if (i != nums.cbegin() && *i == *(i - 1)) { continue; } // eliminate duplicates
            auto L = i + 1, R = nums.cend() - 1;
            while (L < R) {
                const int sum = *i + *L + *R;
                if (abs(sum - target) < abs(ans - target)) {
                    ans = sum;
                    if (ans == target) { return ans; } // early return
                }
                if (sum < target) { ++L; }
                else { --R; }
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    struct input { std::vector<int> nums; int target; };
    std::array<struct input, 2> inputs{{
        { { 4, 0, 5, -5, 3, 3, 0, -4, -5 }, -2 },
        { { -1000, -5, -5, -5, -5, -5, -5, -1, -1, -1 }, -15 }
        }};
    for (auto& input : inputs) {
        std::cout << s.threeSumClosest(input.nums, input.target) << std::endl;
    }
}