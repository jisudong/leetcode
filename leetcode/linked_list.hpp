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

using namespace std;

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

 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/delete-node-in-a-linked-list/
*/
void deleteNode(ListNode* node) {
    node->val = node->next->val;
    node->next = node->next->next;
}


/**
 21.合并两个有序链表
 
 将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/merge-two-sorted-lists/
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
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/
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
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/linked-list-cycle/
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
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/reverse-linked-list/
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
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/
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
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/remove-linked-list-elements/
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
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/middle-of-the-linked-list/
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
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/palindrome-linked-list/
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
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/intersection-of-two-linked-lists/
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

 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/add-two-numbers/
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
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/
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
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/reverse-linked-list-ii/
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


/**
 24. 两两交换链表中的节点
 
 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs/
 */
ListNode* swapPairs(ListNode* head) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *prev = dummy;
    while (head != NULL && head->next != NULL) {
        ListNode *p = head->next;
        head->next = p->next;
        p->next = prev->next;
        prev->next = p;
        prev = head;
        head = head->next;
    }
    return dummy->next;
}


/**
61.旋转链表
 
 给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/rotate-list/
 */
ListNode* rotateRight(ListNode* head, int k) {
    ListNode *p = head;
    ListNode *last = NULL;
    int len = 0;
    while (p != NULL) {
        last = p;
        p = p->next;
        len++;
    }
    if (len == 0 || k % len == 0) {
        return head;
    }
    
    last->next = head;
    p = head;
    k %= len;
    
    while (len - k) {
        last = p;
        p = p->next;
        len--;
    }
    last->next = NULL;
    return p;
}


/**
 82. 删除排序链表中的重复元素 II
 
 给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/
 */
ListNode* deleteDuplicates2(ListNode* head) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *prev = dummy;
    ListNode *p = head;
    bool haveduplicate = false;
    while (p != NULL && p->next != NULL) {
        if (p->val == p->next->val) {
            p->next = p->next->next;
            haveduplicate = true;
        } else {
            p = p->next;
            if (haveduplicate) {
                prev->next = p;
                haveduplicate = false;
            } else {
                prev = prev->next;
            }
        }
    }
    if (haveduplicate) {
        prev->next = NULL;
    }
    return dummy->next;
}


/**
 86. 分隔链表
 
 给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。

 你应当保留两个分区中每个节点的初始相对位置。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/partition-list/
 */
ListNode* partition(ListNode* head, int x) {
    ListNode *dummy1 = new ListNode(0);
    ListNode *dummy2 = new ListNode(0);
    ListNode *p1 = dummy1;
    ListNode *p2 = dummy2;
    while (head != NULL) {
        if (head->val < x) {
            p1->next = head;
            head = head->next;
            p1 = p1->next;
        } else {
            p2->next = head;
            head = head->next;
            p2 = p2->next;
        }
    }
    p2->next = NULL;
    p1->next = dummy2->next;
    head = dummy1->next;
    delete dummy1;
    delete dummy2;
    return head;
}


/**
 142. 环形链表 II
 
 给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/linked-list-cycle-ii/
 */
ListNode *detectCycle(ListNode *head) {
//    if (head == NULL || head->next == NULL) {
//        return NULL;
//    }
//    ListNode *p = head; // 快指针
//    ListNode *q = head; // 慢指针
//    while (p->next != NULL && p->next->next != NULL) {
//        q = q->next;
//        p = p->next->next;
//        if (p == q) { // 有环
//            p = head;
//            while (p != q) {
//                p = p->next;
//                q = q->next;
//            }
//            return p;
//        }
//    }
//    return NULL;
    
    // 堆的地址从低到高，LeetCode的链表内存是顺序申请的，如果有环，head->next一定小于head
    // 此方法有讨巧的地方，仅作为一种思路
    while (head != NULL) {
        if (!std::less<ListNode *>()(head, head->next)) {
            return head->next;
        }
        head = head->next;
    }
    return NULL;
}


/**
 143. 重排链表
 
 给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
 将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…

 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/reorder-list/
 */
void reorderList(ListNode* head) {
    if (head == NULL) return;
    ListNode *dummy = new ListNode(0);
    
    ListNode *p1 = head;
    ListNode *p2 = head->next;
    while (p2 != NULL && p2->next != NULL) {
        p1 = p1->next;
        p2 = p2->next->next;
    }
    
    ListNode *prev = p1;
    p2 = p1->next;
    while (prev->next && p2->next) {
        ListNode *p = p2->next;
        p2->next = p->next;
        p->next = prev->next;
        prev->next = p;
    }
    
    ListNode *l2 = prev->next;
    prev->next = NULL;
    p1 = dummy;
    while (head != NULL) {
        p1->next = head;
        head = head->next;
        p1 = p1->next;
        
        if (l2) {
            p1->next = l2;
            l2 = l2->next;
            p1 = p1->next;
        }
        
    }
    
    head = dummy->next;
}


/**
 147. 对链表进行插入排序
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/insertion-sort-list/
 */
