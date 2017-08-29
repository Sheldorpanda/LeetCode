/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(!head){return 0;}
        if(!(head->next)){return head;}
        ListNode* curr = head;
        while(curr){
            int v = curr->val;
            ListNode* temp = curr->next;
            if(v < x){
                if(!l_head){
                    l_head = curr;
                } else {
                    l_tail->next = curr;
                }
                l_tail = curr;
                curr->next = 0;
            }else{
                if(!ge_head){
                    ge_head = curr;
                } else {
                    ge_tail->next = curr;
                }
                ge_tail = curr;
                curr->next = 0;
            }
            curr = temp;
        }
        if(l_head){
            l_tail->next = ge_head;
            return l_head;
        } else {
            return ge_head;
        }
    }
    
private:
    
    ListNode* l_head;
    ListNode* l_tail;
    ListNode* ge_head;
    ListNode* ge_tail;

    
};