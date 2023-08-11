#include <vector>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, const int k) {
        if (head == nullptr) { return head; }
        ListNode* const dummy = new ListNode(0, head);
        std::vector<ListNode*> p(k + 1);
        auto try_next_nodes = [&]() {
            for (int i = 0; i < k; ++i) {
                if (p[i]->next != nullptr) { p[i + 1] = p[i]->next; }
                else { return false; }
            }
            return true;
            };
        for (p[0] = dummy; p[0] != nullptr; p[0] = p[k - 1]->next) {
            if (try_next_nodes() == false) { break; }
            p[0]->next = p[k - 1]->next;
            for (int i = k - 1; i > 0; --i) { p[i]->next = p[i - 1]; }

        }
    }
};