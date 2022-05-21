#include <iostream>
#include <string>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
	ListNode* addTwoNumbers(const ListNode* l1, const ListNode* l2) {
		ListNode* r = new ListNode, * l = r;
		int carry = 0;
		while (true) {
			if (l1 == nullptr) {
				while (l2 != nullptr) {
					const int x = l2->val + carry;
					if (x > 9) { l->next = new ListNode{ x % 10 }; carry = 1; }
					else { l->next = new ListNode{ x }; carry = 0; }
					l2 = l2->next; l = l->next;
				}
				if (carry == 1) l->next = new ListNode{ 1 };
				return r->next;
			}
			else if (l2 == nullptr) {
				while (l1 != nullptr) {
					const int x = l1->val + carry;
					if (x > 9) { l->next = new ListNode{ x % 10 }; carry = 1; }
					else { l->next = new ListNode{ x }; carry = 0; }
					l1 = l1->next; l = l->next;
				}
				if (carry == 1) l->next = new ListNode{ 1 };
				return r->next;
			}
			else {
				const int x = l1->val + l2->val + carry;
				if (x > 9) { l->next = new ListNode{ x % 10 }; carry = 1; }
				else { l->next = new ListNode{ x }; carry = 0; }
				l1 = l1->next; l2 = l2->next; l = l->next;
			}
		}
	}
};

ListNode* ConstructList(const string& data) {
	ListNode* target = new ListNode, * DummyHead = target;
	for (auto i : data) {
		const int x = i - '0';
		target->next = new ListNode{ x };
		target = target->next;
	}
	return DummyHead->next;
}

int main() {
	const string s1 = "9999999";
	const string s2 = "9999";
	const ListNode* l1 = ConstructList(s1);
	const ListNode* l2 = ConstructList(s2);
	Solution s;
	const ListNode* const l = s.addTwoNumbers(l1, l2), * r = l;
	while (r != nullptr) {
		cout << r->val;
		r = r->next;
	}
	return 0;
}