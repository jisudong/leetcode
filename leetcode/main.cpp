//
//  main.cpp
//  leetcode
//
//  Created by jisudong on 2019/9/26.
//  Copyright © 2019 jisudong. All rights reserved.
//

#include <iostream>
#include "linked_list.hpp"
#include <queue>
#include <cstdlib>

using namespace std;

void middleorder(TreeNode *tree) {
    if (tree == NULL) {
        return;
    }
    middleorder(tree->left);
    cout << tree->val << endl;
    middleorder(tree->right);
}

int maxSubseqSum(int a[], int n) {
    // 三重循环
    int thisSum, maxSum = 0;
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            thisSum = 0;
            for (k = i; k < j; k++) {
                thisSum += a[k];
            }
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

int main(int argc, const char * argv[]) {
    
    int a[] = {-2, 11, -4, 13, -5, -2};
    int res = maxSubseqSum(a, 6);
    
    ListNode *l1 = new ListNode(0);
    ListNode *l2 = new ListNode(0);
    ListNode *p1 = l1;
    ListNode *p2 = l2;
    for (int i = 1; i < 3; i++) {
        p1->next = new ListNode((rand()%30));
        p1 = p1->next;
        p2->next = new ListNode(i);
        p2 = p2->next;
        if (i % 2 != 0) {
//            if (i >= 5) {
//                if (i == 5) {
//                    p2->next = p1;
//                }
//            } else {
//            }
            
            
        } else {
            
        }
    }
    
//    p1->next = l1->next->next;
    
//    p2 = reverseList(l2->next);
//    p1->next = p2;
    
//    p1->next = l1->next->next->next;
   
//    ListNode *result = deleteDuplicates(l1->next);
//    bool isCycle = hasCycle(l1->next);
//    ListNode *result = reverseList(l1->next);

//    TreeNode *tree = sortedListToBST(l1->next);
//    middleorder(tree);
    
//     ListNode *result = oddEvenList(l1->next);
//    bool isPalind = isPalindrome(l1->next);
//    reorderList(l1->next);
    
    vector<ListNode *> lists = splitListToParts(l1->next, 5);
       
    getchar();
    
    return 0;
}
