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

/*返回三个整数的最大值*/
int Max(int A, int B, int C) {
    return (A > B) ? (A > C ? A : C) : (B > C ? B : C);
}

/*分治法球List[left]到List[right]的最大子列和*/
int divideAndConquer(int list[], int left, int right) {
    int maxLeftSum, maxRightSum;  //存放左右子问题的解
    int maxLeftBorderSum, maxRightBorderSum;  //存放跨分界线的结果
    
    int leftBorderSum, rightBorderSum;
    int center, i;
    
    /*递归的终止条件，子列只有1个数字*/
    if (left == right) {
        if (list[left] > 0) {
            return list[left];
        } else {
            return 0;
        }
    }
    
    /* “分”的过程 */
    center = (left + right) >> 1; //找到中分点
    maxLeftSum = divideAndConquer(list, left, center); //递归求左子列和
    maxRightSum = divideAndConquer(list, center + 1, right); //递归求右子列和
    
    /*求跨分界线的最大子列和*/
    maxLeftBorderSum = 0;
    leftBorderSum = 0;
    for (i = center; i >= left; i--) {
        leftBorderSum += list[i];
        if (leftBorderSum > maxLeftBorderSum) {
            maxLeftBorderSum = leftBorderSum;
        }
    } //左边扫描结束
    
    maxRightBorderSum = 0;
    rightBorderSum = 0;
    for (i = center + 1; i <= right; i++) {
        rightBorderSum += list[i];
        if (rightBorderSum > maxRightBorderSum) {
            maxRightBorderSum = rightBorderSum;
        }
    } //右边扫描结束
    
    return Max(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int maxSubseqSum(int a[], int n) {
    // 三重循环
//    int thisSum, maxSum = 0;
//    int i, j, k;
//    for (i = 0; i < n; i++) {
//        for (j = i; j < n; j++) {
//            thisSum = 0;
//            for (k = i; k < j; k++) {
//                thisSum += a[k];
//            }
//            if (thisSum > maxSum) {
//                maxSum = thisSum;
//            }
//        }
//    }
//    return maxSum;
    
    
    // 两重循环
//    int thisSum, maxSum = 0;
//    int i, j;
//    for (i = 0; i < n; i++) {
//        thisSum = 0;
//        for (j = i; j < n; j++) {
//            thisSum += a[j];
//            if (thisSum > maxSum) {
//                maxSum = thisSum;
//            }
//        }
//
//    }
//    return maxSum;
    
    
    //在线处理
//    int thisSum, maxSum, i;
//    thisSum = maxSum = 0;
//    for (i = 0; i < n; i++) {
//        thisSum += a[i];
//        if (thisSum > maxSum) {
//            maxSum = thisSum;
//        } else if (thisSum < 0) {
//            thisSum = 0;
//        }
//    }
//    return maxSum;

    
    // 分而治之
    return divideAndConquer(a, 0, n-1);
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
