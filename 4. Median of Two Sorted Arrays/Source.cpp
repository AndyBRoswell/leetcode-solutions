#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(const vector<int>& a, const vector<int>& b) {
        size_t i = 0, j = 0;
        vector<int> c;
        while (true) {
            if (i == a.size()) { for (; j < b.size(); ++j) c.emplace_back(b[j]); break; }
            if (j == b.size()) { for (; i < a.size(); ++i) c.emplace_back(a[i]); break; }
            if (a[i] <= b[j]) { c.emplace_back(a[i]); ++i; }
            else { c.emplace_back(b[j]); ++j; }
        }
        const size_t m = c.size() / 2;
        if (c.size() % 2 == 0) return (double(c[m - 1]) + c[m]) / 2;
        else return c[m];
    }
};

int main() {
    Solution s;
    cout << s.findMedianSortedArrays({ 1,2 }, { 3,4 });
    return 0;
}