#include <iostream>

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* p = head;
        int N = 0;
        while (p->next != nullptr) { p = p->next; ++N; }
        ++N;
        if (N == 1) { return nullptr; }
        else if (N == 2) {
            switch (n) {
            case 1:
                head->next = nullptr;
                return head;
            case 2:
                return head->next;
            }
        }
        else { // N >= 3
            p = head;
            if (n == 1) {
                while (p->next->next != nullptr) { p = p->next; }
                p->next = nullptr;
                return head;
            }
            else if (n == N) {
                return head->next;
            }
            else {
                for (int i = 0; i < N - n - 1; ++i) { p = p->next; }
                p->next = p->next->next;
                return head;
            }
        }
        return nullptr; // never reach here
    }
};

int main() {
    Solution s;
    ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    ListNode* p = s.removeNthFromEnd(head, 2);
    while (p != nullptr) {
        std::cout << p->val << "->";
        p = p->next;
    }
    return 0;
}