#include <vector>
#include <queue>

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
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        struct comparator { bool operator()(const ListNode* const lhs, const ListNode* const rhs) const { return lhs->val > rhs->val; } };
        if (lists.size() == 0) { return nullptr; }
        std::priority_queue<ListNode*, std::vector<ListNode*>, comparator> Q;
        ListNode* head = nullptr;
        ListNode* current = nullptr;
        for (auto list : lists) {
            if (list != nullptr) { Q.push(list); }
        }
        if (Q.empty()) { return nullptr; }
        {
            ListNode* const node = Q.top();
            Q.pop();
            head = node;
            current = head;
            if (node->next != nullptr) { Q.push(node->next); } // you cannot put this push operation after the previous pop operation
        }
        while (!Q.empty()) {
            ListNode* const node = Q.top();
            Q.pop();
            current->next = node;
            current = current->next;
            if (node->next != nullptr) { Q.push(node->next); } // you cannot put this push operation after the previous pop operation
        }
        return head;
    }
};

int main() {

}