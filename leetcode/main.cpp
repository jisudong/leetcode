//
//  main.cpp
//  leetcode
//
//  Created by 秀健身 on 2019/9/26.
//  Copyright © 2019 jisudong. All rights reserved.
//

#include <iostream>
#include "linked_list.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    ListNode *l1 = new ListNode(0);
    ListNode *l2 = new ListNode(0);
    ListNode *p1 = l1;
    ListNode *p2 = l2;
    for (int i = 1; i < 7; i++) {
        p1->next = new ListNode(i);
        p1 = p1->next;
        if (i % 2 != 0) {
            p1->next = new ListNode(i);
            p1 = p1->next;
        } else {
            p2->next = new ListNode(i);
            p2 = p2->next;
        }
    }
   
    ListNode *result = deleteDuplicates(l1->next);
       
    getchar();
    
    return 0;
}
