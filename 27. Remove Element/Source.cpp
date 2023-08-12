#include <vector>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        // i: index of current element
        // j: index of next element not equal to val
        size_t i = 0, j = 0;
        for (; i != nums.size(); ++i) {
            if (nums[i] != val) {
                nums[j] = nums[i];
                ++j;
            }
        }
        return j;
    }
};
