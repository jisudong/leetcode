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



/// 237.删除链表中的结点
void deleteNode(ListNode* node);


#endif /* linked_list_hpp */
