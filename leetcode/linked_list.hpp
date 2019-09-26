//
//  linked_list.hpp
//  leetcode
//
//  Created by 秀健身 on 2019/9/26.
//  Copyright © 2019 jisudong. All rights reserved.
//

#ifndef linked_list_hpp
#define linked_list_hpp

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};



/**
237.删除链表中的结点

删除某个链表中给定的（非末尾）节点，你将只被给定要求被删除的节点。
https://leetcode-cn.com/problems/delete-node-in-a-linked-list/
*/
void deleteNode(ListNode* node) {
    node->val = node->next->val;
    node->next = node->next->next;
}


/**
 21.合并两个有序链表
 
 将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的
 https://leetcode-cn.com/problems/merge-two-sorted-lists/
 */
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
//    if (l1 == NULL) return l2;
//    if (l2 == NULL) return l1;
//    ListNode *dummyhead = new ListNode(0);
//    ListNode *p = dummyhead;
//    while (l1 != NULL && l2 != NULL) {
//        if (l1->val < l2->val) {
//            p->next = l1;
//            p = p->next;
//            l1 = l1->next;
//        } else {
//            p->next = l2;
//            p = p->next;
//            l2 = l2->next;
//        }
//    }
//    if (l1 == NULL) {
//        p->next = l2;
//    } else {
//        p->next = l1;
//    }
//    return dummyhead->next;
    
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;
    if (l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}


/**
 83.删除排序链表中的重复元素
 
 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。
 https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/
 */
ListNode* deleteDuplicates(ListNode* head) {
    ListNode *p = head;
    while (p != NULL && p->next != NULL) {
        if (p->val == p->next->val) {
            p->next = p->next->next;
        } else {
            p = p->next;
        }
    }
    return head;
}


#endif /* linked_list_hpp */
