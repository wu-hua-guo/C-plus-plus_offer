#include "ex22_1.h"
#include<cstdio>
#include <stdlib.h>
namespace ex22_1 {


//结构体节点
struct ListNode
{
    int       m_nValue;
    ListNode* m_pNext;
};
void PrintListNode(ListNode* pNode)
{
    if(pNode == nullptr)
    {
        printf("The node is nullptr\n");
    }
    else
    {
        printf("The key in node is %d.\n", pNode->m_nValue);
    }
}
ListNode* CreateListNode(int value)
{
    ListNode* pNode = new ListNode();
    pNode->m_nValue = value;
    pNode->m_pNext = nullptr;

    return pNode;
}
void ConnectListNodes(ListNode* pCurrent, ListNode* pNext)
{
    if(pCurrent == nullptr)
    {
        printf("Error to connect two nodes.\n");
        exit(1);
    }

    pCurrent->m_pNext = pNext;
}
void DestroyList(ListNode** pHead)
{
    if(pHead == nullptr||*pHead == nullptr)
        return;

    ListNode* nextNode = ((*pHead)->m_pNext);
    delete *pHead;
    *pHead = nullptr;
    //pHead = nullptr;
    //
    DestroyList(&nextNode);
}


ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
    //输入链表为空，或者查找数为0，是非法输入，则输出空结果
    if(pListHead == nullptr || k == 0)
        return nullptr;

    ListNode *pAhead = pListHead;
    ListNode *pBehind = nullptr;

    for(unsigned int i = 0; i < k - 1; ++ i)
    {
        //输入n是否超出节点数目
        if(pAhead->m_pNext != nullptr)
            pAhead = pAhead->m_pNext;
        else
        {
            return nullptr;
        }
    }

    pBehind = pListHead;
    while(pAhead->m_pNext != nullptr)
    {
        pAhead = pAhead->m_pNext;
        pBehind = pBehind->m_pNext;
    }

    return pBehind;
}

ListNode* FindKthToTail_2(ListNode* pListHead,unsigned int k)
{
    if(pListHead == nullptr || k == 0)
    {
        return nullptr;
    }

    unsigned int size = 0;
    ListNode* pHead = pListHead;
    while(pHead !=nullptr)
    {
        ++size;
        pHead = pHead->m_pNext;
    }

    pHead = pListHead;
    unsigned int n = size - k + 1;
    if(n > 0)
    {
        for(unsigned int index = 1;index < n;++index)
        {
            pHead = pHead->m_pNext;
        }
    }
    else return nullptr;

    return pHead;
}
void Test1()
{
    printf("=====Test1 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf(" expected result: 4.\n");
    ListNode* pNode = FindKthToTail(pNode1, 2);
    PrintListNode(pNode);

    pNode = FindKthToTail_2(pNode1, 2);
    PrintListNode(pNode);

    DestroyList(&pNode1);
}
// 测试要找的结点是链表的尾结点
void Test2()
{
    printf("=====Test2 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: 5.\n");
    ListNode* pNode = FindKthToTail(pNode1, 1);
    PrintListNode(pNode);


    pNode = FindKthToTail_2(pNode1, 2);
    PrintListNode(pNode);

    DestroyList(&pNode1);
}

// 测试要找的结点是链表的头结点
void Test3()
{
    printf("=====Test3 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: 1.\n");
    ListNode* pNode = FindKthToTail(pNode1, 5);
    PrintListNode(pNode);

    pNode = FindKthToTail_2(pNode1, 3);
    PrintListNode(pNode);

    DestroyList(&pNode1);
}

// 测试空链表
void Test4()
{
    printf("=====Test4 starts:=====\n");
    printf("expected result: nullptr.\n");
    ListNode* pNode = FindKthToTail(nullptr, 100);
    PrintListNode(pNode);

    pNode = FindKthToTail_2(nullptr, 100);
    PrintListNode(pNode);
}

// 测试输入的第二个参数大于链表的结点总数
void Test5()
{
    printf("=====Test5 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: nullptr.\n");
    ListNode* pNode = FindKthToTail(pNode1, 6);
    PrintListNode(pNode);

    pNode = FindKthToTail_2(pNode1, 6);
    PrintListNode(pNode);

    DestroyList(&pNode1);
}

// 测试输入的第二个参数为0
void Test6()
{
    printf("=====Test6 starts:=====\n");
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    printf("expected result: nullptr.\n");
    ListNode* pNode = FindKthToTail(pNode1, 0);
    PrintListNode(pNode);

    pNode = FindKthToTail_2(pNode1, 0);
    PrintListNode(pNode);
    DestroyList(&pNode1);
}
int run()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

    return 0;
}
}