ListNode* insertionSortList(ListNode* head) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *sorted;
    while (head != NULL && head->next != NULL) {
        if (head->val <= head->next->val) {
            head = head->next;
            continue;
        }
        sorted = dummy;
        while (sorted->next->val < head->next->val) {
            sorted = sorted->next;
        }
        ListNode *cur = head->next;
        head->next = cur->next;
        cur->next = sorted->next;
        sorted->next = cur;
    }
    return dummy->next;
}


/**
 148. 排序链表
 
 在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/sort-list/
 */
ListNode *cut(ListNode *head, int n) {
    ListNode *p = head;
    while (--n && p != NULL) {
        p = p->next;
    }
    if (p == NULL) {
        return NULL;
    }
    ListNode *next = p->next;
    p->next = NULL;
    return next;
}
ListNode* sortList(ListNode* head) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *p = head;
    int length = 0;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    for (int i = 1; i < length; i <<= 1) {
        ListNode *cur = dummy->next;
        ListNode *tail = dummy;
        while (cur != NULL) {
            ListNode *left = cur;
            ListNode *right = cut(left, i);
            cur = cut(right, i);
            
            tail->next = mergeTwoLists(left, right);
            while (tail->next != NULL) {
                tail = tail->next;
            }
        }
    }
    return dummy->next;
}


/**
 328. 奇偶链表
 
 给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，而不是节点的值的奇偶性。

 请尝试使用原地算法完成。你的算法的空间复杂度应为 O(1)，时间复杂度应为 O(nodes)，nodes 为节点总数。

 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/odd-even-linked-list/
 */
ListNode* oddEvenList(ListNode* head) {
//    if (head == NULL) return NULL;
//    ListNode *dummy1 = new ListNode(0);
//    ListNode *dummy2 = new ListNode(0);
//    ListNode *p1 = dummy1, *p2 = dummy2;
//    int length = 0;
//    while (head != NULL) {
//        length++;
//        if (length % 2 == 1) {
//            p1->next = head;
//            p1 = p1->next;
//        } else {
//            p2->next = head;
//            p2 = p2->next;
//        }
//        head = head->next;
//    }
//    p2->next = NULL;
//    p1->next = dummy2->next;
//    return dummy1->next;
    
    if (head == NULL || head->next == NULL) {
        return head;
    }
    // head 为奇链表头结点，o 为奇链表尾结点
    ListNode *o = head;
    // p 为偶链表头结点
    ListNode *p = head->next;
    // e 为偶链表尾结点
    ListNode *e = p;
    while (o->next != NULL && e->next != NULL) {
        o->next = e->next;
        o = o->next;
        e->next = o->next;
        e = e->next;
    }
    o->next = p;
    return head;
}


/**
 725. 分隔链表
 
 给定一个头结点为 root 的链表, 编写一个函数以将链表分隔为 k 个连续的部分。

 每部分的长度应该尽可能的相等: 任意两部分的长度差距不能超过 1，也就是说可能有些部分为 null。

 这k个部分应该按照在链表中出现的顺序进行输出，并且排在前面的部分的长度应该大于或等于后面的长度。

 返回一个符合上述规则的链表的列表。

 举例： 1->2->3->4, k = 5 // 5 结果 [ [1], [2], [3], [4], null ]

 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/split-linked-list-in-parts
 */
vector<ListNode*> splitListToParts(ListNode* root, int k) {
//    vector<ListNode *> lists;
//    ListNode *p = root;
//    int length = 0;
//    while (p != NULL) {
//        length++;
//        p = p->next;
//    }
//
//    int len = length / k;
//    int remainder = length % k;
//    p = root;
//
//    while (p != NULL) {
//        lists.push_back(p);
//        for (int i = 1; i < len; i++) {
//            p = p->next;
//        }
//        if (len > 0 && remainder > 0) {
//            p = p->next;
//            remainder--;
//        }
//        ListNode *tmp = p->next;
//        p->next = NULL;
//        p = tmp;
//    }
//
//    for (int i = (int)lists.size(); i < k; i++) {
//        lists.push_back(NULL);
//    }
//
//    return lists;
    
    
    ListNode *p = root;
    int length = 0;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    int aveLength = length / k;
    int remainder = length % k;
    vector<ListNode *> lists(k, NULL);
    ListNode *head = root;
    ListNode *prev = NULL;
    for (int i = 0; i < k; i++) {
        lists[i] = head;
        int tempLength = remainder > 0 ? (aveLength + 1) : aveLength;
        for (int j = 0; j < tempLength; j++) {
            prev = head;
            head = head->next;
        }
        if (prev != NULL) prev->next = NULL;
        if (remainder > 0) remainder--;
    }
    return lists;
}

/**
 二叉树层序遍历
 */
void levelTraversal(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *node = q.front();
        q.pop();
        cout << node->val << endl;
        if (node->left != NULL) {
            q.push(node->left);
        }
        if (node->right != NULL) {
            q.push(node->right);
        }
    }
}



#endif /* linked_list_hpp */
