#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> twoSum(const vector<int>& a, int t) {
		unordered_map<int, size_t> f; // a[i] -> i (value -> index (i.e., subscript))
		for (size_t i = 0; i < a.size(); ++i) f.emplace(a[i], i);
		for (size_t i = 0; i < a.size(); ++i) {
			auto Y = f.find(t - a[i]);
			if (Y != f.end() && Y->second != i) return { int(i), int(Y->second) };
		}
		return {};
	}
};

int main() {

}