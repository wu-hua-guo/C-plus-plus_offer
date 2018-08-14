#include "ex24.h"

#include <cstdio>
#include "Utilities\List.h"
namespace ex24 {
/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/

//==================================================================
// 《剑指Offer——名企面试官精讲典型编程题》代码
// 作者：何海涛
//==================================================================

// 面试题24：反转链表
// 题目：定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的
// 头结点。

ListNode* ReverseList(ListNode* pHead)
{
    if(pHead == nullptr)
        return nullptr;

    ListNode* pReversHead = pHead;
    ListNode* pNext = pHead->m_pNext;
    pReversHead->m_pNext = nullptr;
    while(pNext != nullptr)
    {
        ListNode* pNode = pNext;
        pNext = pNext->m_pNext;

        pNode->m_pNext = pReversHead;
        pReversHead = pNode;
    }

    return pReversHead;

}

ListNode* ReverseList_1(ListNode* pHead)
{
    if(pHead == nullptr)
        return nullptr;


    ListNode* pReversHead = nullptr;
    ListNode* pPrev = nullptr;
    ListNode* pNode = pHead;

    while(pNode !=nullptr)
    {
        ListNode* pNext = pNode->m_pNext;
        if(pNext == nullptr)
            pReversHead = pNode;

        pNode->m_pNext = pPrev;

        pPrev = pNode;
        pNode = pNext;
    }

    return pReversHead;

}

ListNode* ReverseList_2(ListNode* pHead)
{
    ListNode* pReversedHead = nullptr;
    ListNode* pNode = pHead;
    ListNode* pPrev = nullptr;
    while(pNode != nullptr)
    {
        ListNode* pNext = pNode->m_pNext;

        if(pNext == nullptr)
            pReversedHead = pNode;

        pNode->m_pNext = pPrev;

        pPrev = pNode;
        pNode = pNext;
    }

    return pReversedHead;
}

// ====================测试代码====================
ListNode* Test(ListNode* pHead)
{
    printf("The original list is: \n");
    PrintList(pHead);

    ListNode* pReversedHead = ReverseList(pHead);

    printf("The reversed list is: \n");
    PrintList(pReversedHead);

    return pReversedHead;
}

// 输入的链表有多个结点
void Test1()
{
    printf("Test1:\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    ListNode* pReversedHead = Test(pNode1);

    DestroyList(pReversedHead);
}

// 输入的链表只有一个结点
void Test2()
{
    printf("Test2:\n");
    ListNode* pNode1 = CreateListNode(1);

    ListNode* pReversedHead = Test(pNode1);

    DestroyList(pReversedHead);
}

// 输入空链表
void Test3()
{
    printf("Test3:\n");
    Test(nullptr);
}

void Test4()
{
    printf("Test4:\n");
    ListNode* pNode1 = CreateListNode(5);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(99);
    ListNode* pNode4 = CreateListNode(49);
    ListNode* pNode5 = CreateListNode(512);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    ListNode* pReversedHead = Test(pNode1);

    DestroyList(pReversedHead);
}
int run()
{
    Test1();
    Test2();
    Test3();
    Test4();

    return 0;
}


}
