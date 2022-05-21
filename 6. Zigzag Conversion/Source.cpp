#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	string convert(const string& s, const int rho) {
		if (rho == 1) return s;
		auto get_row = [rho](const int p) {
			const int Q = p / (rho - 1), R = p % (rho - 1);
			switch (Q % 2) {
			case 0: return R;
			case 1: return rho - 1 - R;
			}
			return -1;
		};
		auto get_column = [rho, s](const int p) {
			const int Q = p / (rho - 1);
			switch (Q % 2) {
			case 0: return Q / 2 * (rho - 1);
			case 1: return p - (Q + 1) / 2 * (rho - 1);
			}
			return -1;
		};
		vector<string> a;
		const int chi = get_column(s.length() - 1) + 1;
		for (int i = 0; i < rho; ++i) { a.emplace_back(chi, ' '); }
		for (size_t p = 0; p < s.length(); ++p) {
			const int x = get_row(p), y = get_column(p);
			a[x][y] = s[p];
		}
		string result;
		for (int i = 0; i < rho; ++i)
			for (int j = 0; j < chi; ++j) if (a[i][j] != ' ') result += a[i][j];
		return result;
	}
};

int main() {
	Solution S;
	const string s = "PAYPALISHIRING";
	const string r = S.convert(s, 4);
	cout << r << endl;
	return 0;
}