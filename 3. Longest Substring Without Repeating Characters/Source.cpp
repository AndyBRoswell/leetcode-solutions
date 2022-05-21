#include <algorithm>
#include <bitset>
#include <string>

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(const string& s) {
		if (s.empty()) return 0;
		size_t a = 0, b = 0;
		bitset<128> n;
		n[s[0]] = true;
		char c;
		size_t lmax = 1, l = 1;
		while (b != s.size() - 1) {
			c = s[b + 1];
			switch (n[c]) {
			case false:
				n[c] = true;
				++b; ++l;
				lmax = max(lmax, l);
				break;
			case true:
				n[s[a]] = false;
				++a; --l;
				break;
			}
		}
		return lmax;
	}
};

int main() {

}