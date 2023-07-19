#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::sort(nums.begin(), nums.end()); // so that we can immediately eliminate some impossible cases (the smallest one of the 3-tuple is positive)
        for (auto i = nums.cbegin(); i != nums.cend() - 2 && *i <= 0; ++i) {
            if (i != nums.cbegin() && *i == *(i - 1)) { continue; } // eliminate duplicates
            auto L = i + 1, R = nums.cend() - 1;
            while (L < R) {
                const int sum = *i + *L + *R;
                if (sum == 0) {
                    result.push_back({ *i, *L, *R });
                    while (L < R && L + 1 < nums.cend() && *L == *(L + 1)) { ++L; }     // eliminate duplicates
                    while (L < R && R - 1 > nums.cbegin() && *R == *(R - 1)) { --R; }   // eliminate duplicates
                    ++L; --R;                                                           // only move one of the pointers is not enough after eliminating duplicates
                }
                else if (sum < 0) { ++L; }
                else { --R; }
            }
        }
        return result;
    }
};