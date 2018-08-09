#include "ex17.h"
#include <cstdio>
#include <memory>
#include <cstring>
#include <vector>
#include <iostream>
namespace ex17 {
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

// 面试题17：打印1到最大的n位数
// 题目：输入数字n，按顺序打印出从1最大的n位十进制数。比如输入3，则
// 打印出1、2、3一直到最大的3位数即999。

using namespace std;
class Digit
{
    friend ostream& operator<<(ostream& os,const Digit& digit);
public:
    bool isOverflow;
    Digit(){}
    Digit(const int n):isOverflow(false){_digit = std::move(vector<char>(n,'0'));}

    Digit& operator ++()
    {
        isOverflow = false;
        auto rbegin_iter = _digit.rbegin(),rend_iter = _digit.rend();
        for(auto reiter = rbegin_iter;reiter!=rend_iter;++reiter)
        {
            int number = *reiter - '0' ;
            if(reiter == rbegin_iter)
                ++number;
            if(number >=10)
            {
                number -=10;
                if( reiter+1 != rend_iter)
                    *(reiter+1) +=1;
                else
                    isOverflow = true;
            }
            *reiter = number + '0';
        }
        return *this;
    }
    Digit& operator =(const Digit& rhs)
    {
        this->_digit = rhs._digit;
        this->isOverflow = rhs.isOverflow;
        return *this;
    }

    Digit operator ++(int)
    {
        Digit preDigit = *this;
        ++(*this);
        return preDigit;
    }
private:
    vector<char> _digit;

};
class Digit2
{
    friend ostream& operator<<(ostream& os,const Digit2& digit);
public:
    bool isOverflow;
    Digit2(){//初始化_digit
        _digit = new char[1];
        _digit[1] = '\0';
    }
    Digit2(const int n):isOverflow(false)
    {
        //初始化_digit
        _digit = new char[n+1];
        memset(_digit,'0',n);
        _digit[n] = '\0';
    }
    ~Digit2(){delete []_digit;}

    Digit2& operator ++()
    {
        isOverflow = false;
        int length = strlen(_digit);
        for(int index=length-1;index >=0;--index)
        {
            int number = _digit[index] - '0';
            if(index ==length-1)
                ++number;

            if(number>=10)
            {
                number -=10;
                if(index == 0)
                    isOverflow = true;
                else
                    ++_digit[index-1];

            }
            _digit[index] = number + '0';

        }

        return *this;
    }


    Digit2& operator =(const Digit2& rhs)
    {
        if(&rhs !=this)
        {
            delete []this->_digit;
            int length = strlen(rhs._digit);
            this->_digit = new char[length + 1];
            for(int i=0;i<=length;++i)
            {
                this->_digit[i] = rhs._digit[i];
            }
            this->isOverflow = rhs.isOverflow;
        }
        return *this;
    }

    Digit2 operator ++(int)
    {
        Digit2 preDigit;
        preDigit = *this;
        ++(*this);
        return preDigit;
    }
private:
    char* _digit;

};
ostream& operator<<(ostream& os,const Digit& digit)
{
    bool isBeginning0 = true;
    for(const auto& value:digit._digit)
    {
        if(isBeginning0&&(value - '0')!=0)
            isBeginning0 = false;

        if(!isBeginning0)
            os<<value;
    }
    if(isBeginning0)
        os<<0;

    return os;
}
ostream& operator<<(ostream& os,const Digit2& digit)
{
    bool isBeginning0 = true;
    int length = strlen(digit._digit);
    for(int i=0;i<length;++i)
    {
        if(isBeginning0&&(digit._digit[i]!='0'))
            isBeginning0 = false;
        if(!isBeginning0)
            os<<digit._digit[i];
    }
    if(isBeginning0)
        os<<'0';

    return os;
}
void PrintNumber(char* number);
bool Increment(char* number);
void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index,bool& isBeginning0);

void PrintOneToMaxOfNDigits_1(int n)
{
    if (n <= 0)
        return;

    Digit2 digit(n);
    //cout <<digit<<endl;
    //    while(!(++digit).isOverflow)
    //    {
    //        cout<<digit<<" ";
    //    }
    //    cout<<endl;
    //    digit.isOverflow = false;


    while(!(++digit).isOverflow)
    {
        //cout << digit<<" ";
    }
    cout <<"over!" <<endl;
}

// ====================方法一====================
void Print1ToMaxOfNDigits_1(int n)
{
    if (n <= 0)
        return;

    char *number = new char[n + 1];
    memset(number, '0', n);
    number[n] = '\0';

    while (!Increment(number))
    {
        PrintNumber(number);
    }
    cout <<endl;

    delete[]number;
}

// 字符串number表示一个数字，在 number上增加1
// 如果做加法溢出，则返回true；否则为false
bool Increment(char* number)
{
    bool isOverflow = false;
    int nTakeOver = 0;
    int nLength = strlen(number);

    for (int i = nLength - 1; i >= 0; i--)
    {
        int nSum = number[i] - '0' + nTakeOver;
        if (i == nLength - 1)
            nSum++;

        if (nSum >= 10)
        {
            if (i == 0)
                isOverflow = true;
            else
            {
                nSum -= 10;
                nTakeOver = 1;
                number[i] = '0' + nSum;
            }
        }
        else
        {
            number[i] = '0' + nSum;
            break;
        }
    }

    return isOverflow;
}

// ====================方法二====================
void Print1ToMaxOfNDigits_2(int n)
{
    if (n <= 0)
        return;

    char* number = new char[n + 1];
    number[n] = '\0';

    bool isBeginning0 = true;
    Print1ToMaxOfNDigitsRecursively(number, n, 0,isBeginning0);

    cout <<endl;
    delete[] number;
}

void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index,bool& isBeginning0)
{
    if (index == length )
    {
        if(isBeginning0)
        {
            isBeginning0 = false;
            return;
        }

        PrintNumber(number);
        return;
    }

    for (int i = 0; i < 10; ++i)
    {
        number[index ] = i + '0';
        Print1ToMaxOfNDigitsRecursively(number, length, index + 1,isBeginning0);
    }
}

// ====================公共函数====================
// 字符串number表示一个数字，数字有若干个0开头
// 打印出这个数字，并忽略开头的0
void PrintNumber(char* number)
{
    bool isBeginning0 = true;
    int nLength = strlen(number);

    for (int i = 0; i < nLength; ++i)
    {
        if (isBeginning0 && number[i] != '0')
            isBeginning0 = false;

        if (!isBeginning0)
        {
            printf("%c", number[i]);
        }
    }

    printf("\t");
}

// ====================测试代码====================
void Test(int n)
{
    printf("Test for %d begins:\n", n);

    Print1ToMaxOfNDigits_1(n);
    Print1ToMaxOfNDigits_2(n);

    printf("\nTest for %d ends.\n", n);
}

void run()
{
    //    Test(1);
    //    Test(2);

    //    Test(0);
    //    Test(-1);
    //    vector<char> cVec;
    //    cVec = std::move(vector<char>(2,'0'));
    //    auto iter = cVec.begin();
    //    *iter +=1;
    //    int number = *cVec.begin() - '0';
    //    cout <<number<<endl;

    //Test(9);

    Print1ToMaxOfNDigits_2(2);

    //Print1ToMaxOfNDigits_2(3);





}
}
