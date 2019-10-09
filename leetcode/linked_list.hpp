//
//  linked_list.hpp
//  leetcode
//
//  Created by jisudong on 2019/9/26.
//  Copyright © 2019 jisudong. All rights reserved.
//

#ifndef linked_list_hpp
#define linked_list_hpp

#include <iostream>
#include <vector>
#include <queue>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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


/**
 141.环形链表
 
 给定一个链表，判断链表中是否有环
 https://leetcode-cn.com/problems/linked-list-cycle/
 */
bool hasCycle(ListNode *head) {
    if (head == NULL || head->next == NULL) return false;
    
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}


/**
 206.反转链表
 
 反转一个单链表
 https://leetcode-cn.com/problems/reverse-linked-list/
 */
ListNode* reverseList(ListNode* head) {
//    ListNode *result = NULL, *tmp;
//    while (head != NULL) {
//        tmp = head;
//        head = head->next;
//        tmp->next = result;
//        result = tmp;
//    }
//    return result;
    
    ListNode *result = head;
    while (result && head->next != NULL) {
        ListNode *p = head->next;
        head->next = p->next;
        p->next = result;
        result = p;
    }
    return result;
}


/**
 109. 有序链表转换二叉搜索树
 
 给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。
 https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/
 */
TreeNode* sortedListToBST(ListNode* head) {
//    if (head == NULL) return NULL;
//    if (head->next == NULL) return new TreeNode(head->val);
//
//    ListNode *pre = head;
//    ListNode *mid = pre->next;
//    ListNode *p = mid->next;
//
//    while (p != NULL && p->next != NULL) {
//        mid = mid->next;
//        p = p->next->next;
//        pre = pre->next;
//    }
//
//    pre->next = NULL; // 把链表断开为左、右两段链表
//    TreeNode *root = new TreeNode(mid->val);
//    root->left = sortedListToBST(head);
//    root->right = sortedListToBST(mid->next);
//
//    return root;
    
    
    if (head == NULL) return NULL;
    if (head->next == NULL) return new TreeNode(head->val);
    
    std::vector<ListNode *> nodes;
    ListNode *p = head;
    
    while (p != NULL) {
        nodes.push_back(p);
        p = p->next;
    }
   
    int rootIndex = (int)nodes.size() >> 1;
    TreeNode *root = new TreeNode(nodes.at(rootIndex)->val);
    
    std::queue<TreeNode *> parentNodes;
    parentNodes.push(root);
    
    std::queue<int> ranges;
    int invalidIndex = -1;
    if (rootIndex == 0) {
        ranges.push(invalidIndex);
        ranges.push(invalidIndex);
    } else {
        ranges.push(0);
        ranges.push(rootIndex - 1);
    }
    
    if (rootIndex == nodes.size() - 1) {
        ranges.push(invalidIndex);
        ranges.push(invalidIndex);
    } else {
        ranges.push(rootIndex + 1);
        ranges.push((int)nodes.size() - 1);
    }
    
    TreeNode *parent;
    while (!ranges.empty()) {
        parent = parentNodes.front();
        parentNodes.pop();
        
        if (ranges.size() > 0) {
            int start = ranges.front();
            ranges.pop();
            int end = ranges.front();
            ranges.pop();
            if (start != invalidIndex) {
                int mid = (start + end) >> 1;
                TreeNode *leftNode = new TreeNode(nodes.at(mid)->val);
                parent->left = leftNode;
                if (start != end) {
                    if (start != mid) {
                        ranges.push(start);
                        ranges.push(mid - 1);
                    } else {
                        ranges.push(invalidIndex);
                        ranges.push(invalidIndex);
                    }
                    
                    ranges.push(mid + 1);
                    ranges.push(end);
                    parentNodes.push(leftNode);
                }
            }
        }
        
        if (ranges.size() > 0) {
            int start = ranges.front();
            ranges.pop();
            int end = ranges.front();
            ranges.pop();
            
            if (start != invalidIndex) {
                int mid = (start + end) >> 1;
                TreeNode *rightNode = new TreeNode(nodes.at(mid)->val);
                parent->right = rightNode;
                if (start != end) {
                    if (start != mid) {
                        ranges.push(start);
                        ranges.push(mid - 1);
                    } else {
                        ranges.push(invalidIndex);
                        ranges.push(invalidIndex);
                    }
                    
                    ranges.push(mid + 1);
                    ranges.push(end);
                    parentNodes.push(rightNode);
                }
            }
        }
    }
    
    return root;
}


