#include "ex35.h"
#include <cstdio>
#include "Utilities\ComplexList.h"
#include <map>
#include <iostream>
namespace ex35 {
using namespace std;
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

// 面试题35：复杂链表的复制
// 题目：请实现函数ComplexListNode* Clone(ComplexListNode* pHead)，复
// 制一个复杂链表。在复杂链表中，每个结点除了有一个m_pNext指针指向下一个
// 结点外，还有一个m_pSibling 指向链表中的任意结点或者nullptr。



void CloneNodes(ComplexListNode* pHead);
void ConnectSiblingNodes(ComplexListNode* pHead);
ComplexListNode* ReconnectNodes(ComplexListNode* pHead);

ComplexListNode* Clone(ComplexListNode* pHead)
{
    if(pHead == nullptr)
        return nullptr;

    //建立一个头指针
    ComplexListNode* pClonedHead = new ComplexListNode();
    pClonedHead->m_nValue = pHead->m_nValue;
    pClonedHead->m_pNext = nullptr;
    pClonedHead->m_pSibling = nullptr;

    map<ComplexListNode* ,ComplexListNode*> ListNodeMap;
    ListNodeMap.insert(std::pair<ComplexListNode* ,ComplexListNode*>(pHead,pClonedHead));

    ComplexListNode* pNode = pHead->m_pNext;
    ComplexListNode* pClonedNode = pClonedHead;
    while(pNode !=nullptr)
    {
         //新建一个节点
         ComplexListNode* pClonedNextNode = new ComplexListNode();
         pClonedNextNode->m_nValue = pNode->m_nValue;
         pClonedNextNode->m_pNext = nullptr;
         pClonedNextNode->m_pSibling = nullptr;

         //把新建的节点添加到pClonedNode中
         pClonedNode->m_pNext = pClonedNextNode;
         pClonedNode = pClonedNode->m_pNext;
         //同时添加到map中
         ListNodeMap.insert(std::pair<ComplexListNode* ,ComplexListNode*>(pNode,pClonedNode));

         //pNode指向下一个
         pNode = pNode->m_pNext;
    }

    pNode = pHead;
    pClonedNode = pClonedHead;

    while(pNode != nullptr)
    {
        ComplexListNode* pSipling = pNode->m_pSibling;
        if(pSipling !=nullptr)
        {
            ComplexListNode* pCloneSipling = ListNodeMap.find(pSipling)->second;
            pClonedNode->m_pSibling = pCloneSipling;
        }
        pNode = pNode->m_pNext;
        pClonedNode = pClonedNode->m_pNext;
    }

    return pClonedHead;
}

ComplexListNode* Clone_1(ComplexListNode* pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}
void CloneNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode !=nullptr)
    {
        ComplexListNode* pCloned = new ComplexListNode();
        pCloned->m_nValue = pNode->m_nValue;
        pCloned->m_pNext = pNode->m_pNext;
        pCloned->m_pSibling = pNode->m_pSibling;

        pNode->m_pNext = pCloned;
        pNode = pCloned->m_pNext;
    }
}
void CloneNodes_1(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode != nullptr)
    {
        ComplexListNode* pCloned = new ComplexListNode();
        pCloned->m_nValue = pNode->m_nValue;
        pCloned->m_pNext = pNode->m_pNext;
        pCloned->m_pSibling = nullptr;

        pNode->m_pNext = pCloned;

        pNode = pCloned->m_pNext;
    }
}
void ConnectSiblingNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while (pNode !=nullptr)
    {
        ComplexListNode* pSiblingNode = pNode->m_pSibling;
        ComplexListNode* pCloned = pNode->m_pNext;
        if(pSiblingNode != nullptr)
            pCloned->m_pSibling = pSiblingNode->m_pNext;

        pNode = pCloned->m_pNext;

    }
}
void ConnectSiblingNodes_1(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode != nullptr)
    {
        ComplexListNode* pCloned = pNode->m_pNext;
        if(pNode->m_pSibling != nullptr)
        {
            pCloned->m_pSibling = pNode->m_pSibling->m_pNext;
        }

        pNode = pCloned->m_pNext;
    }
}

ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    ComplexListNode* pClonedHead = nullptr;

    if(pNode !=nullptr)
    {
        pClonedHead = pHead->m_pNext;
        pNode->m_pNext = pClonedHead->m_pNext;
        pNode = pNode->m_pNext;
    }

    ComplexListNode* pCloned = pClonedHead;
    while(pNode !=nullptr)
    {
        pCloned->m_pNext = pNode->m_pNext;
        pCloned = pCloned->m_pNext;

        pNode->m_pNext = pCloned->m_pNext;
        pNode = pNode->m_pNext;

    }
    return pClonedHead;
}

