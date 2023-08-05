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
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* const ret = head->next;
        ListNode* const dummy = new ListNode(0, head);
        for (ListNode* p = dummy; p != nullptr; p = p->next->next) {
            ListNode* const q = p->next;
            if (q == nullptr) { break; }
            ListNode* const r = q->next;
            if (r == nullptr) { break; }
            p->next = r;
            q->next = r->next;
            r->next = q;
        }
        return ret;
    }
};