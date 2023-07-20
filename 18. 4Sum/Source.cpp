#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
        if (nums.size() < 4) { return {}; }
        std::vector<std::vector<int>> result;
        std::sort(nums.begin(), nums.end());
        for (auto i = nums.cbegin(); i != nums.cend() - 3; ++i) {
            if (i != nums.cbegin() && *i == *(i - 1)) { continue; } // eliminate duplicates
            for (auto j = i + 1; j != nums.cend() - 2; ++j) {
                if (j != i + 1 && *j == *(j - 1)) { continue; }     // eliminate duplicates
                auto k = j + 1, l = nums.cend() - 1;
                while (k < l) {
                    //const int64_t sum = *i + *j + *k + *l;
                    int64_t sum = *i + *j;  // workaround for LeetCode's overflow sanitizer
                    sum += *k;
                    sum += *l;
                    if (sum == target) {
                        result.push_back({ *i, *j, *k, *l });
                        while (k < l && k + 1 < nums.cend() && *k == *(k + 1)) { ++k; }     // eliminate the remaining duplicate 4-tuples as well as 4-tuples with duplicate elements
                        while (k < l && l - 1 >= nums.cbegin() && *l == *(l - 1)) { --l; }  // eliminate the remaining duplicate 4-tuples as well as 4-tuples with duplicate elements
                        ++k; --l;                                                           // only moving 1 of the pointers causes sum != target thus we also move the other one to eliminate unnecessary comparisons
                    }
                    else if (sum < target) { ++k; }
                    else { --l; }
                }
            }
        }
        return result;
    }
};