#include <vector>

class Solution {
public:
    int maxArea(const std::vector<int>& h) {
        const size_t n = h.size();
        size_t a = 0, b = n - 1;
        int V = 0;
        while (a < b) {
            if(h[a] <= h[b]) {
                V = std::max<int>(V, (b - a) * h[a]);
                ++a;
            }
            else {
                V = std::max<int>(V, (b - a) * h[b]);
                --b;
            }
        }
    }
};