ComplexListNode* ReconnectNodes_1(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    ComplexListNode* pClonedHead = nullptr;
    ComplexListNode* pClonedNode = nullptr;

    if(pNode != nullptr)
    {
        pClonedHead = pClonedNode = pNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }

    while(pNode != nullptr)
    {
        pClonedNode->m_pNext = pNode->m_pNext;
        pClonedNode = pClonedNode->m_pNext;

        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }

    return pClonedHead;
}

// ====================测试代码====================
void Test(const char* testName, ComplexListNode* pHead)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    printf("The original list is:\n");
    PrintList(pHead);

    ComplexListNode* pClonedHead = Clone(pHead);

    printf("The cloned list is:\n");
    PrintList(pClonedHead);

    printf("The original list is:\n");
    PrintList(pHead);
}

//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void Test1()
{
    ComplexListNode* pNode1 = CreateNode(1);
    ComplexListNode* pNode2 = CreateNode(2);
    ComplexListNode* pNode3 = CreateNode(3);
    ComplexListNode* pNode4 = CreateNode(4);
    ComplexListNode* pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, pNode3);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, nullptr);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test1", pNode1);
}

// m_pSibling指向结点自身
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//         |       | /|\           /|\
//         |       | --             |
//         |------------------------|
void Test2()
{
    ComplexListNode* pNode1 = CreateNode(1);
    ComplexListNode* pNode2 = CreateNode(2);
    ComplexListNode* pNode3 = CreateNode(3);
    ComplexListNode* pNode4 = CreateNode(4);
    ComplexListNode* pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, nullptr);
    BuildNodes(pNode2, pNode3, pNode5);
    BuildNodes(pNode3, pNode4, pNode3);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test2", pNode1);
}

// m_pSibling形成环
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//          |              /|\
//          |               |
//          |---------------|
void Test3()
{
    ComplexListNode* pNode1 = CreateNode(1);
    ComplexListNode* pNode2 = CreateNode(2);
    ComplexListNode* pNode3 = CreateNode(3);
    ComplexListNode* pNode4 = CreateNode(4);
    ComplexListNode* pNode5 = CreateNode(5);

    BuildNodes(pNode1, pNode2, nullptr);
    BuildNodes(pNode2, pNode3, pNode4);
    BuildNodes(pNode3, pNode4, nullptr);
    BuildNodes(pNode4, pNode5, pNode2);

    Test("Test3", pNode1);
}

// 只有一个结点
void Test4()
{
    ComplexListNode* pNode1 = CreateNode(1);
    BuildNodes(pNode1, nullptr, pNode1);

    Test("Test4", pNode1);
}

// 鲁棒性测试
void Test5()
{
    Test("Test5", nullptr);
}

int run()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();

    return 0;
}
int run_1()
{

    int *one = new int(1);
    int *one_1 = new int(1);

    int *tow = new int(2);
    int *tow_1 = new int(2);
    map<int *,int *> myMap;
    myMap.insert(std::pair<int*,int*>(one,one_1));
    myMap.insert(std::pair<int*,int*>(tow,tow_1));

    map<int *,int *>::iterator find = myMap.find(one);

    int* find_one_1 = find->second;

    if(find_one_1 == one_1)
        cout<<"find\n";



    *one = 88;
    for(const auto& onePair:myMap)
    {
        cout<<*onePair.first<<" "<<*onePair.second<<endl;
    }
    return 0;
}

}
