#include <string>
#include <vector>

using namespace std;

class Solution {
	pair<ptrdiff_t, ptrdiff_t> ExpandFromPalindromicCenter(const string& S, ptrdiff_t L, ptrdiff_t R) {
		while (L >= 0 and R < S.size() and S[L] == S[R]) { --L; ++R; }
		return { L + 1, R - 1 };
	}
public:
	string longestPalindrome(const string& s) {
		ptrdiff_t L = 0, R = 0;
		for (ptrdiff_t i = 0; i < s.size(); ++i) {
			auto [L1, R1] = ExpandFromPalindromicCenter(s, i, i);			// 回文中心为一个字符的情况
			auto [L2, R2] = ExpandFromPalindromicCenter(s, i, i + 1);		// 回文中心为两个字符的情况
			if (R1 - L1 > R - L) { L = L1; R = R1; }
			if (R2 - L2 > R - L) { L = L2; R = R2; }
		}
		return s.substr(L, R - L + 1);
	}
};

int main() {

}