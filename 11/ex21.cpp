#include "ex21.h"
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
namespace ex21 {
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

// 面试题21：调整数组顺序使奇数位于偶数前面
// 题目：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有
// 奇数位于数组的前半部分，所有偶数位于数组的后半部分。

void reorder_1(vector<int>& iVec)
{
    if(iVec.size()<=1)
        return;

    auto iterBegin = iVec.begin();
    auto iterEnd = iVec.end() - 1;
    while (iterBegin < iterEnd) {
        while(iterBegin < iterEnd && (*iterBegin &0x1) == 1 )
            ++iterBegin;

        while(iterBegin < iterEnd && (*iterEnd &0x1) == 0)
            --iterEnd;

        if(iterBegin<iterEnd){
            int temp = *iterBegin;
            *iterBegin = *iterEnd;
            *iterEnd = temp;
        }
    }
}
bool isOdd(const int& value)
{
    if(value&0x1)
        return true;
    return false;
}
void reorder(vector<int>& iVec,bool (*fun)(const int& value))
{
    auto iterBegin = iVec.begin();
    auto iterEnd = iVec.end() - 1;
    while (iterBegin < iterEnd) {
        while(iterBegin < iterEnd && fun(*iterBegin) )
            ++iterBegin;

        while(iterBegin < iterEnd && !fun(*iterEnd))
            --iterEnd;

        if(iterBegin<iterEnd){
            int temp = *iterBegin;
            *iterBegin = *iterEnd;
            *iterEnd = temp;
        }
    }
}

void reorder_2(vector<int>& iVec)
{
    if(iVec.size()<=1)
        return;
    reorder(iVec,isOdd);

}
void Reorder(int *pData, unsigned int length, bool (*func)(int));
//是否是偶数
bool isEven(int n);

// ====================方法一====================
void ReorderOddEven_1(int *pData, unsigned int length)
{
    if(pData == nullptr || length == 0)
        return;

    int *pBegin = pData;
    int *pEnd = pData + length - 1;

    while(pBegin < pEnd)
    {
        // 向后移动pBegin，直到它指向偶数
        while(pBegin < pEnd && (*pBegin & 0x1) != 0)
            pBegin ++;

        // 向前移动pEnd，直到它指向奇数
        while(pBegin < pEnd && (*pEnd & 0x1) == 0)
            pEnd --;

        if(pBegin < pEnd)
        {
            int temp = *pBegin;
            *pBegin = *pEnd;
            *pEnd = temp;
        }
    }
}

// ====================方法二====================
void ReorderOddEven_2(int *pData, unsigned int length)
{
    Reorder(pData, length, isEven);
}

void Reorder(int *pData, unsigned int length, bool (*func)(int))
{
    if(pData == nullptr || length == 0)
        return;

    int *pBegin = pData;
    int *pEnd = pData + length - 1;

    while(pBegin < pEnd)
    {
        // 向后移动pBegin
        while(pBegin < pEnd && !func(*pBegin))
            pBegin ++;

        // 向前移动pEnd
        while(pBegin < pEnd && func(*pEnd))
            pEnd --;

        if(pBegin < pEnd)
        {
            int temp = *pBegin;
            *pBegin = *pEnd;
            *pEnd = temp;
        }
    }
}

bool isEven(int n)
{
    return (n & 1) == 0;
}

// ====================测试代码====================
void PrintArray(int numbers[], int length)
{
    if(length < 0)
        return;

    for(int i = 0; i < length; ++i)
        printf("%d\t", numbers[i]);

    printf("\n");
}
void printNum(const int& value)
{
    cout<<value<<" ";
}

void Test(char* testName, int numbers[], int length)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

//    vector<int> iVec(numbers,numbers+length);

//    for_each(iVec.begin(),iVec.end(),[](const int& value){cout<<value<<" ";});
//    cout<<endl;

//    int* copy = new int[length];
//    for(int i = 0; i < length; ++i)
//    {
//        copy[i] = numbers[i];
//    }

//    printf("Test for solution 1:\n");
//    //PrintArray(numbers, length);
//    for_each(numbers,numbers+length,[](const int& value){cout<<value<<" ";});
//    cout<<endl;
//    ReorderOddEven_1(numbers, length);
//    //PrintArray(numbers, length);
//    for_each(numbers,numbers+length,[](const int& value){cout<<value<<" ";});
//    cout<<endl;

//    printf("Test for solution 2:\n");
//    //PrintArray(copy, length);
//    for_each(copy,copy+length,[](const int& value){cout<<value<<" ";});
//    cout<<endl;
//    ReorderOddEven_2(copy, length);
//    //PrintArray(copy, length);
//    for_each(copy,copy+length,[](const int& value){cout<<value<<" ";});
//    cout<<endl;


    cout << "reoder_1:"<<endl;
    vector<int> iVec(numbers,numbers+length);
    for_each(iVec.begin(),iVec.end(),[](const int& value){cout<<value<<" ";});
    cout<<endl;

    reorder_1(iVec);

    for_each(iVec.begin(),iVec.end(),[](const int& value){cout<<value<<" ";});
    cout<<endl;


    cout << "reoder_2:"<<endl;
    vector<int> iVec2(numbers,numbers+length);
    for_each(iVec2.begin(),iVec2.end(),[](const int& value){cout<<value<<" ";});
    cout<<endl;

    reorder_2(iVec2);

    for_each(iVec2.begin(),iVec2.end(),[](const int& value){cout<<value<<" ";});
    cout<<endl;

//    delete[] copy;
}

void Test1()
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7};
    Test("Test1", numbers, sizeof(numbers)/sizeof(int));
}

void Test2()
{
    int numbers[] = {2, 4, 6, 1, 3, 5, 7};
    Test("Test2", numbers, sizeof(numbers)/sizeof(int));
}

void Test3()
{
    int numbers[] = {1, 3, 5, 7, 2, 4, 6};
    Test("Test3", numbers, sizeof(numbers)/sizeof(int));
}

void Test4()
{
    int numbers[] = {1};
    Test("Test4", numbers, sizeof(numbers)/sizeof(int));
}

void Test5()
{
    int numbers[] = {2};
    Test("Test5", numbers, sizeof(numbers)/sizeof(int));
}

void Test6()
{
    Test("Test6", nullptr, 0);
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