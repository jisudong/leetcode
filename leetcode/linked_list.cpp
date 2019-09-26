//
//  linked_list.cpp
//  leetcode
//
//  Created by 秀健身 on 2019/9/26.
//  Copyright © 2019 jisudong. All rights reserved.
//

#include "linked_list.hpp"


/**
 237.删除链表中的结点
 
 删除某个链表中给定的（非末尾）节点，你将只被给定要求被删除的节点。
 https://leetcode-cn.com/problems/delete-node-in-a-linked-list/
 */
void deleteNode(ListNode* node) {
    node->val = node->next->val;
    node->next = node->next->next;
}