/**
 203.移除链表元素
 
 删除链表中等于给定值 val 的所有节点。
 https://leetcode-cn.com/problems/remove-linked-list-elements/
 */
ListNode* removeElements(ListNode* head, int val) {
    if (head == NULL) return NULL;
    
    ListNode *p = head;
    while (p->next != NULL) {
        if (p->next->val == val) {
            p->next = p->next->next;
        } else {
            p = p->next;
        }
    }
    if (head->val == val) {
        head = head->next;
    }
    return head;
}


/**
 876.链表的中间结点
 
 给定一个带有头结点 head 的非空单链表，返回链表的中间结点
 https://leetcode-cn.com/problems/middle-of-the-linked-list/
 */
ListNode* middleNode(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


/**
 234. 回文链表
 
 请判断一个链表是否为回文链表
 https://leetcode-cn.com/problems/palindrome-linked-list/
 */
bool isPalindrome(ListNode* head) {
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    
    ListNode *p1 = reverseList(slow);
    ListNode *p2 = head;
    while (p1 != NULL) {
        if (p1->val != p2->val) {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return true;
}


/**
 160.相交链表
 
 找到两个单链表相交的起始节点
 https://leetcode-cn.com/problems/intersection-of-two-linked-lists/
 */
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//    if (headA == NULL || headB == NULL) {
//        return NULL;
//    }
//    int lenA = 0, lenB = 0;
//    ListNode *pA = headA;
//    ListNode *pB = headB;
//    while (pA != NULL) {
//        lenA++;
//        pA = pA->next;
//    }
//    while (pB != NULL) {
//        lenB++;
//        pB = pB->next;
//    }
//
//    pA = headA;
//    pB = headB;
//    while (lenA > lenB) {
//        lenA--;
//        pA = pA->next;
//    }
//    while (lenB > lenA) {
//        lenB--;
//        pB = pB->next;
//    }
//
//    while (pA != NULL && pB != NULL) {
//        if (pA == pB) {
//            return pA;
//        }
//        pA = pA->next;
//        pB = pB->next;
//    }
//
//    return NULL;
    
    
    if (headA == NULL || headB == NULL) {
        return NULL;
    }
    ListNode *pA = headA;
    ListNode *pB = headB;
    while (pA != pB) {
        pA = pA == NULL ? headB : pA->next;
        pB = pB == NULL ? headA : pB->next;
    }
    return pA;
}


/**
 2.两数相加
 
 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

 https://leetcode-cn.com/problems/add-two-numbers/
 */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *dummy = new ListNode(0);
    ListNode *p = dummy;
    int carry = 0;
    while (l1 != NULL || l2 != NULL) {
        carry /= 10;
        if (l1 != NULL) {
            carry += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            carry += l2->val;
            l2 = l2->next;
        }
        p->next = new ListNode(carry % 10);
        p = p->next;
    }
    
    if (carry / 10 == 1) {
        p->next = new ListNode(1);
    }
    return dummy->next;
}


/**
 19.删除链表的倒数第N个结点
 
 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点
 https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/
 */
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (n <= 0) return NULL;
    
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *p1 = dummy;
    ListNode *p2 = dummy;
    while (n-- && p2 != NULL) {
        p2 = p2->next;
    }
    
    if (p2 == NULL) return NULL;
    
    while (p2->next != NULL) {
        p1 = p1->next;
        p2 = p2->next;
    }
    
    p1->next = p1->next->next;
    
    return dummy->next;
}


/**
 92. 反转链表 II
 
 反转从位置 m 到 n 的链表。请使用一趟扫描完成反转
 https://leetcode-cn.com/problems/reverse-linked-list-ii/
 */
ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *prev = dummy;
    for (int i = 1; i < m; i++) {
        prev = prev->next;
    }
    head = prev->next;
    for (int i = m; i < n; i++) {
        ListNode *p = head->next;
        head->next = p->next;
        p->next = prev->next;
        prev->next = p;
    }
    return dummy->next;
}

#endif /* linked_list_hpp */
